#ifndef MAIN_APP_H
#define MAIN_APP_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "init.h"
#include "all_tasks.h"
#include "api_engine.h"
#include "flash.h"

extern uint8_t updateObjectsSize;
extern IUpdated1ms *update1msObjects[];
//uint32_t idleCount;
int mainApp(void);

#endif //MAIN_APP_H
