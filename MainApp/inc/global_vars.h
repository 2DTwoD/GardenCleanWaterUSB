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
#include "queue.h"
#include "api_engine.h"

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
Coil M1(GPIOB, 0);
Coil C2(GPIOB, 1);
Coil O2(GPIOB, 3);
Coil D2(GPIOB, 4);
Coil M2(GPIOB, 5);
Coil C3(GPIOB, 6);
Coil O3(GPIOB, 7);
Coil D3(GPIOB, 8);
Coil M3(GPIOB, 9);
Coil D4(GPIOB, 10);
Coil M6(GPIOB, 11);
Coil M7(GPIOB, 12);
//Светодиод на blue pill
Coil led(GPIOC, 13);
//Таймеры для M1-M3, M6
Pulse M1timer(20000);//20 секунд дозирование в бак отстойник 1
Pulse M2timer(20000);//20 секунд дозирование в бак отстойник 2
Pulse M3timer(20000);//20 секунд дозирование в бак отстойник 3
OffDelay M6timer(5000);//5 секунд задержка выключения М6 в автомате

//Последовательности
//Бак отстойника1:
uint8_t OB1step;
bool OB1auto = true;
bool OB1next;
Sequence OB1s0(&OB1step, 0);
SequenceDelayed OB1s1(&OB1step, 1, 120000);//2 минуты
SequenceDelayed OB1s2(&OB1step, 2, 30000);//30 секунд
Sequence OB1s3(&OB1step, 3);
SequenceDelayed OB1s4(&OB1step, 4, 345600000);//96 часов
Sequence OB1s5(&OB1step, 5);

//Бак отстойника2:
uint8_t OB2step;
bool OB2auto = true;
bool OB2next;
Sequence OB2s0(&OB2step, 0);
SequenceDelayed OB2s1(&OB2step, 1, 120000);//2 минуты
SequenceDelayed OB2s2(&OB2step, 2, 30000);//30 секунд
Sequence OB2s3(&OB2step, 3);
SequenceDelayed OB2s4(&OB2step, 4, 345600000);//96 часов
Sequence OB2s5(&OB2step, 5);

//Бак отстойника3:
uint8_t OB3step;
bool OB3auto = true;
bool OB3next;
Sequence OB3s0(&OB3step, 0);
SequenceDelayed OB3s1(&OB3step, 1, 120000);//2 минуты
SequenceDelayed OB3s2(&OB3step, 2, 30000);//30 секунд
Sequence OB3s3(&OB3step, 3);
SequenceDelayed OB3s4(&OB3step, 4, 345600000);//96 часов
Sequence OB3s5(&OB3step, 5);

//Чистый бак:
uint8_t CHBstep;
bool CHBauto = true;
bool CHBnext;
Sequence CHBs0(&CHBstep, 0);
SequenceDelayed CHBs1(&CHBstep, 1, 15000);//15 секунд
Sequence CHBs2(&CHBstep, 2);

//Наборы входов/выходов для бочек отстойника
TaskKit ob1Kit{
	&OB1step,
	&OB1auto,
	&OB1next,
	&OB1s0,
	&OB1s1,
	&OB1s2,
	&OB1s3,
	&OB1s4,
	&OB1s5,
	&B1,
	&H1,
	&C1,
	&O1,
	&D1,
	&M1,
	&M1timer
};
TaskKit ob2Kit{
	&OB2step,
	&OB2auto,
	&OB2next,
	&OB2s0,
	&OB2s1,
	&OB2s2,
	&OB2s3,
	&OB2s4,
	&OB2s5,
	&B2,
	&H2,
	&C2,
	&O2,
	&D2,
	&M2,
    &M2timer
};
TaskKit ob3Kit{
	&OB3step,
	&OB3auto,
	&OB3next,
	&OB3s0,
	&OB3s1,
	&OB3s2,
	&OB3s3,
	&OB3s4,
	&OB3s5,
	&B3,
	&H3,
	&C3,
	&O3,
	&D3,
	&M3,
    &M3timer
};

//Очередь баков
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
	&M1timer,
	&M2timer,
	&M3timer,
	&M6timer,
	&OB1s1,
	&OB1s2,
	&OB1s4,
	&OB2s1,
	&OB2s2,
	&OB2s4,
	&OB3s1,
	&OB3s2,
	&OB3s4,
	&CHBs1
};

uint8_t updateObjectsSize = sizeof(update1msObjects) / sizeof(*update1msObjects);

//Очередь для связи по COM порту
xQueueHandle commQueue = xQueueCreate(MAX_COMMAND_LEN, sizeof (uint8_t));

//Задачи для баков
TaskHandle_t OB1TaskHandle = nullptr;
TaskHandle_t OB2TaskHandle = nullptr;
TaskHandle_t OB3TaskHandle = nullptr;
TaskHandle_t CHBTaskHandle = nullptr;

#endif //GLOBAL_VARS_H