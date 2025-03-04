#ifndef COMMON_FOR_TASKS_H
#define COMMON_FOR_TASKS_H

#define NUM_OF_TANKS 3

#include "FreeRTOS.h"
#include "task.h"

#include <cstdint>
#include <cstring>

#include "usbd_cdc_if.h"

#include "coil.h"
#include "coil_with_timer.h"
#include "sequence.h"
#include "simple_input.h"

struct TaskKit{
	uint8_t* OBstep;
	bool* OBauto;
	bool* OBnext;
	Sequence* OBs0;
	SequenceDelayed* OBs1;
	SequenceDelayed* OBs2;
	Sequence* OBs3;
	SequenceDelayed* OBs4;
	Sequence* OBs5;
	SimpleInputDelayed* B;
	SimpleInputDelayed* H;
	Coil* C;
	Coil* O;
	Coil* D;
	Coil* M;
	Pulse* Mtimer;
};

void pushSeqInQueue(Sequence *seq);
Sequence* getSeqFromQueue();
void deleteSeqFromQueue(Sequence *seq);
void resetCHBsteps();
void getQueueString(char* result);
bool queueIsEmpty();
void lockSeqIfStepEqual(Sequence *seq, uint8_t step);

#endif //COMMON_FOR_TASKS_H