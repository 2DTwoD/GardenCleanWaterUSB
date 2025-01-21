#include "common_for_tasks.h"

extern Sequence *queue[];
extern Sequence CHBs0;
extern SequenceDelayed CHBs1;
extern Sequence CHBs2;
extern Sequence OB1s5;
extern Sequence OB2s5;
extern Sequence OB3s5;
extern Coil D4;
extern Coil M7;
extern uint8_t CHBstep;

void pushSeqInQueue(Sequence *const seq){
	taskENTER_CRITICAL();
	for(uint8_t i = 0; i < NUM_OF_TANKS; i++){
		if(i == NUM_OF_TANKS - 1){
			queue[i] = seq;
		} else {
			if(queue[i] == nullptr){
				queue[i] = queue[i + 1];
				queue[i + 1] = nullptr;
			}
		}
	}
	taskEXIT_CRITICAL();
}

Sequence* getSeqFromQueue(){
	taskENTER_CRITICAL();
	for(uint8_t i = 0; i < NUM_OF_TANKS; i++){
		if(queue[i] != nullptr){
			taskEXIT_CRITICAL();
			return queue[i];
		}
	}
	taskEXIT_CRITICAL();
	return nullptr;
}

void deleteSeqFromQueue(Sequence *const seq){
	taskENTER_CRITICAL();
	for(uint8_t i = 0; i < NUM_OF_TANKS; i++){
		if(queue[i] == seq){
			queue[i] = nullptr;
		}
	}
	taskEXIT_CRITICAL();
}

char getOBnum(Sequence* seq){
    if(seq == &OB1s5){
        return '1';
    } else if(seq == &OB2s5){
        return '2';
    } else if(seq == &OB3s5){
        return '3';
    } else {
        return '0';
    }
}

void getQueueString(char* result){
    taskENTER_CRITICAL();
    for(uint8_t i = 0; i < NUM_OF_TANKS; i++){
        result[i] = getOBnum(queue[i]);
    }
    taskEXIT_CRITICAL();
}

bool queueIsEmpty(){
    taskENTER_CRITICAL();
    for(uint8_t i = 0; i < NUM_OF_TANKS; i++){
        if(queue[i] != nullptr){
            return false;
        }
    }
    taskEXIT_CRITICAL();
    return true;
}

void resetCHBsteps(){
	CHBs0.reset();
	CHBs1.reset();
	CHBs2.reset();
	D4 = false;
	M7 = false;
	CHBstep = 0;
}

