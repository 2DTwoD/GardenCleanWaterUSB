#ifndef API_ENGINE_H
#define API_ENGINE_H

#include "FreeRTOS.h"
#include "task.h"

#include <cstdint>
#include <cstring>

#include "usbd_cdc_if.h"

#include "coil.h"
#include "coil_with_timer.h"
#include "simple_input.h"
#include "sequence.h"

//Максимальная длина команды
#define MAX_COMMAND_LEN 32

void checkCommandAndSendResponse(uint8_t *command, uint8_t len);

#endif //API_ENGINE_H
