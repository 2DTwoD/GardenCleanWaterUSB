#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include "coil.h"
#include "coil_with_timer.h"
#include "simple_input.h"
#include "sequence.h"
#include "common_timer.h"
#include "on_delay.h"
#include "pulse.h"
#include "common_for_tasks.h"

//Входа/выхода
SimpleInputDelayed B1(GPIOA, 0, 500);
SimpleInputDelayed H1(GPIOA, 1, 500);
SimpleInputDelayed B2(GPIOA, 2, 500);
SimpleInputDelayed H2(GPIOA, 3, 500);
SimpleInputDelayed B3(GPIOA, 4, 500);
SimpleInputDelayed H3(GPIOA, 5, 500);
SimpleInputDelayed S4(GPIOA, 6, 5000);
SimpleInputDelayed S5(GPIOA, 7, 5000);
SimpleInputDelayed S6(GPIOA, 8, 5000);
Coil C1(GPIOA, 9);
Coil O1(GPIOA, 10);
Coil D1(GPIOA, 15);
CoilPulse M1(GPIOB, 0, 2000);
Coil C2(GPIOB, 1);
Coil O2(GPIOB, 3);
Coil D2(GPIOB, 4);
CoilPulse M2(GPIOB, 5, 2000);
Coil C3(GPIOB, 6);
Coil O3(GPIOB, 7);
Coil D3(GPIOB, 8);
CoilPulse M3(GPIOB, 9, 2000);
Coil D4(GPIOB, 10);
CoilOffDelay M6(GPIOB, 11, 5000);
Coil M7(GPIOB, 12);
Coil Me1(GPIOB, 13);
Coil Me2(GPIOB, 14);
Coil Me3(GPIOB, 15);
//Светодиод на blue pill
Coil led(GPIOC, 13);

//Последовательности
//Бак отстойника1:
uint8_t OB1step;
Sequence OB1s0(&OB1step, 0);
SequenceDelayed OB1s1(&OB1step, 1, 120000);//2 минуты
SequenceDelayed OB1s2(&OB1step, 2, 30000);//30 секунд
Sequence OB1s3(&OB1step, 3);
SequenceDelayed OB1s4(&OB1step, 4, 345600000);//96 часов
PulseInterrapt OB1s4MeTimer(3600000);//1 час
Sequence OB1s5(&OB1step, 5);

//Бак отстойника2:
uint8_t OB2step;
Sequence OB2s0(&OB2step, 0);
SequenceDelayed OB2s1(&OB2step, 1, 120000);//2 минуты
SequenceDelayed OB2s2(&OB2step, 2, 30000);//30 секунд
Sequence OB2s3(&OB2step, 3);
SequenceDelayed OB2s4(&OB2step, 4, 345600000);//96 часов
PulseInterrapt OB2s4MeTimer(3600000);//1 час
Sequence OB2s5(&OB2step, 5);

//Бак отстойника3:
uint8_t OB3step;
Sequence OB3s0(&OB3step, 0);
SequenceDelayed OB3s1(&OB3step, 1, 120000);//2 минуты
SequenceDelayed OB3s2(&OB3step, 2, 30000);//30 секунд
Sequence OB3s3(&OB3step, 3);
SequenceDelayed OB3s4(&OB3step, 4, 345600000);//96 часов
PulseInterrapt OB3s4MeTimer(3600000);//1 час
Sequence OB3s5(&OB3step, 5);

//Чистый бак:
uint8_t CHBstep;
Sequence CHBs0(&CHBstep, 0);
SequenceDelayed CHBs1(&CHBstep, 1, 15000);//15 секунд
Sequence CHBs2(&CHBstep, 2);

//Наборы входов/выходов для бочек отстойника
TaskKit ob1Kit{
	&OB1step,
	&OB1s0,
	&OB1s1,
	&OB1s2,
	&OB1s3,
	&OB1s4,
	&OB1s4MeTimer,
	&OB1s5,
	&B1,
	&H1,
	&C1,
	&O1,
	&D1,
	&M1,
	&Me1,
};
TaskKit ob2Kit{
	&OB2step,
	&OB2s0,
	&OB2s1,
	&OB2s2,
	&OB2s3,
	&OB2s4,
	&OB2s4MeTimer,
	&OB2s5,
	&B2,
	&H2,
	&C2,
	&O2,
	&D2,
	&M2,
	&Me2
};
TaskKit ob3Kit{
	&OB3step,
	&OB3s0,
	&OB3s1,
	&OB3s2,
	&OB3s3,
	&OB3s4,
	&OB3s4MeTimer,
	&OB3s5,
	&B3,
	&H3,
	&C3,
	&O3,
	&D3,
	&M3,
	&Me3
};

//Очередь
Sequence *queue[] = {nullptr, nullptr, nullptr};

IUpdated1ms *update1msObjects[] = {
	&B1,
	&H1,
	&B2,
	&H2,
	&B3,
	&H3,
	&S4,
	&S5,
	&S6,
	&M1,
	&M2,
	&M3,
	&M6,
	&OB1s1,
	&OB1s2,
	&OB1s4,
	&OB1s4MeTimer,
	&OB2s1,
	&OB2s2,
	&OB2s4,
	&OB2s4MeTimer,
	&OB3s1,
	&OB3s2,
	&OB3s4,
	&OB3s4MeTimer,
	&CHBs1
};

uint8_t updateObjectsSize = sizeof(update1msObjects) / sizeof(*update1msObjects);
#endif //GLOBAL_VARS_H