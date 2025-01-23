#ifndef COIL_WITH_TIMER_H
#define COIL_WITH_TIMER_H

#include "stm32f1xx.h"
#include "interfaces.h"
#include "gpio_common.h"
#include "common.h"
#include "common_timer.h"
#include "on_delay.h"
#include "off_delay.h"
#include "pulse.h"
#include "coil.h"

class CoilOnDelay: private OnDelayCommon, public Coil, public IUpdated1ms {
  public:
		CoilOnDelay(GPIO_TypeDef *gpio, uint8_t pin, uint16_t delay);
        using Coil::set;
        using Coil::reset;
        using OnDelayCommon::getPeriod;
        using OnDelayCommon::setPeriod;
        using OnDelayCommon::getTimeRemain;
		void update1ms() override;
	
		void setValue(bool value) override;

        void resetTimer();
	
		CoilOnDelay& operator=(bool value);
};

class CoilOffDelay: private OffDelayCommon, public Coil, public IUpdated1ms {
  public:
		using Coil::set;
		using Coil::reset;
        using OffDelayCommon::getPeriod;
        using OffDelayCommon::setPeriod;
        using OffDelayCommon::getTimeRemain;
		CoilOffDelay(GPIO_TypeDef *gpio, uint8_t pin, uint16_t delay);
	
		void update1ms() override;
	
		void setValue(bool value) override;

        void resetTimer();
	
		CoilOffDelay& operator=(bool value);
};

class CoilPulse: private PulseCommon, public Coil, public IUpdated1ms  {
  public:
		using Coil::set;
		using Coil::reset;
        using PulseCommon::getPeriod;
        using PulseCommon::setPeriod;
        using PulseCommon::getTimeRemain;
		CoilPulse(GPIO_TypeDef *gpio, uint8_t pin, uint16_t pulse);
	
		void update1ms() override;
	
		void setValue(bool value) override;

        void resetTimer();
	
		CoilPulse& operator=(bool value);
};
#endif //COIL_WITH_TIMER_H