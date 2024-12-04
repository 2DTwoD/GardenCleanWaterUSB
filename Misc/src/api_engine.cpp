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
extern CoilPulse M1;
extern Coil C2;
extern Coil O2;
extern Coil D2;
extern CoilPulse M2;
extern Coil C3;
extern Coil O3;
extern Coil D3;
extern CoilPulse M3;
extern Coil D4;
extern CoilOffDelay M6;
extern Coil M7;


//Последовательности
//Бак отстойника1:
extern uint8_t OB1step;
extern Sequence OB1s0;
extern SequenceDelayed OB1s1;
extern SequenceDelayed OB1s2;
extern Sequence OB1s3;
extern SequenceDelayed OB1s4;
extern Sequence OB1s5;

//Бак отстойника2:
extern uint8_t OB2step;
extern Sequence OB2s0;
extern SequenceDelayed OB2s1;
extern SequenceDelayed OB2s2;
extern Sequence OB2s3;
extern SequenceDelayed OB2s4;
extern Sequence OB2s5;

//Бак отстойника3:
extern uint8_t OB3step;
extern Sequence OB3s0;
extern SequenceDelayed OB3s1;
extern SequenceDelayed OB3s2;
extern Sequence OB3s3;
extern SequenceDelayed OB3s4;
extern Sequence OB3s5;

//Чистый бак:
extern uint8_t CHBstep;
extern Sequence CHBs0;
extern SequenceDelayed CHBs1;
extern Sequence CHBs2;

static const char *patternPeriph = "{'H1':%d,'H2':%d,'H3':%d,'B1':%d,'B2':%d,'B3':%d,'S4':%d,'S5':%d,'S6':%d,"
                      "'C1':%d,'C2':%d,'C3':%d,'O1':%d,'O2':%d,'O3':%d,'D1':%d,'D2':%d,'D3':%d,'D4':%d,"
                      "'M1':%d,'M2':%d,'M3':%d,'M6':%d,'M7':%d}";

static const char *patternOB = "{'step':%d,'s1St':%d,'s2St':%d,'s3St':%d,'s4St':%d,'s5St':%d,'s6St':%d,"
                            "'s2Per':%d,'s2TimeRem':%d,'s3Per':%d,'s3TimeRem':%d,"
                            "'s4MPer':%d,'s4MTimeRem':%d,'s5Per':%d,'s5TimeRem':%d}";

static const char *patternCHB = "{'step':%d,'s1St':%d,'s2St':%d,'s3St':%d,'s2Per':%d,'s2TimeRem':%d}";

static uint8_t container[CONTAINER_LEN];

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

void checkCommandAndSendResponse(uint8_t *command, uint8_t len){
    char action[MAX_COMMAND_LEN];
    char parameter[MAX_COMMAND_LEN];
    char strValue[MAX_COMMAND_LEN];
    zeroAndFill(action, strtok((char *)command, "."));
    zeroAndFill(parameter, strtok(nullptr, "."));
    zeroAndFill(strValue, strtok(nullptr, "."));
    uint32_t value = atoi(strValue);
    if(!strncmp("get", action, 3)){
        memset(container, 0, CONTAINER_LEN);
        if(!strncmp("periph", parameter, 6)){
            sprintf((char *)container, patternPeriph, H1.isActive(), H2.isActive(), H3.isActive(), B1.isActive(),
                    B2.isActive(), B3.isActive(), S4.isActive(), S5.isActive(), S6.isActive(), C1.isActive(),
                    C2.isActive(), C3.isActive(), O1.isActive(), O2.isActive(), O3.isActive(), D1.isActive(),
                    D2.isActive(), D3.isActive(), D4.isActive(), M1.isActive(), M2.isActive(), M3.isActive(),
                    M6.isActive(), M7.isActive());
            sendResponse();
        } else if(!strncmp("ob1", parameter, 3)){
            sprintf((char *)container, patternOB, OB1step + 1, OB1s0.getStatus(), OB1s1.getStatus(), OB1s2.getStatus(),
                    OB1s3.getStatus(), OB1s4.getStatus(), OB1s5.getStatus(), OB1s1.getPeriod(), OB1s1.getTimeRemain(),
                    OB1s2.getPeriod(), OB1s2.getTimeRemain(), M1.getPeriod(), M1.getTimeRemain(),
                    OB1s4.getPeriod(), OB1s4.getTimeRemain());
            sendResponse();
        } else if(!strncmp("ob2", parameter, 3)){
            sprintf((char *)container, patternOB, OB2step + 1, OB2s0.getStatus(), OB2s1.getStatus(), OB2s2.getStatus(),
                    OB2s3.getStatus(), OB2s4.getStatus(), OB2s5.getStatus(), OB2s1.getPeriod(), OB2s1.getTimeRemain(),
                    OB2s2.getPeriod(), OB2s2.getTimeRemain(), M2.getPeriod(), M2.getTimeRemain(),
                    OB2s4.getPeriod(), OB2s4.getTimeRemain());
            sendResponse();
        } else if(!strncmp("ob3", parameter, 3)){
            sprintf((char *)container, patternOB, OB3step + 1, OB3s0.getStatus(), OB3s1.getStatus(), OB3s2.getStatus(),
                    OB3s3.getStatus(), OB3s4.getStatus(), OB3s5.getStatus(), OB3s1.getPeriod(), OB3s1.getTimeRemain(),
                    OB3s2.getPeriod(), OB3s2.getTimeRemain(), M3.getPeriod(), M3.getTimeRemain(),
                    OB3s4.getPeriod(), OB3s4.getTimeRemain());
            sendResponse();
        } else if(!strncmp("chb", parameter, 3)){
            sprintf((char *)container, patternCHB, CHBstep + 1, CHBs0.getStatus(), CHBs1.getStatus(), CHBs2.getStatus(),
                    CHBs1.getPeriod(), CHBs1.getTimeRemain());
            sendResponse();
        } else {
            sendRespText("wrong get command");
        }
    } else if(!strncmp("set", action, 3)){
        if(!strncmp("c1", parameter, 2)){
            C1.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("c2", parameter, 2)){
            C2.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("c3", parameter, 2)){
            C3.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("o1", parameter, 2)){
            O1.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("o2", parameter, 2)){
            O2.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("o3", parameter, 2)){
            O3.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("d1", parameter, 2)){
            D1.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("d2", parameter, 2)){
            D2.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("d3", parameter, 2)){
            D3.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("d4", parameter, 2)){
            D4.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("m1", parameter, 2)){
            M1.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("m2", parameter, 2)){
            M2.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("m3", parameter, 2)){
            M3.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("m6", parameter, 2)){
            M6.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("m7", parameter, 2)){
            M7.setValue(limit((int)value, 0, 1));
        } else if(!strncmp("ob1step", parameter, 7)){
            OB1step = limit((int)value, 0, 6) - 1;
        } else if(!strncmp("ob2step", parameter, 7)){
            OB2step = limit((int)value, 0, 6) - 1;
        } else if(!strncmp("ob3step", parameter, 7)){
            OB3step = limit((int)value, 0, 6) - 1;
        } else if(!strncmp("chbstep", parameter, 7)){
            CHBstep = limit((int)value, 0, 6) - 1;
        } else if(!strncmp("ob1s2per", parameter, 8)){
            OB1s1.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob1s3per", parameter, 8)){
            OB1s2.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob1s4mper", parameter, 9)){
            M1.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob1s5per", parameter, 8)){
            OB1s4.setPeriod(limit(value, (uint32_t)1000, (uint32_t)4294967295));
        } else if(!strncmp("ob2s2per", parameter, 8)){
            OB2s1.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob2s3per", parameter, 8)){
            OB2s2.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob2s4mper", parameter, 9)){
            M2.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob2s5per", parameter, 8)){
            OB2s4.setPeriod(limit(value, (uint32_t)1000, (uint32_t)4294967295));
        } else if(!strncmp("ob3s2per", parameter, 8)){
            OB3s1.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob3s3per", parameter, 8)){
            OB3s2.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob3s4mper", parameter, 9)){
            M3.setPeriod(limit((int)value, 1000, 600000));
        } else if(!strncmp("ob3s5per", parameter, 8)){
            OB3s4.setPeriod(limit(value, (uint32_t)1000, (uint32_t)4294967295));
        } else if(!strncmp("chbs2per", parameter, 8)){
            CHBs1.setPeriod(limit((int)value, 1000, 600000));
        }  else {
            sendRespText("wrong set command");
            return;
        }
        sendRespText("ok");
    } else if(!strncmp("ping", action, 4)){
        sendRespText("pong");
    }
}