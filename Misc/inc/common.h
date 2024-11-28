#ifndef COMMON_H
#define COMMON_H
#include "stdint.h"

enum IMPULSE {
	RISE = 0,
	FALL,
	RISE_FALL
};

void badTimeOut(uint32_t);

int8_t getPosition(volatile uint32_t mask);

template<typename T>
void setRegister(T * const reg, uint32_t mask, uint32_t value){
	*reg &= ~mask;
	*reg |= value;
}

template<typename T>
void setBitsInRegister(T * const reg, uint32_t mask, uint32_t value){
	int8_t pos = getPosition(mask);
	if(pos < 0) return;
	*reg &= ~mask;
	*reg |= (value << pos);
}

template<typename T>
T max(T val1, T val2){
	if(val1 > val2){
		 return val1;
	}
	return val2;
}

template<typename T>
T min(T val1, T val2){
	if(val1 < val2){
		 return val1;
	}
	return val2;
}

template<typename T>
void toggle(T *const val1, T *const val2){
	T toggle;
	toggle = *val1;
	*val1 = *val2;
	*val2 = toggle;
}

template<typename T>
T limit(T value, T valMin, T valMax){
	if(valMin > valMax){
		toggle(&valMin, &valMax);
	}
	if(value < valMin){
		value = valMin;
	} else if(value > valMax){
		value = valMax;
	}
	return value;
}

template<typename T>
T getRange(const T *const limits){
	return limits[1] - limits[0];
}

template<typename T>
void copyArrays(const T *const src, T *const dst, uint8_t len){
	for(int i = 0; i < len; i++){
		dst[i] = src[i];
	}
}

template<typename T>
T abs(T value){
	if(value < 0){
		value *= -1;
	}
	return value;
}
#endif //COMMON_H
