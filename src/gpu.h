#ifndef GPU_H
#define GPU_H

#include <stdint.h>

#define GPU_NAME_LENGTH 28

typedef struct {
    char name[GPU_NAME_LENGTH];
    float usagePercent;
    float temperature;
} GPUStatus;

uint8_t initGPU(void);
void quitGPU(void);

uint8_t readGPUUsage(GPUStatus* gpu);
uint8_t readGPUTemperature(GPUStatus* gpu);
uint8_t getGPUName(GPUStatus* gpu);

#endif