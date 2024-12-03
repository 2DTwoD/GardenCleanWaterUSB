#include "main_app.h"

extern TaskKit ob1Kit;
extern TaskKit ob2Kit;
extern TaskKit ob3Kit;

int mainApp(void){
	tickInit();
	
	BaseType_t xReturned;
	xReturned = xTaskCreate(OBTask, "OB1Task", configMINIMAL_STACK_SIZE, (void*) &ob1Kit , tskIDLE_PRIORITY + 2, NULL);
	if( xReturned != pdPASS ){
		__NOP();
	}
	xReturned = xTaskCreate(OBTask, "OB2Task", configMINIMAL_STACK_SIZE, (void*) &ob2Kit, tskIDLE_PRIORITY + 2, NULL);
	if( xReturned != pdPASS ){
		__NOP();
	}
	xReturned = xTaskCreate(OBTask, "OB3Task", configMINIMAL_STACK_SIZE, (void*) &ob3Kit, tskIDLE_PRIORITY + 2, NULL);
	if( xReturned != pdPASS ){
		__NOP();
	}
	xReturned = xTaskCreate(CHBTask, "CHBTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
	if( xReturned != pdPASS ){
		__NOP();
	}
	xReturned = xTaskCreate(diagTask, "diagTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
	if( xReturned != pdPASS ){
		__NOP();
	}
    commQueue = xQueueCreate(MAX_COMMAND_LEN, sizeof (uint8_t));
    xReturned = xTaskCreate(comm, "commTask", configMINIMAL_STACK_SIZE * 4, NULL, tskIDLE_PRIORITY + 3, NULL);
    if( xReturned != pdPASS ){
        __NOP();
    }
	vTaskStartScheduler();
	
	while(1);
}
