#include <NetworkScanner.h>

int prev_rx = 0;
int prev_tx = 0;
/*
*   As read in the function documentation for retrieving bytes, these are the paths which need to be hardcoded into the program.
*/
const char *rxAdress = "/sys/class/net/lo/statistics/rx_bytes";
const char *txAdress = "/sys/class/net/lo/statistics/tx_bytes";

double GetApproxMaxThroughput(double nominalPercentage)
{
    char response[100];
    char bitrate[10];
    FILE * file = popen("iwlist wlo1 rate", "r");
    int flag = 0;
    while(fgets(response, 100, file) !=NULL && flag < 1)
    {
        flag = flag + 1;
    }

    int charAppender = 0;

    for (int i = 0; response[i]; i++)
    {
        if (isdigit(response[i]))
        {
            bitrate[charAppender] = response[i];
            charAppender = charAppender + 1;
        } else if (response[i] == '.')
        {
            i = 100;
        }
    }

    char * output;
    double bitrate_int = strtol(bitrate, &output, 10);
    bitrate_int = bitrate_int + 1;

    if (nominalPercentage != 0 && nominalPercentage <= 100)
    {
        nominalPercentage = nominalPercentage / 100;
    }
    printf("%f", (nominalPercentage * bitrate_int));

    return nominalPercentage * bitrate_int;
}

int GetRx_Bytes()
{
    FILE* ptr;
    int num = 0;
    ptr = fopen(rxAdress, "r");
    fscanf(ptr, "%d", &num);
    fclose(ptr);

    return num;
}

int GetTx_Bytes()
{
    FILE* ptr;
    int num = 0;
    ptr = fopen(txAdress, "r");
    fscanf(ptr, "%d", &num);
    fclose(ptr);

    return num;
}

int GetRxThroughput()
{   int bytes = GetRx_Bytes();
    int negativeFlag = 0;
    if (bytes <= -1)
    {
        bytes = bytes * -1;
        negativeFlag = 1;
    }
    if (prev_rx == 0)
    {
        prev_rx = bytes;
        printf("%d", prev_rx);

        return 0;
    }else {
        int diff = 0;
        if (negativeFlag == 1)
        {
            diff = prev_rx - bytes;
        } else
        {
            diff = bytes - prev_rx;
        }        
        prev_rx = bytes;

        return diff;
    }
}

int GetTxThroughput()
{   
    int bytes = GetTx_Bytes();
    int negativeFlag = 0;
    if (bytes <= -1)
    {
        bytes = bytes * -1;
        negativeFlag = 1;
    }
    if (prev_tx == 0)
    {
        prev_tx = bytes;

        return 0;
    }else {
        int diff = 0;
        if (negativeFlag == 1)
        {
            diff = prev_tx - bytes;
        } else
        {
            diff = bytes - prev_tx;
        } 
        prev_tx = bytes;

        return diff;
    }
}
