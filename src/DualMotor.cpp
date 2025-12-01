#include "DualMotor.h"

DualMotor::DualMotor() {}

DualMotor::DualMotor(uint8_t standbyP, uint8_t pwmM1P, uint8_t outM1aP, uint8_t outM1bP, uint8_t pwmM2P, uint8_t outM2aP, uint8_t outM2bP)
    : standbyPin(standbyP), pwmPinM1(pwmM1P), outPinM1a(outM1aP), outPinM1b(outM1bP), pwmPinM2(pwmM2P), outPinM2a(outM2aP), outPinM2b(outM2bP)
      {
        _standby = _inactive;
        dirM1Indicator = _coast; 
        dirM2Indicator = _coast; 
        speedM1 = 0; speedM2 = 0; 
        invertM1 = false; 
        invertM2 = true;    
    }

void DualMotor::begin() 
{
    pinMode(standbyPin, OUTPUT);
    pinMode(pwmPinM1, OUTPUT);
    pinMode(outPinM1a, OUTPUT);
    pinMode(outPinM1b, OUTPUT);
    pinMode(pwmPinM2, OUTPUT);
    pinMode(outPinM2a, OUTPUT);
    pinMode(outPinM2b, OUTPUT);

    setStandby(_inactive);
    brake(_both);
}

void DualMotor::setStandby(_MODE mode) 
{
    _standby = mode;
    digitalWrite(standbyPin, mode == _active ? LOW : HIGH);
}

_MODE DualMotor::getStandby() 
{
    return static_cast<_MODE>(_standby);
}

void DualMotor::setInverted(_motor M, bool invert) 
{
    if (M == _M1 || M == _both) invertM1 = invert;
    if (M == _M2 || M == _both) invertM2 = invert;
}

void DualMotor::brake(_motor M) 
{
    setDirection(M, _brake);
    setSpeed(M, 0);
}

void DualMotor::coast(_motor M) 
{
    setDirection(M, _coast);
    setSpeed(M, 0);
}

void DualMotor::setDirection(_motor M, char direction) 
{
    DIR_TYPE dir = _COAST;

    switch (M)
    {
        case _M1:
          switch(direction)
            {
                case _forward:
                    dirM1Indicator = _forward;

                    if (invertM1) dirM1 = _REVERSE;
                    else dirM1 = _FORWARD;

                    break;

                case _reverse:
                    dirM1Indicator = _reverse;
                    
                    if (invertM1) dirM1 = _FORWARD;
                    else dirM1 = _REVERSE;
                    
                    break;

                case _brake:
                    dirM1 = _BRAKE;
                    break;

                case _coast:
                    dirM1 = _COAST;
                    break;

                default:
                    break;
            }

        case _M2:
            switch(direction)
            {
                case _forward:
                    dirM2Indicator = _forward;

                    if (invertM2) dirM2 = _REVERSE;
                    else dirM2 = _FORWARD;

                    break;

                case _reverse:
                    dirM2Indicator = _reverse;
                    
                    if (invertM2) dirM2 = _FORWARD;
                    else dirM2 = _REVERSE;
                    
                    break;

                case _brake:
                    dirM2 = _BRAKE;
                    break;

                case _coast:
                    dirM2 = _COAST;
                    break;

                default:
                    break;
                    
            }

        case _both:
             setDirection(_M1, direction); 
             setDirection(_M2, direction); 
        
            break;

        default:
            break;

    }

    applySettings(M);
}

char DualMotor::getDirection(_motor M) 
{
    if (M == _M1) return dirM1Indicator;
    if (M == _M2) return dirM2Indicator;
    return _crossed;
}

void DualMotor::setSpeed(_motor M, int speed) 
{
    speed = constrain(speed, -255, 255);
    if (M == _M1 || M == _both) speedM1 = abs(speed);
    if (M == _M2 || M == _both) speedM2 = abs(speed);
    applySettings(M);
}

uint8_t DualMotor::getSpeed(_motor M, int speed) 
{
    if (M == _M1) return speedM1;
    if (M == _M2) return speedM2;
    return (speedM1 + speedM2) / 2;
}

void DualMotor::setDirSpeed(_motor M, char direction, int speed) 
{
    setDirection(M, direction);
    setSpeed(M, speed);
}

void DualMotor::getDirSpeed(_motor M, char &direction, int &speed) 
{
    if (M == _M1) {
        direction = dirM1Indicator;
        speed = speedM1;
    } else if (M == _M2) {
        direction = dirM2Indicator;
        speed = speedM2;
    }
}

void DualMotor::applySettings(_motor M) 
{
    setStandby(_inactive); //Ensure the driver is inactive before applying settings.
    if (M == _M1 || M == _both) {
        digitalWrite(outPinM1a, dirM1._a);
        digitalWrite(outPinM1b, dirM1._b);
        analogWrite(pwmPinM1, speedM1);
    }
    if (M == _M2 || M == _both) {
        digitalWrite(outPinM2a, dirM2._a);
        digitalWrite(outPinM2b, dirM2._b);
        analogWrite(pwmPinM2, speedM2);
    }
    setStandby(_active); //Reactivate the driver after applying settings.
}
