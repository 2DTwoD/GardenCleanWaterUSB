#include "main_app.h"

extern TaskKit ob1Kit;
extern TaskKit ob2Kit;
extern TaskKit ob3Kit;

extern TaskHandle_t OB1TaskHandle;
extern TaskHandle_t OB2TaskHandle;
extern TaskHandle_t OB3TaskHandle;
extern TaskHandle_t CHBTaskHandle;

int mainApp(void){
	tickInit();

    readFlash();

	BaseType_t xReturned;
	xReturned = xTaskCreate(OBTask, "OB1Task", configMINIMAL_STACK_SIZE,
                            (void*) &ob1Kit , tskIDLE_PRIORITY + 2, &OB1TaskHandle);
	if( xReturned != pdPASS ){
		__NOP();
	}
	xReturned = xTaskCreate(OBTask, "OB2Task", configMINIMAL_STACK_SIZE,
                            (void*) &ob2Kit, tskIDLE_PRIORITY + 2, &OB2TaskHandle);
	if( xReturned != pdPASS ){
		__NOP();
	}
	xReturned = xTaskCreate(OBTask, "OB3Task", configMINIMAL_STACK_SIZE,
                            (void*) &ob3Kit, tskIDLE_PRIORITY + 2, &OB3TaskHandle);
	if( xReturned != pdPASS ){
		__NOP();
	}
	xReturned = xTaskCreate(CHBTask, "CHBTask", configMINIMAL_STACK_SIZE,
                            NULL, tskIDLE_PRIORITY + 1, &CHBTaskHandle);
	if( xReturned != pdPASS ){
		__NOP();
	}
	xReturned = xTaskCreate(diagTask, "diagTask", configMINIMAL_STACK_SIZE,
                            NULL, tskIDLE_PRIORITY + 3, NULL);
	if( xReturned != pdPASS ){
		__NOP();
	}
    xReturned = xTaskCreate(comm, "commTask", configMINIMAL_STACK_SIZE * 10,
                            NULL, tskIDLE_PRIORITY + 1, NULL);
    if( xReturned != pdPASS ){
        __NOP();
    }

	vTaskStartScheduler();
	
	while(1);
}


extern "C"{
void vApplicationIdleHook ( void ){
    //idleCount++;
}
void vApplicationTickHook ( void ){
}
void vApplicationMallocFailedHook ( void ){
    while(1);
}
void vApplicationStackOverflowHook( TaskHandle_t xTask, char * pcTaskName ){
    ( void ) pcTaskName;
    ( void ) xTask;
    while(1);
}
void TIM2_IRQHandler(void){
    TIM2->SR &= ~TIM_SR_UIF;
    for(int i = 0; i < updateObjectsSize; i++){
        update1msObjects[i]->update1ms();
    }
}
}