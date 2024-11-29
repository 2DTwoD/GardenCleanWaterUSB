#ifndef MAIN_APP_H
#define MAIN_APP_H

//#define SIM_ON

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "init.h"
#include "all_tasks.h"

extern uint8_t updateObjectsSize;
extern IUpdated1ms *update1msObjects[];
extern xQueueHandle commQueue;
//uint32_t idleCount;
int mainApp(void);

#endif //MAIN_APP_H
