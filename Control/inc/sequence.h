#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "rf_impulse.h"
#include "common_timer.h"

enum Status{
    SEQ_STAND_BY = 0,
    SEQ_ACTIVE = 1,
    SEQ_LOCKED = 2,
    SEQ_FINISHED = 3,
    SEQ_UNKNOWN = 4
};

class Sequence: private RFimpulse{
	private:
		bool strt;
		bool lck;
		bool fin;
		const uint8_t seq_step;
		uint8_t *cur_step_pointer;
		bool isMyStep();
	public:
		Sequence(uint8_t *const cur_step_pointer, uint8_t seq_step);
		virtual void reset();
		void start(bool value);
		void lock(bool value);
		void finish(bool value);
        uint8_t getStep() const;
		void slfSet(bool strt, bool lck, bool fin);
		bool active();
		bool started();
		bool locked();
		bool finished();
		bool finishedImpulse();
        Status getStatus();
};

class SequenceDelayed: private CommonTimer, public Sequence, public IUpdated1ms{
	public:
		SequenceDelayed(uint8_t *const cur_step_pointer, uint8_t seq_step, uint32_t delay);
		void update1ms() override;
        void reset() override;
		using Sequence::start;
		using Sequence::finish;
		using Sequence::active;
		using Sequence::started;
		using Sequence::locked;
		using Sequence::finished;
		using Sequence::finishedImpulse;
        using CommonTimer::getTimeRemain;
        using CommonTimer::getPeriod;
        using CommonTimer::setPeriod;
};
#endif //SEQUENCE_H