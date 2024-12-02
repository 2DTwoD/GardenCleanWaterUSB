#ifndef ALL_TASKS_H
#define ALL_TASKS_H
#include "stdint.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "common_for_tasks.h"
#include "api_engine.h"
#include "coil.h"
#include "coil_with_timer.h"
#include "simple_input.h"
#include "sequence.h"
#include "common_timer.h"

void OBTask(void *pvParameters);
void CHBTask(void *pvParameters);
void diagTask(void *pvParameters);
void comm(void *pvParameters);

#endif //ALL_TASKS_H