#include <SpeedyStepper.h>


//
// pin assignments
//
const int LED_PIN = 13;
const int MOTOR_STEP_PIN = 3;
const int MOTOR_DIRECTION_PIN = 2;


//
// create the stepper motor object
//
SpeedyStepper stepper;



void setup() 
{
  //
  // setup the LED pin and enable print statements
  //
  pinMode(LED_PIN, OUTPUT);   
  Serial.begin(9600);


  //
  // connect and configure the stepper motor to its IO pins
  //
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
}



void loop() 
{
  //
  // Here will will try rotating at faster and faster speeds.  You can
  // see how the motor's torque is reduced as the speed increases by
  // pinching the shaft with your fingers.  Note: When the motor can't
  // go at the commanded speed, it simply stops.
  //
  // I have conducted all of these tests with 1x microstepping.
  //

  //
  // 100 steps/second
  //
  Serial.println("Testing 100 steps/second.");
  stepper.setSpeedInStepsPerSecond(12500);
  stepper.setAccelerationInStepsPerSecondPerSecond(40000);
  stepper.moveRelativeInSteps(4000);
  delay(100);
  stepper.moveRelativeInSteps(-4000);
  delay(100);
  /*
  //
  // 200 steps/second
  //
  Serial.println("Testing 200 steps/second.");
  stepper.setSpeedInStepsPerSecond(200);
  stepper.setAccelerationInStepsPerSecondPerSecond(800);
  stepper.moveRelativeInSteps(400);
  delay(800);

  //
  // 400 steps/second
  //
  Serial.println("Testing 400 steps/second.");
  stepper.setSpeedInStepsPerSecond(400);
  stepper.setAccelerationInStepsPerSecondPerSecond(800);
  stepper.moveRelativeInSteps(800);
  delay(800);

  //
  // 800 steps/second
  // Note: My 12V NEAMA 17 motor with a 20V power supply stops here
  //
  Serial.println("Testing 800 steps/second.");
  stepper.setSpeedInStepsPerSecond(800);
  stepper.setAccelerationInStepsPerSecondPerSecond(800);
  stepper.moveRelativeInSteps(1600);
  delay(800);

  //
  // 1600 steps/second
  //
  Serial.println("Testing 1600 steps/second.");
  stepper.setSpeedInStepsPerSecond(1600);
  stepper.setAccelerationInStepsPerSecondPerSecond(1600); 
  stepper.moveRelativeInSteps(3200);
  delay(800);

  //
  // 3200 steps/second
  //
  Serial.println("Testing 3200 steps/second.");
  stepper.setSpeedInStepsPerSecond(3200);
  stepper.setAccelerationInStepsPerSecondPerSecond(3200); 
  stepper.moveRelativeInSteps(6400);
  delay(800);

  //
  // 6400 steps/second
  // Note: My 3.2V NEAMA 17 motor with a 20V power supply stops here
  //
  Serial.println("Testing 6400 steps/second.");
  stepper.setSpeedInStepsPerSecond(6400);
  stepper.setAccelerationInStepsPerSecondPerSecond(6400); 
  stepper.moveRelativeInSteps(12800);
  delay(800);

  //
  // 12500 steps/second, the fastest this library can generate
  // Note: My 3.8V NEAMA 11 motor with a 20V power supply stops here
  //
  Serial.println("Testing 12500 steps/second.");
  stepper.setSpeedInStepsPerSecond(12500);
  stepper.setAccelerationInStepsPerSecondPerSecond(6400);
  stepper.moveRelativeInSteps(38400);
  delay(800);

  Serial.println("");  
  delay(3000);
  */
}