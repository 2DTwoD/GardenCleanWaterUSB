#include "all_tasks.h"

extern Sequence CHBs2;
	
void resetAllSteps(TaskKit* taskKit){
	taskKit->OBs0->reset();
	taskKit->OBs1->reset();
	taskKit->OBs2->reset();
	taskKit->OBs3->reset();
	taskKit->OBs4->reset();
	taskKit->OBs5->reset();
    taskKit->M->resetTimer();
	*taskKit->C = false;
	*taskKit->O = false;
	*taskKit->D = false;
	*taskKit->M = false;
}

void OBTask(void *pvParameters){
	TaskKit* obKit = (TaskKit*) pvParameters;
	resetAllSteps(obKit);
	while(1){
		if(obKit->OBs4->finishedImpulse()){
			pushSeqInQueue(obKit->OBs5);
		}
		switch(*obKit->OBstep){
			case 0:
				obKit->OBs0->start(true);
				obKit->OBs0->finish(obKit->H->isNotActive());
				*obKit->C = false;
				*obKit->M = false;
				break;
			case 1:
				obKit->OBs1->start(true);
				*obKit->C = false;
				*obKit->O = false;
				*obKit->D = obKit->OBs1->active();
				*obKit->M = false;
				break;
			case 2:
				obKit->OBs2->start(true);
				*obKit->C = obKit->OBs2->active();
				*obKit->O = false;
				*obKit->D = obKit->OBs2->active();
				*obKit->M = false;
				break;
			case 3:
				obKit->OBs3->start(true);
				obKit->OBs3->finish(obKit->B->isActive());
				*obKit->C = obKit->OBs3->active();
				*obKit->O = false;
				*obKit->D = false;
                *obKit->M = obKit->OBs3->active();
                if(obKit->OBs3->finished() && obKit->M->isActive()){
                    obKit->M->resetTimer();
                }
				break;
			case 4:
				obKit->OBs4->start(true);
				*obKit->C = false;
				*obKit->O = false;
				*obKit->D = false;
				*obKit->M = false;
				break;
			case 5:
				obKit->OBs5->lock(CHBs2.locked());
//				obKit->OBs5->finish(obKit->H->isNotActive());
				obKit->OBs5->finish(true);
				*obKit->C = false;
				*obKit->O = obKit->OBs5->active();
				*obKit->D = false;
				*obKit->M = false;
				break;
			default:
				*obKit->OBstep = 0;
				taskENTER_CRITICAL();
				if(getSeqFromQueue() == obKit->OBs5){
					resetCHBsteps();
				}
				taskEXIT_CRITICAL();
				deleteSeqFromQueue(obKit->OBs5);
				resetAllSteps(obKit);
		}
		vTaskDelay(1);
	}
}

