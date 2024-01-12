#ifndef _INCLUDE_DYNAMICLOADSCALER_H
#define _INCLUDE_DYNAMICLOADSCALER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "logger.h"

int getUsagePercentage(int threshold, int amountOfBytes);
int setQuality(int quality);
int addQuality(int quality);
int subtractQuality(int quality);
int setAdaptiveScalingModifyer(int usagepercentage, int threshold);
int selectScalingModifyerHalf(int usagepercentage);

#endif