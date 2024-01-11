
//  Author:     Lukas Gregor
//  Date:       18.07.2023
//  Title:      sin_wave_generator
//  Iteration:  V1.0
//
//  Notes:
//  
//
//  ToDo:
//  - find the reason for the column bug
//  - understand the sin() and radians() functions
//
//
//  Goals:
//  - make a loading screen 


// Rotary Encoder Inputs
#define nEnable 9
#define CLK 8
#define DT 7
#define SW 6

int motor_position = 0;
int counter = 0;
int old_counter = counter;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

//Steppi
#include <SpeedyStepper.h>
SpeedyStepper stepper;

// SSD1306
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       // Root library
#include <Adafruit_SSD1306.h>   // Library for using a specific display

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

const int LED_PIN = 13;
const int MOTOR_STEP_PIN = 3;
const int MOTOR_DIRECTION_PIN = 2;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
	// Set encoder pins as inputs
	pinMode(CLK,INPUT);
	pinMode(DT,INPUT);
	pinMode(SW, INPUT_PULLUP);
  pinMode(nEnable,OUTPUT);

	// Setup Serial Monitor
	Serial.begin(9600);
  digitalWrite(nEnable,HIGH);

	// Read the initial state of CLK
	lastStateCLK = digitalRead(CLK);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();

  saturn_animation();

  home_screen();
}

void loop() {
  // put your main code here, to run repeatedly:

}



void testdrawline() {
  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(i, 0, i,display.height()-1, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn line
  }
}



void saturn_animation() {
  int16_t i;
  display.clearDisplay();

  for (i=0;i<=360;i++) {
    // the starting point gets zeroed to the middle of the screen by deviding the displayhight by 2.
    // Ontop of that the sinwave gets added. The Aplitude is 20 Pixels. It is important to use radians for yet unknown reasons. If the columns aren't set right, a bug might occur.
    if(i<300){
    display.drawPixel(display.width()/2 + 20*sin(radians((i*5)+90)), display.height()/2 + 20*sin(radians(i*5)), 1);
    }
    display.drawPixel(display.width()/2 + 20*sin(radians((i*5))), display.height()/2 + 20*sin(radians((i*5)-90)), 0);
    if(i<300){
    display.drawPixel(display.width()/2 + -20*sin(radians((i*5)+90)), display.height()/2 + -20*sin(radians(i*5)), 1);
    }
    display.drawPixel(display.width()/2 + -20*sin(radians((i*5))), display.height()/2 + -20*sin(radians((i*5)-90)), 0);


    display.drawPixel(display.width()/2 + 35*sin(radians((i)+270)), display.height()/2 + 9*sin(radians(i)+180), 1);
    display.drawPixel(display.width()/2 + 35*sin(radians((i)+180)), display.height()/2 + 9*sin(radians((i)+90)), 0);

    if(i%4==0){display.display();
    }
  }

  delay(1000);

  display.fillCircle(display.width()/2, display.height()/2, 20, SSD1306_INVERSE);
  display.invertDisplay(1);
  display.display();
  delay(1000);

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(4,44);             // Start at top-left corner
  display.println(F(" by\n  Lukas        Gregor"));

  display.display();

  delay(1000);
  display.invertDisplay(0);

}


void render(){
  display.clearDisplay();
  display.drawCircle(display.width()/4,display.height()/2 , 28, 1);
  display.drawCircle(display.width()*3/4,display.height()/2 , 28, 1);
  display.drawLine(display.width()/4, display.height()/2, display.width()/4 + -28*cos(radians(counter*15+90+(old_counter*15))), display.height()/2 + -28*cos(radians(counter*15+(old_counter*15))), 1);
  display.drawLine(display.width()*3/4, display.height()/2, display.width()*3/4 + -28*cos(radians(motor_position*15+90)), display.height()/2 + -28*cos(radians(motor_position*15)), 1);
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(25,40);             // Start at top-left corner
  display.print(counter*15);
  display.setCursor(90,40);             // Start at top-left corner
  display.print(motor_position*15);
  display.display();
}


void home_screen() {
  render();
  while (true){       
    // Read the current state of CLK
    currentStateCLK = digitalRead(CLK);

    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
      
      // If the DT state is different than the CLK state then
      // the encoder is rotating CCW so decrement
      if (digitalRead(DT) != currentStateCLK) {
        counter --;
        currentDir ="CCW";
      } else {
        // Encoder is rotating CW so increment
        counter ++;
        currentDir ="CW";
      }

      if(counter>12){counter=counter-24;}
      if(counter<-12){counter = counter +24;}

      render();

      delay(1);
/*
      String _s = String(counter);
      display.setTextSize(2);             // Normal 1:1 pixel scale
      display.setCursor(10,10);             // Start at top-left corner
      display.println("counter:");
      display.setTextSize(4);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      if(counter<0){
        display.setCursor(40, 30);
      }
      else{
      display.setCursor(60,30);             // Start at top-left corner
      }
      display.println(_s);
*/
    }


    // Remember last CLK state
    lastStateCLK = currentStateCLK;

    // Read the button state
    int btnState = digitalRead(SW);

    //If we detect LOW signal, button is pressed
    if (btnState == LOW) {
      //if 50ms have passed since last LOW pulse, it means that the
      //button has been pressed, released and pressed again
      if (millis() - lastButtonPress > 50) {
        Serial.println("Button pressed!");
        display.invertDisplay(1);
        display.display();
        digitalWrite(nEnable,LOW);
        stepper.setSpeedInStepsPerSecond(12500);
        stepper.setAccelerationInStepsPerSecondPerSecond(35000);
        stepper.moveRelativeInSteps(int(counter*233.33));
        digitalWrite(nEnable,HIGH);
        display.invertDisplay(0);
        display.display();
        old_counter=counter+old_counter;
        motor_position = motor_position+counter;
        counter = 0;
        render();
      }

      // Remember last button press event
      lastButtonPress = millis();
    }

  delay(1);

  }
}

