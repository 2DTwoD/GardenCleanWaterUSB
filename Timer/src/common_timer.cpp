#include "common_timer.h"

CommonTimer::CommonTimer(uint32_t period){
	this->period = period;
}
void CommonTimer::update(){
	if(started()){
		if(finished()) return;
		curTime++;
	}
}
uint32_t CommonTimer::getPeriod(){
	return period;
}
void CommonTimer::setPeriod(uint32_t value){
    if(finished()){
        setCurrentTime(value);
    } else {
        if(value >= getPeriod()){
            setCurrentTime(getCurrentTime() + value - getPeriod());
        } else {
            setCurrentTime(0);
        }
    }
    period = value;
}
uint32_t CommonTimer::getCurrentTime(){
	return curTime;
}
void CommonTimer::setCurrentTime(uint32_t value){
	curTime = value;
}
uint32_t CommonTimer::getTimeRemain() {
    return getPeriod() - getCurrentTime();
}
void CommonTimer::start(){
	go = true;
}
void CommonTimer::pause(){
	go = false;
}
void CommonTimer::stop(){
	pause();
	reset();
}
void CommonTimer::reset(){
	curTime = 0;
	impulse = false;
}
void CommonTimer::prepareAndStart(){
	stop();
	start();
}
void CommonTimer::finish(){
	start();
	curTime = period;
}
void CommonTimer::setStart(bool value){
	if(value){
		start();
	} else {
		stop();
	}
}
void CommonTimer::setPause(bool value){
	if(value){
		pause();
	} else {
		start();
	}
}
CommonTimer& CommonTimer::operator=(bool value){
	setStart(value);
	return *this;
}
CommonTimer& CommonTimer::operator+=(bool value){
	setPause(value);
	return *this;
}
bool CommonTimer::started(){
	return go;
}
bool CommonTimer::notStarted(){
	return !go;
}
bool CommonTimer::finished(){
 return curTime >= period;
}
bool CommonTimer::notFinished(){
 return curTime < period;
}
bool CommonTimer::finishedImpulse(){
	bool result = finished() && !impulse;
	if (finished()) impulse = true;
	return result;
}
bool CommonTimer::inWork(){
	return started() && notFinished();
}
bool CommonTimer::isFree(){
	return notStarted() || finished();
}
