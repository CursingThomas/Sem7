#ifndef _INCLUDE_DYNAMICLOADSCALER_H
#define _INCLUDE_DYNAMICLOADSCALER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/*
*   Calculates the percentage of bandwidth usage of the stream according to a threshold the user determined. 
*   Parameters:
*
*   -	threshold
*   The allowed bandwidth usage in percentages.
*
*   Min-max value:
*   1- 100.
*
*   -	amountOfBytes
*   The amount of bytes per second.
*
*   Min-max value: 
*   0 – INT_MAX
*/
int GetUsagePercentage(int threshold, int amountOfBytes);

/*
*   Sets a different quality preset in the encoder configuration to down or upscale the current quality of the stream.
*   Parameters:
*   -	quality
*   The given (new) quality to update in the encoder configuration.
*
*   Min-max value: 
*   0 - 100.
*/
int SetQuality(int quality, struct context **list);

/*
*   Adds the specified amount of percentages to the current encoder configuration. 
*   If by addition, the quality exceeds 100; the quality will be set to 100.
*
*   Parameters:
*   -	quality
*   The amount of percentages which should be added to the current encoder configuration for stream quality.
*
*   Min-max value: 
*   0 - 100.
*/
int AddQuality(int quality, struct context **list);

/*
*   Subtracts the specified amount of percentages to the current encoder configuration. 
*   If by subtraction, the quality goes under 0; the quality will be set to 0.
*
*   Parameters:
*   -	quality
*   The amount of percentages which should be added to the current encoder configuration for stream quality.
*
*   Min-max value: 
*   0 - 100.
*/
int SubtractQuality(int quality, struct context **list);

/*
*   Part of the control loop, ensures that the bandwidth usage hovers around the given threshold. 
*   We cannot make this exact, since various factors influence bandwidth; 
*   some which are out of our control.
*
*   Parameters:
*   -	usagePercentage
*   The amount of percentages the current stream draws on the system. This value is retrieved from the network scanner, 
*   which calculates this usage percentage agains another threshold.
*
*   Min-max value: 
*   0 - 100.
*
*   -	threshold
*   The threshold which the control loop aims to hover at in percentages. 
*   Given 25, the system aims to keep the network usage 25% of the threshold stated by the network scanner.
*
*   Min-max value:
*   0 – 100.
*/
int SetAdaptiveScalingModifyer(int usagepercentage, int threshold, struct context **list);

/*
*   Part of the control loop, ensures that the bandwidth usage hovers around 50%. 
*   This 50% is hardcoded. We cannot make this exact, since various factors influence bandwidth; 
*   some which are out of our control. 
*   The 50% is on purpose, since it provides an easy testing point.
*
*   Parameters:
*   -	usagePercentage
*   The amount of percentages the current stream draws on the system. This value is retrieved from the network scanner, 
*   which calculates this usage percentage agains another threshold.
*
*   Min-max value: 
*   0 - 100.
*/
int SelectScalingModifyerHalf(int usagepercentage, struct context **list);

/*
*   Provides controller logic for a P controller. 
*   This is the final and suggested implementation of control logic into the system; 
*   even though other options are provided.
*
*   Parameters:
*   -	SP
*   Abbreviation for setpoint. The threshold which the control loop aims to hover at in percentages. 
*   Given 25, the system aims to keep the network usage 25% of the threshold stated by the network scanner.
*
*   Min-max value: 
*   0 - 100.
*
*   -	Kp
*   Value to give P. Otherwise often mentioned as gain. This value should be found by tuning the p controller. We advise 0.2
*
*   Min-max value:
*   INT_MIN – INT_MAX
*   -	Current
*   The amount of percentages the current stream draws on the system. This value is retrieved from the network scanner, 
*   which calculates this usage percentage agains another threshold.
*
*   Min-max value: 
*   0 - 100.
*/
int PControll(int SP, double Kp, int current);

#endif
