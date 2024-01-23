#ifndef _INCLUDE_THROUGHPUTSCANNER_H
#define _INCLUDE_THROUGHPUTSCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getRx_Bytes();
int getTx_Bytes();
int getRxThroughput();
int getTxThroughput();

//prototype function
double getApproxMaxThroughput(double nominalPercentage);

#endif