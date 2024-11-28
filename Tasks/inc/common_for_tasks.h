#ifndef COMMON_FOR_TASKS_H
#define COMMON_FOR_TASKS_H

#include "FreeRTOS.h"
#include "task.h"

#include "stdint.h"
#include "coil.h"
#include "coil_with_timer.h"
#include "sequence.h"
#include "simple_input.h"

struct TaskKit{
	uint8_t* OBstep;
	Sequence* OBs0;
	SequenceDelayed* OBs1;
	SequenceDelayed* OBs2;
	Sequence* OBs3;
	SequenceDelayed* OBs4;
	PulseInterrapt* OBs4MeTimer;
	Sequence* OBs5;
	SimpleInputDelayed* B;
	SimpleInputDelayed* H;
	Coil* C;
	Coil* O;
	Coil* D;
	CoilPulse* M;
	Coil* Me;
}; 

void pushSeqInQueue(Sequence *seq);
Sequence* getSeqFromQueue();
void deleteSeqFromQueue(Sequence *seq);
void resetCHBsteps();

#endif //COMMON_FOR_TASKS_H