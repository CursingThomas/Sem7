#include <DynamicLoadSaler.h>

int GetUsagePercentage(int threshold, int amountOfBytes)
{
    // all data is in bytes
    if (threshold <= 0)
    {
        // cannot devide by zero and cannot be smaller than 1
        return -1;
    }

    return ((amountOfBytes * 100) / threshold);
}

int SetQuality(int quality, struct context **list)
{
    if (quality < 0 || quality > 100 )
    {
        //0-100 is permitted range
        return -1;
    }
    for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
    {
        list[i]->conf.stream_quality = quality;
    }

    return 1;
}

int AddQuality(int quality, struct context **list)
{
    int currQuality = 0;
    if (quality < 0 || quality > 100 )
    {
        //0-100 is permitted range
        return -1;
    }
    for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
    {
        if ((list[i]->conf.stream_quality) >= 100)
        {
            // quality cannot be over 100 defaulted to 0
            list[i]->conf.stream_quality = 100;
            return -1;
        }

        currQuality= (list[i]->conf.stream_quality  + quality);
        list[i]->conf.stream_quality  = currQuality;
    }

    return 1;
}

int SubtractQuality(int quality, struct context **list)
{
    int currQuality = 0;
    if (quality < 0 || quality > 100 )
    {
        //0-100 is permitted range
        return -1;
    }
    for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
    {
        if ((list[i]->conf.stream_quality - quality) < 0)
        {
            // quality cannot be negative defaulted to 0

            list[i]->conf.stream_quality = 0;
            return -1;
        }

        currQuality = (list[i]->conf.stream_quality - quality);
        list[i]->conf.stream_quality = currQuality;
    }

    return 1;
}

int SetAdaptiveScalingModifyer(int usagepercentage, int threshold, struct context **list)
{
    int subtractionFlag = 0;
    if (threshold < 0 || threshold > 100)
    {
        // out of bounds
        return -1;
    }
    int difference = threshold - usagepercentage;
    if (difference < 0)
    {
        subtractionFlag = 1;
        difference = difference * -1;
    }
    if (difference > 100)
    {
        if (subtractionFlag)
        {
            setQuality(10, list);
        }else{
            setQuality(50, list);
        }

        return 1;        
    }
    if (difference <= 100 && difference >= 90)
    {
        if (subtractionFlag)
        {
            subtractQuality(10, list);
        }else{
            addQuality(10, list);
        }

        return 1;        
    }
    if (difference <= 89 && difference >= 80)
    {
        if (subtractionFlag)
        {
            subtractQuality(9, list);
        }else{
            addQuality(9, list);
        }

        return 1;        
    }
    if (difference <= 79 && difference >= 70)
    {
        if (subtractionFlag)
        {
            subtractQuality(8, list);

        }else{
            addQuality(8, list);
        }

        return 1;        
    }
    if (difference <= 69 && difference >= 60)
    {
        if (subtractionFlag)
        {
            subtractQuality(7, list);
        }else{
            addQuality(7, list);
        }

        return 1;        
    }
    if (difference <= 59 && difference >= 50)
    {
        if (subtractionFlag)
        {
            subtractQuality(6, list);
        }else{
            addQuality(6, list);
        }

        return 1;        
    }
    if( difference <= 49 && difference >= 40)
    {
        if (subtractionFlag)
        {
            subtractQuality(5, list);
        }else{
            addQuality(5, list);
        }

        return 1;        
    }
    if (difference <= 39 && difference >= 30)
    {
        if (subtractionFlag)
        {
            subtractQuality(4, list);
        }else{
            addQuality(4, list);
        }

        return 1;        
    }
    if (difference <= 29 && difference >= 20)
    {
        if (subtractionFlag)
        {
            subtractQuality(3, list);
        }else{
            addQuality(3, list);
        }

        return 1;        
    }

    if (difference <= 19 && difference >= 10)
    {
        if (subtractionFlag)
        {
            subtractQuality(2, list);
        }else{
            addQuality(2, list);
        }

        return 1;        
    }
    if (difference <= 9 && difference >= 0)
    {
        if (subtractionFlag)
        {
            subtractQuality(1, list);
        }else{
            addQuality(1, list);
        }

        return 1;        
    }
}

int SelectScalingModifyer(int usagepercentage, struct context **list)
{
    // scaling in 10% increments
    if (usagepercentage >= 0 && usagepercentage <= 10)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality + 20);
        }
        return 1;
    }
    else if (usagepercentage >= 11 && usagepercentage <= 20)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality + 15);
        }
        return 2;
    }
    else if (usagepercentage >= 21 && usagepercentage <= 30)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {   
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality + 10);            
        }
        return 3;
    }
    else if (usagepercentage >= 31 && usagepercentage <= 40)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality + 5);
        }
        return 4;
    }
    else if (usagepercentage >= 41 && usagepercentage <= 50)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality + 1); 
        }
        return 5;
    }
    else if (usagepercentage >= 51 && usagepercentage <= 60)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality - 1);
        }
        return 6;
    }
    else if (usagepercentage >= 61 && usagepercentage <= 70)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality - 5);
        }
        return 7;
    }
    else if (usagepercentage >= 71 && usagepercentage <= 80)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality - 10);
        }
        return 8;
    }
    else if (usagepercentage >= 81 && usagepercentage <= 90)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality - 15);
        }
        return 9;
    }
    else if (usagepercentage >= 91 && usagepercentage <= 100)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = (list[i]->conf.stream_quality - 20);
        }
        return 10;
    }
    else if (usagepercentage >= 100)
    {
        for (int i = (list[1] != NULL ? 1 : 0); list[i]; i++)
        {
            list[i]->conf.stream_quality = 10;
        }
        return 11;
    }

    return -1;
}

int PControll(int SP, double Kp, int current)
{
    int adjust = SP - current;
    double x = adjust  * Kp;

    return ceil(x);
}
