#include "all_tasks.h"

extern Sequence CHBs2;
extern SimpleInputDelayed S4;
	
void resetAllSteps(TaskKit* taskKit){
	taskKit->OBs0->reset();
	taskKit->OBs1->reset();
	taskKit->OBs2->reset();
	taskKit->OBs3->reset();
	taskKit->OBs4->reset();
	taskKit->OBs5->reset();
    taskKit->Mtimer->reset();
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
        if(!*obKit->OBauto){
            lockSeqIfStepEqual(obKit->OBs0, *obKit->OBstep);
            lockSeqIfStepEqual(obKit->OBs1, *obKit->OBstep);
            lockSeqIfStepEqual(obKit->OBs2, *obKit->OBstep);
            lockSeqIfStepEqual(obKit->OBs3, *obKit->OBstep);
            lockSeqIfStepEqual(obKit->OBs4, *obKit->OBstep);
            lockSeqIfStepEqual(obKit->OBs5, *obKit->OBstep);
            obKit->Mtimer->setPause(true);
            vTaskSuspend(nullptr);
        }
		switch(*obKit->OBstep){
			case 0:
				obKit->OBs0->start(true);
				obKit->OBs0->lock(false);
				obKit->OBs0->finish(obKit->H->isNotActive() || *obKit->OBnext);
                if(!*obKit->OBauto) break;
				*obKit->C = false;
				*obKit->M = false;
				break;
			case 1:
				obKit->OBs1->start(true);
				obKit->OBs1->lock(false);
                obKit->OBs1->finish(*obKit->OBnext);
                if(!*obKit->OBauto) break;
				*obKit->C = false;
				*obKit->O = false;
				*obKit->D = obKit->OBs1->active();
				*obKit->M = false;
				break;
			case 2:
				obKit->OBs2->start(true);
				obKit->OBs2->lock(false);
                obKit->OBs2->finish(*obKit->OBnext);
                if(!*obKit->OBauto) break;
				*obKit->C = obKit->OBs2->active();
				*obKit->O = false;
				*obKit->D = obKit->OBs2->active();
				*obKit->M = false;
				break;
			case 3:
				obKit->OBs3->start(true);
				obKit->OBs3->lock(false);
				obKit->OBs3->finish(obKit->B->isActive() || *obKit->OBnext);
                if(!*obKit->OBauto) break;
				*obKit->C = obKit->OBs3->active();
				*obKit->O = false;
				*obKit->D = false;
                if(obKit->OBs3->finished()){
                    obKit->Mtimer->setPause(true);
                } else {
                    obKit->Mtimer->setPause(false);
                }
                *obKit->Mtimer = obKit->OBs3->active();
                *obKit->M = obKit->Mtimer->get();
				break;
			case 4:
				obKit->OBs4->start(true);
				obKit->OBs4->lock(false);
                obKit->OBs4->finish(*obKit->OBnext);
                if(!*obKit->OBauto) break;
				*obKit->C = false;
				*obKit->O = false;
				*obKit->D = false;
				*obKit->M = false;
				break;
			case 5:
				obKit->OBs5->lock(S4.isActive());
				obKit->OBs5->finish(obKit->H->isNotActive() ||*obKit->OBnext);
                if(!*obKit->OBauto) break;
                *obKit->C = false;
				*obKit->O = obKit->OBs5->active();
				*obKit->D = false;
				*obKit->M = false;
				break;
		}
        if(*obKit->OBstep > 5){
            *obKit->OBstep = 0;
            taskENTER_CRITICAL();
            if(getSeqFromQueue() == obKit->OBs5){
                resetCHBsteps();
            }
            deleteSeqFromQueue(obKit->OBs5);
            taskEXIT_CRITICAL();
            resetAllSteps(obKit);
        }
        *obKit->OBnext = false;
		vTaskDelay(1);
	}
}

