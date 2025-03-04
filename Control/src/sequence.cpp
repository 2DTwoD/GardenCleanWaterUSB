#include "sequence.h"

//Sequence
Sequence::Sequence(uint8_t *const cur_step_pointer, uint8_t seq_step): RFimpulse(RISE), cur_step_pointer(cur_step_pointer), seq_step(seq_step){
}
bool Sequence::isMyStep(){
	return *cur_step_pointer == seq_step;
}
void Sequence::reset(){
	strt = false;
	lck = false;
	fin = false;
	RFimpulse::set(false);
}
void Sequence::start(bool value){
	if(isMyStep() && value){
		strt = true;
	}
}
void Sequence::lock(bool value){
	lck = value;
}
void Sequence::finish(bool value){
	if(isMyStep() && !fin && value){
		fin = true;
		RFimpulse::set(true);
		*cur_step_pointer = seq_step + 1;
	}
}
void Sequence::slfSet(bool strt, bool lck, bool fin){
	if(!isMyStep()){
		return;
	}
	start(strt);
	lock(lck);
	finish(fin);
}
bool Sequence::active(){
	return started() && !locked() && !finished();
}
bool Sequence::started(){
	return strt;
}
bool Sequence::locked(){
	return lck;
}
bool Sequence::finished(){
	return fin;
}
bool Sequence::finishedImpulse(){
	return RFimpulse::get();
}

Status Sequence::getStatus() {
    if (finished()){
        return SEQ_FINISHED;
    } else if(locked()){
        return SEQ_LOCKED;
    } else if(!started()){
        return SEQ_STAND_BY;
    } else if(active()){
        return SEQ_ACTIVE;
    }
    return SEQ_UNKNOWN;
}

uint8_t Sequence::getStep() const {
    return seq_step;
}

//SequenceDelayed
SequenceDelayed::SequenceDelayed(uint8_t *const cur_step_pointer, uint8_t seq_step, uint32_t delay): Sequence(cur_step_pointer, seq_step), CommonTimer(delay){
}
void SequenceDelayed::update1ms(){
	if(Sequence::locked()){
		return;
	}
	CommonTimer::setPause(!Sequence::active());
	CommonTimer::update();
	Sequence::finish(CommonTimer::finished());
}

void SequenceDelayed::reset(){
    Sequence::reset();
    CommonTimer::reset();
}
