
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

int motor_position = 0;
int counter = 0;
int old_counter = counter;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;


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

  display.draw

  display.display();
}

}
