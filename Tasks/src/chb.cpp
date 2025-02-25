#include "all_tasks.h"

extern uint8_t CHBstep;
extern bool CHBauto;
extern bool CHBnext;
extern Sequence CHBs0;
extern SequenceDelayed CHBs1;
extern Sequence CHBs2;

extern SimpleInputDelayed S4;
extern SimpleInputDelayed S5;
extern SimpleInputDelayed S6;
extern Coil D4;
extern Coil M6;
extern Coil M7;

extern OffDelay M6timer;

void CHBTask(void *pvParameters){
	Sequence *current_ob = nullptr;
	while(1){
        if(!CHBauto){
            lockSeqIfStepEqual(&CHBs0, CHBstep);
            lockSeqIfStepEqual(&CHBs1, CHBstep);
            lockSeqIfStepEqual(&CHBs2, CHBstep);
            vTaskSuspend(nullptr);
        }
		if(CHBs0.finishedImpulse() && current_ob != nullptr){
			current_ob->start(true);
		}
		switch(CHBstep) {
            case 0:
                current_ob = getSeqFromQueue();
                CHBs0.start(S5.isNotActive());
                CHBs0.lock(false);
                CHBs0.finish(current_ob != nullptr || CHBnext);
                if(!CHBauto) break;
                D4 = false;
                M7 = false;
                break;
            case 1:
                CHBs1.start(true);
                CHBs1.lock(false);
                CHBs1.finish(CHBnext);
                if(!CHBauto) break;
                D4 = CHBs1.active();
                M7 = false;
                break;
            case 2:
                CHBs2.start(true);
                CHBs2.lock(S4.isActive());
                CHBs2.finish(CHBnext || queueIsEmpty());
                if(!CHBauto) break;
                D4 = false;
                M7 = CHBs2.active();
                break;
        }
        if(CHBstep > 2){
            resetCHBsteps();
        }
        CHBnext = false;
        if(CHBauto){
            M6timer = S6.isActive();
            M6 = M6timer.get();
        }
		vTaskDelay(1);
	}
}

