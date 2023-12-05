#ifndef RADIO_CONTROLLER_H
#define RADIO_CONTROLLER_H

class RadioController {

    public:
    RadioController(int forwardpin, int sidepin);
    void TimerForward();
    void TimerSide();

    int getForwardPulses();
    int getSidePulses();

    protected:
    int forwardPin = 0; //arbitrairy
    int sidePin = 0; //arbitrairy


    volatile long CurrentTimeForward = 0;
    volatile long PulsesForward = 0;
    volatile long StartTimeForward = 0;
    int PulseWidthForward = 0;

    volatile long CurrentTimeSide = 0;
    volatile long PulsesSide = 0;
    volatile long StartTimeSide = 0;
    int PulseWidthSide = 0;
}


#endif 