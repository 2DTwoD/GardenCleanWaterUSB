#include "flash.h"

extern Pulse M1timer;
extern Pulse M2timer;
extern Pulse M3timer;

extern SequenceDelayed OB1s1;
extern SequenceDelayed OB1s2;
extern SequenceDelayed OB1s4;
extern SequenceDelayed OB2s1;
extern SequenceDelayed OB2s2;
extern SequenceDelayed OB2s4;
extern SequenceDelayed OB3s1;
extern SequenceDelayed OB3s2;
extern SequenceDelayed OB3s4;
extern SequenceDelayed CHBs1;

void readFlash(){
    uint32_t flashContain[NUM_OF_VARS_FOR_SAVE];
    for(int8_t i = 0; i < NUM_OF_VARS_FOR_SAVE; i++){
        flashContain[i] = *(uint32_t*)(FLASH_START_ADDRESS + 4 * i);
    }
    if(flashContain[0] == TOKEN){
        M1timer.setPeriod(flashContain[1]);
        M2timer.setPeriod(flashContain[2]);
        M3timer.setPeriod(flashContain[3]);
        OB1s1.setPeriod(flashContain[4]);
        OB1s2.setPeriod(flashContain[5]);
        OB1s4.setPeriod(flashContain[6]);
        OB2s1.setPeriod(flashContain[7]);
        OB2s2.setPeriod(flashContain[8]);
        OB2s4.setPeriod(flashContain[9]);
        OB3s1.setPeriod(flashContain[10]);
        OB3s2.setPeriod(flashContain[11]);
        OB3s4.setPeriod(flashContain[12]);
        CHBs1.setPeriod(flashContain[13]);
    }
}

uint8_t writeVar(uint32_t *addr, uint32_t value, uint8_t *numOfVars){
    if(*numOfVars == 0) return HAL_ERROR;
    uint8_t status;
    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, *addr, value);
    *addr += 4;
    *numOfVars -= 1;
    return status;
}

uint8_t saveFlash(){
    uint8_t status;
    FLASH_EraseInitTypeDef FlashErase;
    uint32_t pageError = 0;
    uint32_t addr = FLASH_START_ADDRESS;
    __disable_irq();
    status = HAL_FLASH_Unlock();
    if(status != HAL_OK){
        return status;
    }
    FlashErase.TypeErase = FLASH_TYPEERASE_PAGES;
    FlashErase.PageAddress = addr;
    FlashErase.NbPages = 1;
    status = HAL_FLASHEx_Erase(&FlashErase, &pageError);
    if (status != HAL_OK)
    {
        HAL_FLASH_Lock();
        __enable_irq();
        return status;
    }
    uint8_t numOfVars = NUM_OF_VARS_FOR_SAVE;
    status |=  writeVar(&addr, TOKEN, &numOfVars);
    status |=  writeVar(&addr, M1timer.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, M2timer.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, M3timer.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB1s1.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB1s2.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB1s4.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB2s1.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB2s2.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB2s4.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB3s1.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB3s2.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, OB3s4.getPeriod(), &numOfVars);
    status |=  writeVar(&addr, CHBs1.getPeriod(), &numOfVars);
    __enable_irq();
    HAL_FLASH_Lock();
    return status;
}

