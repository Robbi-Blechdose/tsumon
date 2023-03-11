#include "panel.h"

#include <stdlib.h>
#include "panels/cpu.h"
#include "panels/ram.h"
#include "panels/gpu.h"
#include "panels/network.h"
#include "panels/fetch.h"
#include "display.h"

const char* panelNames[NUM_PANEL_TYPES] = {
    [P_CPU] = "CPU",
    [P_RAM] = "RAM",
    [P_GPU] = "GPU",
    [P_NETWORK] = "Network",
    [P_FETCH] = "System"
};

uint8_t numPanels;
Panel* panels;

uint8_t initPanel(Panel* panel)
{
    switch(panel->type)
    {
        case P_CPU:
        {
            initCPUPanel(panel);
            return 0;
        }
        case P_RAM:
        {
            initRAMPanel(panel);
            return 0;
        }
        case P_GPU:
        {
            return initGPUPanel(panel);
        }
        case P_NETWORK:
        {
            initNetworkPanel(panel);
            return 0;
        }
        case P_FETCH:
        {
            return initFetchPanel(panel);
        }
        default:
        {
            return 128;
        }
    }
}

//Discards errors from input functions for now
void updatePanel(Panel* panel)
{
    drawTitledWindow(panel->window, panelNames[panel->type], PANEL_WIDTH);
    wattrset(panel->window, A_BOLD);
    mvwaddstr(panel->window, 1, 1, panel->title);
    wattrset(panel->window, 0);

    switch(panel->type)
    {
        case P_CPU:
        {
            readCPUUsage(panel);
            readCPUTemperature(panel);
            drawCPUPanelContents(panel);
            break;
        }
        case P_RAM:
        {
            readRAMUsage(panel);
            drawRAMPanelContents(panel);
            break;
        }
        case P_GPU:
        {
            readGPUUsage(panel);
            readGPUMemoryUsage(panel);
            readGPUTemperature(panel);
            drawGPUPanelContents(panel);
            break;
        }
        case P_NETWORK:
        {
            readNetworkUsage(panel);
            drawNetworkPanelContents(panel);
            break;
        }
        case P_FETCH:
        {
            readUptime(panel);
            drawFetchPanelContents(panel);
            break;
        }
    }
    wrefresh(panel->window);
}

void drawPanelSettings(WINDOW* win, Panel* panel)
{
    switch(panel->type)
    {
        case P_NETWORK:
        {
            drawNetworkPanelSettings(win, panel);
            wrefresh(win);
            break;
        }
        default:
        {
            break;
        }
    }
}

void quitPanel(Panel* panel)
{
    free(panel->data);

    switch(panel->type)
    {
        case P_GPU:
        {
            quitGPU();
            break;
        }
        default:
        {
            break;
        }
    }
}