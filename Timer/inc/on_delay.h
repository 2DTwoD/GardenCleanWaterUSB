#ifndef ON_DELAY_H
#define ON_DELAY_H
#include "stdint.h"
#include "common_timer.h"

class OnDelayCommon: private CommonTimer {
	public:
		OnDelayCommon(uint32_t period);
		void update();
		void set(bool value);
		void setPause(bool value);
		bool get();
		void reset();
};

class OnDelay: public OnDelayCommon, public IUpdated1ms {
	public:
		OnDelay(uint32_t period);
		void update1ms() override;
		OnDelay& operator=(bool value);
		OnDelay& operator+=(bool value);
};

#endif //ON_DELAY_H