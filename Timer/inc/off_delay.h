#ifndef OFF_DELAY_H
#define OFF_DELAY_H

#include "stdint.h"
#include "common_timer.h"

class OffDelayCommon: private CommonTimer{
	private:
		bool startFlag;
	public:
		OffDelayCommon(uint32_t period);
		void update();
		void set(bool value);
		bool get();
		void reset();
        using CommonTimer::getPeriod;
        using CommonTimer::setPeriod;
        using CommonTimer::getTimeRemain;
};

class OffDelay: public OffDelayCommon, public IUpdated1ms {
	public:
		OffDelay(uint32_t period);
		void update1ms() override;
		OffDelay& operator=(bool value);
};

#endif //OFF_DELAY_H