#include "RadioController.h"

RadioController::RadioController(int forwardpin, int sidepin)
{
    forwardPin = forwardpin;
    sidePin = sidepin;

    pinMode(forwardPin, INPUT_PULLUP);
    pinMode(sidePin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(forwardPin),TimerForward,CHANGE);
    attachInterrupt(digitalPinToInterrupt(sidePin),TimerSide,CHANGE);
}

void RadioController::TimerForward()
{
    CurrentTimeForward = micros();
    if (CurrentTimeForward > StartTimeForward){
        PulsesForward = (CurrentTimeForward - StartTimeForward);
        StartTimeForward = CurrentTimeForward;
    }
}

void RadioController::TimerSide()
{
    CurrentTimeSide = micros();
    if (CurrentTimeSide > StartTimeSide){
        PulsesSide = (CurrentTimeSide - StartTimeSide);
        StartTimeSide = CurrentTimeSide;
    }
}

int RadioController::getForwardPulses()
{
    if (PulsesForward < 2000)
    {
        PulseWidthForward = PulsesForward;
        return PulseWidthForward;
    }

}

int RadioController::getSidePulses()
{
    if (PulsesSide < 2000)
    {
        PulseWidthSide = PulsesSide;
        return PulseWidthSide;
    }

}