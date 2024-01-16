#include "dynamicLoadScaler.h"

int getUsagePercentage(int threshold, int amountOfBytes)
{
    // all data is in bytes
    if (threshold == 0 || threshold > 100)
    {
        // cannot devide by zero or exceed 100 percent
        return -1;
    }

    return ((amountOfBytes * 100) / threshold);
}

int setQuality(int quality)
{
    if (quality < 0 || quality > 100 )
    {
        //0-100 is permitted range
        return -1;
    }
    for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
    {
        cnt_list[i]->conf.stream_quality = quality;
    }

    return 1;

}

int addQuality(int quality)
{
    int currQuality = 0;
    if (quality < 0 || quality > 100 )
    {
        //0-100 is permitted range
        return -1;
    }
    for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
    {
        currQuality= (cnt_list[i]->conf.stream_quality + quality);
        if (currQuality > 100)
        {
            // quality cannot be over 100 defaulted to 100
            setQuality(100);
            return -1;
        }

        setQuality(currQuality);
    }
    MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("quality added by: %d"),  quality);

    MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("quality is now: %d"),  currQuality);

    return 1;

}

int subtractQuality(int quality)
{
    int currQuality = 0;
    if (quality < 0 || quality > 100 )
    {
        //0-100 is permitted range
        return -1;
    }
    for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
    {
        currQuality = (cnt_list[i]->conf.stream_quality - quality);
        if (currQuality < 0)
        {
            // quality cannot be negative defaulted to 0
            setQuality(0);
            return -1;
        }
        
        setQuality(currQuality);
    }
    MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("quality subtracted by: %d"),  quality);

    MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("quality is now: %d"),  currQuality);

    return 1;

}

int setAdaptiveScalingModifyer(int usagePercentage, int threshold)
{
    int subtractionFlag = 0;
    if (threshold < 0 || threshold > 100)
    {
        // out of bounds
        return -1;
    }
    int difference = threshold - usagePercentage;
    if (difference < 0)
    {
        subtractionFlag = 1;
        difference = difference * -1;
    }
    MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff: %d\n"), difference);

        if(difference > 100)
    {
        if (subtractionFlag)
        {
            setQuality(10);
        }else{
            setQuality(50);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff > 100\n"));
        return 1;        
    }

    if(difference <= 100 && difference >= 90)
    {
        if (subtractionFlag)
        {
            subtractQuality(10);
        }else{
            addQuality(10);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 100 - 90\n"));
        return 1;        
    }

        if(difference <= 89 && difference >= 80)
    {
        if (subtractionFlag)
        {
            subtractQuality(9);
        }else{
            addQuality(9);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 89 - 80\n"));
        return 1;        
    }

        if(difference <= 79 && difference >= 70)
    {
        if (subtractionFlag)
        {
            subtractQuality(8);
            MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("dsub\n"));
        }else{
            addQuality(8);
            MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("att\n"));
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 79 - 70\n"));
        return 1;        
    }

        if(difference <= 69 && difference >= 60)
    {
        if (subtractionFlag)
        {
            subtractQuality(7);
        }else{
            addQuality(7);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 69 - 60\n"));
        return 1;        
    }

        if(difference <= 59 && difference >= 50)
    {
        if (subtractionFlag)
        {
            subtractQuality(6);
        }else{
            addQuality(6);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 59 - 50\n"));
        return 1;        
    }

        if(difference <= 49 && difference >= 40)
    {
        if (subtractionFlag)
        {
            subtractQuality(5);
        }else{
            addQuality(5);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 49 - 40\n"));
        return 1;        
    }

        if(difference <= 39 && difference >= 30)
    {
        if (subtractionFlag)
        {
            subtractQuality(4);
        }else{
            addQuality(4);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 39 - 30\n"));
        return 1;        
    }

        if(difference <= 29 && difference >= 20)
    {
        if (subtractionFlag)
        {
            subtractQuality(3);
        }else{
            addQuality(3);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 29 - 20\n"));
        return 1;        
    }

        if(difference <= 19 && difference >= 10)
    {
        if (subtractionFlag)
        {
            subtractQuality(2);
        }else{
            addQuality(2);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 19 - 10\n"));
        return 1;        
    }
        if(difference <= 9 && difference >= 0)
    {
        if (subtractionFlag)
        {
            subtractQuality(1);
        }else{
            addQuality(1);
        }
        MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,_("diff 10 - 0\n"));
        return 1;        
    }
}

int selectScalingModifyerHalf(int usagePercentage)
{
    // scaling in 10% increments
    if (usagePercentage >= 0 && usagePercentage <= 10)
    {
        // scale down to x
        //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality + 20);
        }
        return 1;
    }
    else if (usagePercentage >= 11 && usagePercentage <= 20)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality + 15);
        }
        return 2;
    }
    else if (usagePercentage >= 21 && usagePercentage <= 30)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {   
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality + 10);            
        }
        return 3;
    }
    else if (usagePercentage >= 31 && usagePercentage <= 40)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality + 5);
        }
        return 4;
    }
    else if (usagePercentage >= 41 && usagePercentage <= 50)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality + 1); 
        }
        return 5;
    }
    else if (usagePercentage >= 51 && usagePercentage <= 60)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality - 1);
        }
        return 6;
    }
    else if (usagePercentage >= 61 && usagePercentage <= 70)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality - 5);
        }
        return 7;
    }
    else if (usagePercentage >= 71 && usagePercentage <= 80)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality - 10);
        }
        return 8;
    }
    else if (usagePercentage >= 81 && usagePercentage <= 90)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality - 15);
        }
        return 9;
    }
    else if (usagePercentage >= 91 && usagePercentage <= 100)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = (cnt_list[i]->conf.stream_quality - 20);
        }
        return 10;
    }
    else if (usagePercentage >= 100)
    {
        // scale down to x
                //do quality change
        for(int i = (cnt_list[1] != NULL ? 1 : 0); cnt_list[i]; i++)
        {
            cnt_list[i]->conf.stream_quality = 10;
        }
        return 11;
    }

    return -1;
}
