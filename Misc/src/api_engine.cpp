#include "api_engine.h"

#define CONTAINER_LEN 256

extern SimpleInputDelayed B1;
extern SimpleInputDelayed H1;
extern SimpleInputDelayed B2;
extern SimpleInputDelayed H2;
extern SimpleInputDelayed B3;
extern SimpleInputDelayed H3;
extern SimpleInputDelayed S4;
extern SimpleInputDelayed S5;
extern SimpleInputDelayed S6;
extern Coil C1;
extern Coil O1;
extern Coil D1;
extern Coil M1;
extern Coil C2;
extern Coil O2;
extern Coil D2;
extern Coil M2;
extern Coil C3;
extern Coil O3;
extern Coil D3;
extern Coil M3;
extern Coil D4;
extern Coil M6;
extern Coil M7;
//Таймеры M1-M3
extern Pulse M1timer;
extern Pulse M2timer;
extern Pulse M3timer;


//Последовательности
//Бак отстойника1:
extern uint8_t OB1step;
extern bool OB1auto;
extern bool OB1next;
extern Sequence OB1s0;
extern SequenceDelayed OB1s1;
extern SequenceDelayed OB1s2;
extern Sequence OB1s3;
extern SequenceDelayed OB1s4;
extern Sequence OB1s5;

//Бак отстойника2:
extern uint8_t OB2step;
extern bool OB2auto;
extern bool OB2next;
extern Sequence OB2s0;
extern SequenceDelayed OB2s1;
extern SequenceDelayed OB2s2;
extern Sequence OB2s3;
extern SequenceDelayed OB2s4;
extern Sequence OB2s5;

//Бак отстойника3:
extern uint8_t OB3step;
extern bool OB3auto;
extern bool OB3next;
extern Sequence OB3s0;
extern SequenceDelayed OB3s1;
extern SequenceDelayed OB3s2;
extern Sequence OB3s3;
extern SequenceDelayed OB3s4;
extern Sequence OB3s5;

//Чистый бак:
extern uint8_t CHBstep;
extern bool CHBauto;
extern bool CHBnext;
extern Sequence CHBs0;
extern SequenceDelayed CHBs1;
extern Sequence CHBs2;

//Задачи для баков
extern TaskHandle_t OB1TaskHandle;
extern TaskHandle_t OB2TaskHandle;
extern TaskHandle_t OB3TaskHandle;
extern TaskHandle_t CHBTaskHandle;

const char *patternPeriph = "{'H1':%d,'H2':%d,'H3':%d,'B1':%d,'B2':%d,'B3':%d,'S4':%d,'S5':%d,'S6':%d,"
                      "'C1':%d,'C2':%d,'C3':%d,'O1':%d,'O2':%d,'O3':%d,'D1':%d,'D2':%d,'D3':%d,'D4':%d,"
                      "'M1':%d,'M2':%d,'M3':%d,'M6':%d,'M7':%d}";

const char *patternCHB = "{'step':%d,'auto':%d,'s1St':%d,'s2St':%d,'s3St':%d,"
                                "'s2Per':%d,'s2TimeRem':%d,'queue':'%s'}";

const char *patternOB = "{'step':%d,'auto':%d,'s1St':%d,'s2St':%d,'s3St':%d,'s4St':%d,'s5St':%d,'s6St':%d,"
                            "'s2Per':%d,'s2TimeRem':%d,'s3Per':%d,'s3TimeRem':%d,"
                            "'s4Per':%d,'s4TimeRem':%d,'s5Per':%d,'s5TimeRem':%d}";

uint8_t container[CONTAINER_LEN];

void sendRespText(const char *text){
    taskENTER_CRITICAL();
    CDC_Transmit_FS((uint8_t *)text, strlen(text));
    taskEXIT_CRITICAL();
}

void sendResponse(){
    taskENTER_CRITICAL();
    CDC_Transmit_FS(container,CONTAINER_LEN);
    taskEXIT_CRITICAL();
}

void zeroAndFill(char *ar, char *fillVal){
    memset(ar, 0, MAX_COMMAND_LEN);
    sprintf(ar, "%s", fillVal);
}

void setAuto(TaskHandle_t *task, bool *curAuto, bool val){
    *curAuto = val > 0;
    if(*curAuto){
        vTaskResume(*task);
    }
}

void checkCommandAndSendResponse(uint8_t *command, uint8_t len){
    char action[MAX_COMMAND_LEN];
    char parameter[MAX_COMMAND_LEN];
    char strValue[MAX_COMMAND_LEN];
    zeroAndFill(action, strtok((char *)command, "."));
    zeroAndFill(parameter, strtok(nullptr, "."));
    zeroAndFill(strValue, strtok(nullptr, "."));
    uint32_t value = atoi(strValue);
    if(!strcmp("get", action)){
        memset(container, 0, CONTAINER_LEN);
        if(!strcmp("periph", parameter)){
            sprintf((char *)container, patternPeriph, H1.isActive(), H2.isActive(), H3.isActive(), B1.isActive(),
                    B2.isActive(), B3.isActive(), S4.isActive(), S5.isActive(), S6.isActive(), C1.isActive(),
                    C2.isActive(), C3.isActive(), O1.isActive(), O2.isActive(), O3.isActive(), D1.isActive(),
                    D2.isActive(), D3.isActive(), D4.isActive(), M1.isActive(), M2.isActive(), M3.isActive(),
                    M6.isActive(), M7.isActive());
            sendResponse();
        } else if(!strcmp("chb", parameter)){
            char queue[] = "000";
            getQueueString(queue);
            sprintf((char *)container, patternCHB, CHBstep + 1, CHBauto, CHBs0.getStatus(), CHBs1.getStatus(), CHBs2.getStatus(),
                    CHBs1.getPeriod(), CHBs1.getTimeRemain(), queue);
            sendResponse();
        } else if(!strcmp("ob1", parameter)){
            sprintf((char *)container, patternOB, OB1step + 1, OB1auto, OB1s0.getStatus(), OB1s1.getStatus(), OB1s2.getStatus(),
                    OB1s3.getStatus(), OB1s4.getStatus(), OB1s5.getStatus(), OB1s1.getPeriod(), OB1s1.getTimeRemain(),
                    OB1s2.getPeriod(), OB1s2.getTimeRemain(), M1timer.getPeriod(), M1timer.getTimeRemain(),
                    OB1s4.getPeriod(), OB1s4.getTimeRemain());
            sendResponse();
        } else if(!strcmp("ob2", parameter)){
            sprintf((char *)container, patternOB, OB2step + 1, OB2auto, OB2s0.getStatus(), OB2s1.getStatus(), OB2s2.getStatus(),
                    OB2s3.getStatus(), OB2s4.getStatus(), OB2s5.getStatus(), OB2s1.getPeriod(), OB2s1.getTimeRemain(),
                    OB2s2.getPeriod(), OB2s2.getTimeRemain(), M2timer.getPeriod(), M2timer.getTimeRemain(),
                    OB2s4.getPeriod(), OB2s4.getTimeRemain());
            sendResponse();
        } else if(!strcmp("ob3", parameter)){
            sprintf((char *)container, patternOB, OB3step + 1, OB3auto, OB3s0.getStatus(), OB3s1.getStatus(), OB3s2.getStatus(),
                    OB3s3.getStatus(), OB3s4.getStatus(), OB3s5.getStatus(), OB3s1.getPeriod(), OB3s1.getTimeRemain(),
                    OB3s2.getPeriod(), OB3s2.getTimeRemain(), M3timer.getPeriod(), M3timer.getTimeRemain(),
                    OB3s4.getPeriod(), OB3s4.getTimeRemain());
            sendResponse();
        } else if(!strcmp("firmware", parameter)){
            sendRespText(FIRMWARE_VER);
        } else {
            sendRespText("wrong get command");
        }
    } else if(!strcmp("set", action)){
        if(!OB1auto && !strcmp("c1", parameter)){
            C1.setValue(limit((int)value, 0, 1));
        } else if(!OB2auto && !strcmp("c2", parameter)){
            C2.setValue(limit((int)value, 0, 1));
        } else if(!OB3auto && !strcmp("c3", parameter)){
            C3.setValue(limit((int)value, 0, 1));
        } else if(!OB1auto && !strcmp("o1", parameter)){
            O1.setValue(limit((int)value, 0, 1));
        } else if(!OB2auto && !strcmp("o2", parameter)){
            O2.setValue(limit((int)value, 0, 1));
        } else if(!OB3auto && !strcmp("o3", parameter)){
            O3.setValue(limit((int)value, 0, 1));
        } else if(!OB1auto && !strcmp("d1", parameter)){
            D1.setValue(limit((int)value, 0, 1));
        } else if(!OB2auto && !strcmp("d2", parameter)){
            D2.setValue(limit((int)value, 0, 1));
        } else if(!OB3auto && !strcmp("d3", parameter)){
            D3.setValue(limit((int)value, 0, 1));
        } else if(!CHBauto && !strcmp("d4", parameter)){
            D4.setValue(limit((int)value, 0, 1));
        } else if(!OB1auto && !strcmp("m1", parameter)){
            M1.setValue(limit((int)value, 0, 1));
        } else if(!OB2auto && !strcmp("m2", parameter)){
            M2.setValue(limit((int)value, 0, 1));
        } else if(!OB3auto && !strcmp("m3", parameter)){
            M3.setValue(limit((int)value, 0, 1));
        } else if(!CHBauto && !strcmp("m6", parameter)){
            M6.setValue(limit((int)value, 0, 1));
        } else if(!CHBauto && !strcmp("m7", parameter)){
            M7.setValue(limit((int)value, 0, 1));
        } else if(OB1auto && !strcmp("ob1again", parameter)){
            OB1step = 6;
        } else if(!strcmp("ob1auto", parameter)){
            setAuto(&OB1TaskHandle, &OB1auto, value);
        } else if(OB1auto && !strcmp("ob1next", parameter)){
            OB1next = value > 0;
        } else if(OB2auto && !strcmp("ob2again", parameter)){
            OB2step = 6;
        } else if(!strcmp("ob2auto", parameter)){
            setAuto(&OB2TaskHandle, &OB2auto, value);
        } else if(OB2auto && !strcmp("ob2next", parameter)){
            OB2next = value > 0;
        } else if(OB3auto && !strcmp("ob3again", parameter)){
            OB3step = 6;
        } else if(!strcmp("ob3auto", parameter)){
            setAuto(&OB3TaskHandle, &OB3auto, value);
        } else if(OB3auto && !strcmp("ob3next", parameter)){
            OB3next = value > 0;
        } else if(CHBauto && !strcmp("chbagain", parameter)){
            CHBstep = 3;
        } else if(!strcmp("chbauto", parameter)){
            setAuto(&CHBTaskHandle, &CHBauto, value);
        } else if(CHBauto && !strcmp("chbnext", parameter)){
            CHBnext = value > 0;
        } else if(!strcmp("ob1s2per", parameter)){
            OB1s1.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob1s3per", parameter)){
            OB1s2.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob1s4per", parameter)){
            M1timer.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob1s5per", parameter)){
            OB1s4.setPeriod(limit(value, (uint32_t)1000, (uint32_t)999999000));
            saveFlash();
        } else if(!strcmp("ob2s2per", parameter)){
            OB2s1.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob2s3per", parameter)){
            OB2s2.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob2s4per", parameter)){
            M2timer.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob2s5per", parameter)){
            OB2s4.setPeriod(limit(value, (uint32_t)1000, (uint32_t)999999000));
            saveFlash();
        } else if(!strcmp("ob3s2per", parameter)){
            OB3s1.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob3s3per", parameter)){
            OB3s2.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob3s4per", parameter)){
            M3timer.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("ob3s5per", parameter)){
            OB3s4.setPeriod(limit(value, (uint32_t)1000, (uint32_t)999999000));
            saveFlash();
        } else if(!strcmp("chbs2per", parameter)){
            CHBs1.setPeriod(limit((int)value, 1000, 600000));
            saveFlash();
        } else if(!strcmp("allauto", parameter)){
            setAuto(&OB1TaskHandle, &OB1auto, value);
            setAuto(&OB2TaskHandle, &OB2auto, value);
            setAuto(&OB3TaskHandle, &OB3auto, value);
            setAuto(&CHBTaskHandle, &CHBauto, value);
        } else if(!strcmp("all", parameter)){
            if(!OB1auto){
                C1.setValue(value > 0);
                O1.setValue(value > 0);
                D1.setValue(value > 0);
                M1.setValue(value > 0);
            }
            if(!OB2auto){
                C2.setValue(value > 0);
                O2.setValue(value > 0);
                D2.setValue(value > 0);
                M2.setValue(value > 0);
            }
            if(!OB3auto){
                C3.setValue(value > 0);
                O3.setValue(value > 0);
                D3.setValue(value > 0);
                M3.setValue(value > 0);
            }
            if(!CHBauto){
                D4.setValue(value > 0);
                M6.setValue(value > 0);
                M7.setValue(value > 0);
            }
        } else {
            sendRespText("wrong set command");
            return;
        }
        sendRespText("ok");
    } else if(!strcmp("ping", action)){
        sendRespText("pong");
    } else {
        sendRespText("wrong command");
    }
}