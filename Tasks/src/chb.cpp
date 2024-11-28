#include "all_tasks.h"

extern uint8_t CHBstep;
extern Sequence CHBs0;
extern SequenceDelayed CHBs1;
extern Sequence CHBs2;

extern SimpleInputDelayed S4;
extern SimpleInputDelayed S5;
extern SimpleInputDelayed S6;
extern Coil D4;
extern CoilOffDelay M6;
extern Coil M7;

void CHBTask(void *pvParameters){
	Sequence *current_ob = nullptr;
	while(1){
		if(CHBs0.finishedImpulse() && current_ob != nullptr){
			current_ob->start(true);
		}
		switch(CHBstep){
			case 0:
				current_ob = getSeqFromQueue();
				CHBs0.start(S5.isNotActive());
				CHBs0.finish(current_ob != nullptr);
				D4 = false;
				M7 = false;
				break;
			case 1:
				CHBs1.start(true);
				D4 = CHBs1.active();
				M7 = false;
				break;
			case 2:
				CHBs2.start(true);
				CHBs2.lock(S4.isActive());
				D4 = false;
				M7 = CHBs2.active();
				break;
		}
		M6 = S6.isActive();
		vTaskDelay(1);
	}
}

