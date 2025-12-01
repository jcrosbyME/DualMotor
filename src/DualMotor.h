//DualMotor.h

//Developer: John J. Crosby
//E-Mail: jjc@maine.rr.com
//Copywrite 2013 John J. Crosby

#ifndef DUALMOTOR_H
#define DUALMOTOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
;;#include <Program.h>
#include <pins_ardiuono.h>
#endif

const char _forward = 'F';  //Forward directon Indicator
const char _reverse = 'R';  //Reverse direction Indicator
const char _stop    = 'S';  //Stop Indicator
const char _brake   = 'B';  //Brake Indicator
const char _coast   = 'C';  //Coast Indicator
const char _crossed = 'X';  //Crossed Indicator

enum _MODE 
{
    _active = 0,
    _inactive = 1
};

enum _motor 
{
    _both = 0,
    _M1 = 1,
    _M2 = 2
};

typedef struct _DIR
{
    uint8_t _a;
    uint8_t _b;
} DIR_TYPE;



class DualMotor {
public:
    DualMotor();

    DualMotor( uint8_t standbyP, uint8_t pwmM1P, uint8_t outM1aP, uint8_t outM1bP, uint8_t pwmM2P, uint8_t outM2aP, uint8_t outM2bP);

    void begin();

    void setStandby(_MODE mode);    //Set the Standby Mode, _active ('0') or _inactive ('1').
    _MODE getStandby();             //Get the current Standby Mode, _active or _inactive.

    void setInverted(_motor M, bool invert); //Set inversion of motor direction. true = inverted, false = normal.

    void brake(_motor M);
    void coast(_motor M);

    void setDirection(_motor M, char direction);
    char getDirection(_motor M);

    void setSpeed(_motor M, int speed); // Speed range: -255 to 255
    uint8_t getSpeed(_motor M, int speed); // Speed range: -255 to 255. If _both motors are selected, the average speed is returned.

    void setDirSpeed(_motor M, char direction, int speed);       //Sets both direction ('F' or 'R') and speed (0-255). 
    void getDirSpeed(_motor M, char &direction, int &speed);    //Gets both direction ('F' or 'R') and speed (0-255). _both motors will not be supported. 

private:
    uint8_t standbyPin;         //Digital Output Pin that corresponds to the Standby function Input of the Motor Driver.

    uint8_t pwmPinM1;           //PWM Output Pin that corresponds to the PWM Input of Motor 1 of the Motor Driver.
    uint8_t outPinM1a;          //Digital Output Pin that corresponds to the Direction A Input of Motor 1 of the Motor Driver.
    uint8_t outPinM1b;          //Digital Output Pin that corresponds to the Direction B Input of Motor 1 of the Motor Driver.
    
    uint8_t pwmPinM2;           //PWM Output Pin that corresponds to the PWM Input of Motor 2 of the Motor Driver.
    uint8_t outPinM2a;          //Digital Output Pin that corresponds to the Direction A Input of Motor 2 of the Motor Driver.
    uint8_t outPinM2b;          //Digital Output Pin that corresponds to the Direction B Input of Motor 2 of the Motor Driver.

    uint8_t _standby;          //Current Standby Mode of the Motor Driver.

    char dirM1Indicator;        //Current Direction Indicator of Motor 1. Stored as char.
    DIR_TYPE dirM1;             //Current Direction of Motor 1. Stored as DIR_TYPE struct.
    uint8_t speedM1;            //Current Speed of Motor 1.

    char dirM2Indicator;        //Current Direction Indicator of Motor 2. Stored as char.
    DIR_TYPE dirM2;             //Current Direction of Motor 2. Stored as DIR_TYPE struct.
    uint8_t speedM2;            //Current Speed of Motor 2.
    
    DIR_TYPE _FORWARD = {HIGH, LOW};
    DIR_TYPE _REVERSE = {LOW, HIGH};
    DIR_TYPE _BRAKE   = {HIGH, HIGH};
    DIR_TYPE _COAST   = {LOW, LOW};

    bool invertM1;           //Inversion flag for Motor 1 direction.
    bool invertM2;           //Inversion flag for Motor 2 direction.

    void applySettings(_motor M);
    
};

#endif // DUALMOTOR_H

