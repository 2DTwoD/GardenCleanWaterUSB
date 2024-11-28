#ifndef PULSE_H
#define PULSE_H

#include "stdint.h"
#include "common_timer.h"

class PulseCommon: private CommonTimer {
	private:
		bool startFlag;
	public:
		PulseCommon(uint32_t period);
		void update();
		void set(bool value);
		bool get();
		void reset();
};

class Pulse: public PulseCommon, public IUpdated1ms {
	public:
		Pulse(uint32_t period);
		void update1ms() override;
		Pulse& operator=(bool value);
};

class PulseInterrapt: public PulseCommon, public IUpdated1ms {
	public:
		PulseInterrapt(uint32_t period);
		void update1ms() override;
		void set(bool value);
		PulseInterrapt& operator=(bool value);
};

#endif //PULSE_H