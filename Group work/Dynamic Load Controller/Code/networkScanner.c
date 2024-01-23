int prev_rx = 0;
int prev_tx = 0;

double getApproxMaxThroughput(double nominalPercentage)
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
  printf("%s", response);
  printf("%s",bitrate);
  char * output;
  double bitrate_int = strtol(bitrate, &output, 10);
  bitrate_int = bitrate_int + 1;
  printf("%f", bitrate_int); 
    if (nominalPercentage != 0 && nominalPercentage <= 100)
    {
        nominalPercentage = nominalPercentage / 100;
    }
printf("%f", (nominalPercentage * bitrate_int));
  return nominalPercentage * bitrate_int;
    
}

int getRx_Bytes()
{
    FILE* ptr;
    int num = 0;
    ptr = fopen("/sys/class/net/lo/statistics/rx_bytes", "r");
    fscanf(ptr, "%d", &num);
    fclose(ptr);

    return num;
}

int getTx_Bytes()
{
    FILE* ptr;
    int num = 0;
    ptr = fopen("/sys/class/net/lo/statistics/tx_bytes", "r");
    fscanf(ptr, "%d", &num);
    fclose(ptr);

    return num;
}

int getRxThroughput()
{   int bytes = getRx_Bytes();
    int negativeFlag = 0;
    if (bytes <= -1)
    {
        bytes = bytes * -1;
        //printf("Bytes switched to a postive number\n");
        negativeFlag = 1;
    }
    if (prev_rx == 0)
    {
        prev_rx = bytes;
        printf("%d", prev_rx);
        return 0;
    }
    else {
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

int getTxThroughput()
{   
    int bytes = getTx_Bytes();
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
    }
    else {
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
