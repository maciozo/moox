#include "hexchat-plugin.h"

#define PNAME "moox"
#define PDESC "moo for Hexchat"
#define PVERSION "win-x64-0.1"

static hexchat_plugin *ph;

static int
moo (char *word[], char *word_eol[], void *userdata)
{
    
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