#include "api_engine.h"

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
extern PulseInterrapt OB1s4MeTimer;
extern Sequence OB1s5;

//Бак отстойника2:
extern uint8_t OB2step;
extern Sequence OB2s0;
extern SequenceDelayed OB2s1;
extern SequenceDelayed OB2s2;
extern Sequence OB2s3;
extern SequenceDelayed OB2s4;
extern PulseInterrapt OB2s4MeTimer;
extern Sequence OB2s5;

//Бак отстойника3:
extern uint8_t OB3step;
extern Sequence OB3s0;
extern SequenceDelayed OB3s1;
extern SequenceDelayed OB3s2;
extern Sequence OB3s3;
extern SequenceDelayed OB3s4;
extern PulseInterrapt OB3s4MeTimer;
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
                            "'s4Per':%d,'s4TimeRem':%d,'s5Per':%d,'s5TimeRem':%d}";

static const char *patternCHB = "{'step':%d,'s1St':%d,'s2St':%d,'s3St':%d,'s2Per':%d,'s2TimeRem':%d";
static uint8_t container[256];

void checkCommandAndSendResponse(uint8_t *command, uint8_t len){
    if(!strncmp("opaopa", (const char*)command, len)){
        taskENTER_CRITICAL();
        CDC_Transmit_FS(command, len);
        taskEXIT_CRITICAL();
    } else if(!strncmp("getPeriph", (const char*)command, len)){
        memset(container, 0, 256);
        sprintf((char *)container, patternPeriph, H1.isActive(), H2.isActive(), H3.isActive(), B1.isActive(),
                B2.isActive(), B3.isActive(), S4.isActive(), S5.isActive(), S6.isActive(), C1.isActive(),
                C2.isActive(), C3.isActive(), O1.isActive(), O2.isActive(), O3.isActive(), D1.isActive(),
                D2.isActive(), D3.isActive(), D4.isActive(), M1.isActive(), M2.isActive(), M3.isActive(),
                M6.isActive(), M7.isActive());
        taskENTER_CRITICAL();
        CDC_Transmit_FS(container,256);
        taskEXIT_CRITICAL();
    } else if(!strncmp("getOB1", (const char*)command, len)){
        memset(container, 0, 256);
        sprintf((char *)container, patternOB, OB1step, H2.isActive(), H3.isActive(), B1.isActive(),
                B2.isActive(), B3.isActive(), S4.isActive(), S5.isActive(), S6.isActive(), C1.isActive(),
                C2.isActive(), C3.isActive(), O1.isActive(), O2.isActive(), O3.isActive(), D1.isActive(),
                D2.isActive(), D3.isActive(), D4.isActive(), M1.isActive(), M2.isActive(), M3.isActive(),
                M6.isActive(), M7.isActive());
        taskENTER_CRITICAL();
        CDC_Transmit_FS(container,256);
        taskEXIT_CRITICAL();
    }
}