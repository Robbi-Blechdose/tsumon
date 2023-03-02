#include "fetch.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
    char os[PANEL_WIDTH - 5];
    char kernel[PANEL_WIDTH - 9];
} FetchData;

uint8_t getOS(char* os)
{
    FILE* issue = fopen("/etc/issue", "r");
    if(issue == NULL)
    {
        return 1;
    }

    if(fgets(os, PANEL_WIDTH - 5, issue) == NULL)
    {
        fclose(issue);
        return 2;
    }

    fclose(issue);
    return 0;
}

uint8_t getKernel(char* kernel)
{
    FILE* version = fopen("/proc/version", "r");
    if(version == NULL)
    {
        return 1;
    }

    if(fscanf(version, "%*s %*s %s", kernel) != 1)
    {
        fclose(version);
        return 2;
    }

    fclose(version);
    return 0;
}

uint8_t initFetchPanel(Panel* panel)
{
    panel->window = newwin(PANEL_HEIGHT, PANEL_WIDTH, 0, 0);
    panel->data = malloc(sizeof(FetchData));
    strcpy(panel->title, "");

    //Read data - this doesn't change so doing it on startup is enough
    FetchData* data = (FetchData*) panel->data;
    uint8_t err = getOS(data->os);
    if(err)
    {
        return err;
    }
    return getKernel(data->kernel);
}

void drawFetchPanelContents(Panel* panel)
{
    FetchData* data = (FetchData*) panel->data;
    mvwaddstr(panel->window, 1, 1, "OS:");
    mvwaddstr(panel->window, 1, 5, data->os);
    mvwaddstr(panel->window, 2, 1, "Kernel:");
    mvwaddstr(panel->window, 2, 9, data->kernel);
}