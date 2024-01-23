#ifndef _INCLUDE_DYNAMICLOADSCALER_H
#define _INCLUDE_DYNAMICLOADSCALER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int GetUsagePercentage(int threshold, int amountOfBytes);
int SetQuality(int quality, struct context **list);
int AddQuality(int quality, struct context **list);
int SubtractQuality(int quality, struct context **list);
int SetAdaptiveScalingModifyer(int usagepercentage, int threshold, struct context **list);
int SelectScalingModifyerHalf(int usagepercentage, struct context **list);
int PControll(int SP, double Kp, int current);

#endif