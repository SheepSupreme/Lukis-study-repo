
//  Author:     Lukas Gregor
//  Date:       23.07.2023
//  Title:      1_axis_belt_drive
//  Iteration:  V1.0

#include <SpeedyStepper.h>
SpeedyStepper stepper;

// SSD1306
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       // Root library
#include <Adafruit_SSD1306.h>   // Library for using a specific display

#define nEnable 9
#define CLK 8
#define DT 7
#define SW 6

int calibration_sequence = 0;
int pos_max;
int motor_position = 0;
int8_t counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;
static uint8_t prevNextCode = 0;
static uint16_t store=0;


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
  pinMode(CLK, INPUT);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT);
  pinMode(DT, INPUT_PULLUP);
	pinMode(SW, INPUT_PULLUP);
  pinMode(nEnable,OUTPUT);

	// Setup Serial Monitor
	Serial.begin(9600);
  digitalWrite(nEnable,HIGH);

  //Stepper speed
  stepper.setSpeedInStepsPerSecond(16000);
  stepper.setAccelerationInStepsPerSecondPerSecond(250000);

	// Read the initial state of CLK
	lastStateCLK = digitalRead(CLK);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  saturn_animation();
  display.display();
  calibration();
  control();
}

void loop() {
  // put your main code here, to run repeatedly:
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


void calibration_image(){
  display.clearDisplay();

  if (calibration_sequence == 0){
    display.drawCircle(32, 32, 24, 1);
    display.drawCircle(96, 32, 24, 1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(25, 30);
    display.println(counter);
  }
  else if(calibration_sequence == 1){
    display.fillCircle(32, 32, 24, 1);
    display.drawCircle(96, 32, 24, 1);
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(25, 30);
    display.println(pos_max);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(75, 30);
    display.println(counter);
  }
  else if(calibration_sequence == 2){
    display.fillCircle(32, 32, 24, 1);
    display.fillCircle(96, 32, 24, 1);
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(20, 25);
    display.println(pos_max);
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(85, 25);
  }
  display.display();
}

void calibration(){
  display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);
  calibration_image();
  static int8_t val;
  while (calibration_sequence <2){
    
    if( val=read_rotary() ) {
      counter +=val;
      calibration_image();
      digitalWrite(nEnable,LOW);
      stepper.moveRelativeInSteps(val*200);
      digitalWrite(nEnable,HIGH);
   }

    /*currentStateCLK = digitalRead(CLK);
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
      if (digitalRead(DT) != currentStateCLK) {
        counter --;
        calibration_image();
        currentDir ="CCW";
        digitalWrite(nEnable,LOW);
        stepper.moveRelativeInSteps(-200);
        digitalWrite(nEnable,HIGH);
      
      } else {
        counter ++;
        calibration_image();
        currentDir ="CW";
        digitalWrite(nEnable,LOW);
        stepper.moveRelativeInSteps(200);
        digitalWrite(nEnable,HIGH);
      }
      Serial.println(counter);
    }*/
    
    lastStateCLK = currentStateCLK;
    int btnState = digitalRead(SW);

    if (btnState == LOW) {
      //if 50ms have passed since last LOW pulse, it means that the
      //button has been pressed, released and pressed again
      if (millis() - lastButtonPress > 50) {
        Serial.println("Button pressed!");
        if (calibration_sequence == 0){
          Serial.println("Minimal Position set to ");
          Serial.print(counter);
          counter = 0;
        }
        if (calibration_sequence == 1){
          Serial.println("Maximal Position set to ");
          Serial.print(counter);
          pos_max = counter;
          motor_position = counter;
        }
      calibration_sequence += 1;
      }

      // Remember last button press event
      lastButtonPress = millis();
      calibration_image();
    }
  }
  Serial.println(F("Calibration end"));
}

void control(){
  Serial.println(F("Control start"));
  display.setTextSize(3);             // Normal 1:1 pixel scale
  control_image();
  static int8_t val;
  while (true){
    
    if( val=read_rotary() ) {
      if (val > 0 && counter < pos_max){
        counter +=val;
      }
      else if (val < 0 && counter > 0){
        counter +=val;
      }
      control_image();
   }
    
    /*currentStateCLK = digitalRead(CLK);
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
      if (digitalRead(DT) != currentStateCLK && counter > 0) {
        counter --;
        control_image();
        currentDir ="CCW";
      } else if (digitalRead(DT) == currentStateCLK && counter < pos_max){
        counter ++;
        control_image();
        currentDir ="CW";
      }
      Serial.println(counter);
    }*/
    
    lastStateCLK = currentStateCLK;
    int btnState = digitalRead(SW);

    if (btnState == LOW) {
      int8_t relative_movement = counter - motor_position;
      if (relative_movement != 0){
        motor_position = counter;
        control_image();
        digitalWrite(nEnable,LOW);
        stepper.moveRelativeInSteps((relative_movement)*200);
        digitalWrite(nEnable,HIGH);
      }   
    }    
  }
}

void control_image(){
  display.clearDisplay();
  display.drawRect(0, 0, display.width(), 20, 1);
  display.fillRect(0, 0,float (motor_position)/float (pos_max)*127, 20, 1);
  display.drawLine(float (counter)/float (pos_max)*127, 0,float (counter)/float (pos_max)*127, 25, 1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,40);
  display.println(motor_position);
  display.display();
}

int8_t read_rotary() {
  static int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

  prevNextCode <<= 2;
  if (digitalRead(DT)) prevNextCode |= 0x02;
  if (digitalRead(CLK)) prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table[prevNextCode] ) {
      store <<= 4;
      store |= prevNextCode;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store&0xff)==0x2b) return -1;
      if ((store&0xff)==0x17) return 1;
   }
   return 0;
}
