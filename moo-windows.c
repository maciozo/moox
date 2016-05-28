#include "hexchat-plugin.h"
#include "getinfo.h"

#define PNAME "moox"
#define PDESC "moo for Hexchat"
#define PVERSION "win-x64-0.1"

static hexchat_plugin *ph;

char osName[256] = "\0";
char hostname[64] = "\0";
char osVersion[256] = "\0";
char architecture[64] = "\0";
int cpuCount = -1;
long int totalRAM = -1;
int gpuCount = -1;
char cpuNames[128][256];
char gpuNames[128][128];

int cpuLoad;
long int freeRAM;
long int uptime;
int cpuSpeed;

static int
moo (char *word[], char *word_eol[], void *userdata)
{
	int i;
	char stringToSend[4096];
	char format[4096] = "moo: os: %s (%s) up: %s cpu %s (%s) at %iMHz (%i%% Load) gfx: %s %iMB res: %ix%i %ibit %iHz ram: %i/%iMB hdd:";
	
	if (word[2][0] == 0) // Plain /moo
	{
		if (OSName[0] == '\0') // First run - set variables that won't change during operation
		{
			osName = getOSName();
			hostname = getHostname();
			osVersion = getOSVersion();
			architecture = getArchitecture();
			cpuCount = getCPUCount();
			totalRAM = getTotalRAM();
			gpuCount = getGPUCount();
			gpuNames = getGPUNames();
			for (i = 0; i < cpuCount; i++)
			{
				cpuNames[i] = getCPUName(i);
			}
		}
		cpuLoad = getCPULoad(0);
		freeRAM = getFreeRAM();
		uptime = getUptime();
		cpuSpeed = getCPUSpeed(0);
		
		sprintf(stringToSend, )
	}
}


void
hexchat_plugin_get_info (char **name, char **desc, char **version, void **reserved)
{
    *name = PNAME;
    *desc = PDESC;
    *version = PVERSION;
}

int
hexchat_plugin_init (hexchat_plugin *plugin_handle, char **plugin_name, char **plugin_desc, char **plugin_version, char *arg)
{
    /* we need to save this for use with any hexchat_* functions */
    ph = plugin_handle;

    /* tell HexChat our info */
    *plugin_name = PNAME;
    *plugin_desc = PDESC;
    *plugin_version = PVERSION;

    hexchat_hook_command (ph, "moo", HEXCHAT_PRI_NORM, moo, "Usage: moo, Send system info", 0);

    hexchat_print (ph, "moox loaded successfully!\n");

    return 1;       /* return 1 for success */
}