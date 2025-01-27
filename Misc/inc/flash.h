#ifndef FLASH_H
#define FLASH_H

#include <cstdint>
#include "stm32f1xx.h"

#include "pulse.h"
#include "sequence.h"

#define FLASH_START_ADDRESS 0x0801F800
#define TOKEN 12321
#define NUM_OF_VARS_FOR_SAVE 14

//Чтение внутренней флэш памяти
void readFlash();

//Запись во внутреннюю флэш память
uint8_t saveFlash();

#endif //FLASH_H
