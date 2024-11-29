#include "all_tasks.h"

//Максимальная длина команды
#define MAX_COMMAND_LEN 30

extern xQueueHandle commQueue;
void comm(void *pvParameters){
    uint8_t received;
    uint8_t commandStr[MAX_COMMAND_LEN];
    int16_t index = -1;
    while(1){
        if(xQueueReceive(commQueue, &received, portMAX_DELAY) == pdTRUE){
            if(index >= 0){
                if(received == ']' || index >= MAX_COMMAND_LEN){
                    checkCommandAndSendResponse(commandStr, index);
                    index = -1;
                } else {
                    commandStr[index] = received;
                    index++;
                }
            } else if(received == '['){
                index = 0;
            }
        }
    }
}