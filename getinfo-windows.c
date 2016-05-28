#include <stdlib.h>
#include <time.h>
#include <stdio.h>

const char*
getOSName()
{
    FILE *fp
    char output[256];
    
    fp = popen("wmic OS get Caption", "r");
    
    if (fp == NULL)
    {
        return "ERROR (wmic)";
    }
    
    fgets(output, sizeof(output)-1, fp); // First line is "Caption"
    fgets(output, sizeof(output)-1, fp); // Second line contains the value we want
    
    if (output == NULL)
    {
        pclose(fp);
        return "ERROR (output)";
    }
    
    pclose(fp);
    return output;
}

const char*
getOSVersion()
{
    FILE *fp
    char output[256];
    
    fp = popen("wmic OS get Version", "r");
    
    if (fp == NULL)
    {
        return "ERROR (wmic)";
    }
    
    fgets(output, sizeof(output)-1, fp); // First line is "Version"
    fgets(output, sizeof(output)-1, fp); // Second line contains the value we want
    
    if (output == NULL)
    {
        pclose(fp);
        return "ERROR (output)";
    }
    
    pclose(fp);
    return output;
}

const long int
getUptime()
{
    FILE *fp
    char output[256];
    int i = 0;
    int yearDelta = 0;
    int monthDelta = 0;
    struct tm tm_boot;
    struct tm tm_current;
    time_t bootTime;
    time_t currentTime;
    
    fp = popen("wmic OS get LastBootUpTime", "r");
    
    if (fp == NULL)
    {
        return -1;
    }
    
    fgets(output, sizeof(output)-1, fp); // First line is "LastBootUpTime"
    fgets(output, sizeof(output)-1, fp); // Second line contains the value we want
    
    if (output == NULL)
    {
        pclose(fp);
        return -1;
    }
    pclose(fp);
    
    // Format = YYYYmmDDHHMMSS.usecond+tz
    // Essentially cropping out the unnecessary precision and difference from UTC
    while (output[i] != '.')
    {
        i++;
    }
    output[i] = '\0';
    
    if (strptime(timestamp, "%Y%m%d%H%M%S", &tm_boot) != NULL)
    {
        bootTime = mktime(&tm_boot);
    }
    else
    {
        return -1; 
    }
    
    fp = popen("wmic OS get LocalDateTime", "r");
    
    if (fp == NULL)
    {
        return -1;
    }
    
    fgets(output, sizeof(output)-1, fp); // First line is "LocalDateTime"
    fgets(output, sizeof(output)-1, fp); // Second line contains the value we want
    
    if (output == NULL)
    {
        pclose(fp);
        return -1;
    }
    pclose(fp);
    
    while (output[i] != '.')
    {
        i++;
    }
    output[i] = '\0';
    
    if (strptime(timestamp, "%Y%m%d%H%M%S", &tm_current) != NULL)
    {
        currentTime = mktime(&tm_current);
    }
    else
    {
        return -1; 
    }
    
    return (long)tm_current - (long)tm_boot;
}

const int 
getCPUCount()
{
    FILE *fp
    char output[256];
    int numberOfCPUs = 0;
    
    fp = popen("wmic CPU list instance", "r");
    
    if (fp == NULL)
    {
        return -1;
    }
    
    fgets(output, sizeof(output)-1, fp); // First line is "DeviceID"
    
    while (fgets(output, sizeof(output)-1, fp) != NULL) // Subsequent lines list all CPU IDs
    {
        if (output[0] == 'C') // IDs formatted as "CPUxx"
        {
            numberOfCPUs++;
        }
    }
    
    pclose(fp);
    return numberOfCPUs;
}

const char*
getCPUName(const int cpuID)
{
    FILE *fp
    char output[256];
    char command[64];
    
    sprintf(command, "wmic CPU CPU%i get Name", cpuID);
    
    fp = popen(command, "r");
    
    if (fp == NULL)
    {
        return "ERROR (wmic)";
    }
    
    fgets(output, sizeof(output)-1, fp); // First line is "Name"
    fgets(output, sizeof(output)-1, fp); // Second line contains the value we want
    
    if (output == NULL)
    {
        pclose(fp);
        return "ERROR (output)";
    }
    
    pclose(fp);
    return output;
}

const int 
getCoreCount(const int cpuID)
{
    FILE *fp
    char output[256];
    char command[64];
    
    sprintf(command, "wmic CPU CPU%i get NumberOfCores", cpuID);
    
    fp = popen(command, "r");
    
    if (fp == NULL)
    {
        return -1;
    }
    
    fgets(output, sizeof(output)-1, fp); // First line is "NumberOfCores"
    fgets(output, sizeof(output)-1, fp); // Second line contains the value we want
    
    if (output == NULL)
    {
        pclose(fp);
        return -1;
    }
    
    pclose(fp);
    return atoi(output);
}

const int 
getCPUSpeed(const int cpuID)
{
    FILE *fp
    char output[256];
    char command[64];
    
    sprintf(command, "wmic CPU CPU%i get CurrentClockSpeed", cpuID);
    
    fp = popen(command, "r");
    
    if (fp == NULL)
    {
        return -1;
    }
    
    fgets(output, sizeof(output)-1, fp); // First line is "CurrentClockSpeed"
    fgets(output, sizeof(output)-1, fp); // Second line contains the value we want
    
    if (output == NULL)
    {
        pclose(fp);
        return -1;
    }
    
    pclose(fp);
    return atoi(output);
}
