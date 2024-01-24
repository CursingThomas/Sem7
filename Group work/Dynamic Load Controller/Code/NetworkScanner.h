#ifndef _INCLUDE_THROUGHPUTSCANNER_H
#define _INCLUDE_THROUGHPUTSCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
*   Reads network adapter register of Rx Bytes for the hardcoded network adapter. 
*   In our case, we want to use a local network so we use the “lo” prefix. 
*   This needs to be configured in code and built for every machine.
*/
int GetRx_Bytes();

/*
*   Reads network adapter register of Tx Bytes for the hardcoded network adapter. 
*   In our case, we want to use a local network so we use the “lo” prefix. 
*   This needs to be configured in code and built for every machine.
*/
int GetTx_Bytes();

/*
*   Calculates the difference between two separate readings of the Rx_bytes register. 
*   Like mentioned above, these registers can be negative; 
*   that means this class is responsible for handling this data correctly.
*/
int GetRxThroughput();

/*
*   Calculates the difference between two separate readings of the Tx_bytes register. 
*   Like mentioned above, these registers can be negative; 
*   that means this class is responsible for handling this data correctly.
*/
int GetTxThroughput();

/*
*   prototype function
*   According to a nominal percentage value of the bitrate from the network adapter, 
*   tries to calculate a suggestive threshold to limit the system to.
*
*   Parameters:
*
*   -	nominalPercentage
*   The nominal percentage given by a reliable source to approach the optimum threshold with.
*
*   Min-max:
*   0 – 100.
*/
double GetApproxMaxThroughput(double nominalPercentage);

#endif
