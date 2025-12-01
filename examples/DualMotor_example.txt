// DualMotor_example.ino        

#include <Arduino.h>
//
#include "DualMotor.h"

DualMotor motors(  5,   //Standby Pin
                    18,  //PWM Motor 1 Pin
                    19,  //Output Motor 1a Pin
                    21,  //Output Motor 1b Pin
                    22,  //PWM Motor 2 Pin
                    23,  //Output Motor 2a Pin
                    25); //Output Motor 2b Pin
                    
void setup() 
{
    Serial.begin(115200);
    delay(1000);


    Serial.println("Setup complete");
}
    
void loop() 
{
    // Your code here
}