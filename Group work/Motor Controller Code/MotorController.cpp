#include "MotorController.h"

MotorController::MotorController(SETTINGS settings, uint8_t DIR_PWM_PIN, uint8_t SPEED_PWM_PIN)
{
    chosen_settings = settings;
    direction_pin = DIR_PWM_PIN;
    speed_pin = SPEED_PWM_PIN;
    

    pinMode(direction_pin, OUTPUT);
    pinMode(speed_pin, OUTPUT);
    
    digitalWrite(direction_pin, LOW);
    digitalWrite(speed_pin, LOW);

}

void MotorController::setSpeed(uint8_t speed)
{
    if(speed > 255)
    {
        speed = 255;
    }

    analogWrite(speed_pin, speed);
}

void MotorController::changeDir(bool direction, uint8_t speed);
{
    if (direction == 0)
    {
        digitalWrite(direction_pin, LOW);
        setSpeed(speed);
    }
    if (direction == 1)
    {
        digitalWrite(direction_pin, LOW);
        setSpeed(speed);
    }
}
