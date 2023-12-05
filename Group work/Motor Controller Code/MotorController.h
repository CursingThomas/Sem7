#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <stdint.h>
#include <Arduino.h>

enum SETTINGS {
    DIRECTION_PWM,
    SPEED_PWM,
};

class MotorController {
    public:
    MotorController(SETTINGS settings, uint8_t DIR_PWM_PIN, uint8_t SPEED_PWM_PIN);
    void setSpeed(uint8_t speed);
    void changeDir(bool direction, uint8_t speed);

    protected:
    SETTINGS chosen_settings;
    uint8_t speed_pin;
    uint8_t direction_pin;
};

#endif