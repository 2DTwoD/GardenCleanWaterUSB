#include "all_tasks.h"

enum DiagPeriod{
	MIN = 200,
	MID = 1000,
	MAX = 3000,
	SHORT_DELAY = 300,
	LONG_DELAY = 3000,
};

extern uint8_t OB1step;
extern uint8_t OB2step;
extern uint8_t OB3step;
extern uint8_t CHBstep;

static uint8_t one =  0;
static uint8_t two =  1;
static uint8_t three =  2;

static DiagPeriod serial[]{MAX, MIN, MID, MIN, MID, MIN, MID, MIN};
static uint8_t* numOfSteps[]{&one, &CHBstep, &one, &OB1step, &two, &OB2step, &three, &OB3step};

extern Coil led;

void diagTask(void *pvParameters){
	led = false;
	uint8_t position = 0;
	int8_t step = 0;
	int16_t time = 0;
	int8_t dir = 1;
	while(1){
		if(time <= 0){
			time = 0;
			dir = 1;
			if(step < 0){
				position++;
				if(position >= 8){
					position = 0;
				}
				step = *numOfSteps[position];
			}
			step--;
		}
		time += dir;
		if(dir > 0 && time > serial[position]){
			if(position % 2 && step < 0){
				time = LONG_DELAY;
			} else {
				time = SHORT_DELAY;
			}
			dir = -1;
		}
		led = dir < 0;
		vTaskDelay(1);
	}
}
