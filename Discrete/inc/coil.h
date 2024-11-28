#ifndef COIL_H
#define COIL_H

#include "stm32f1xx.h"
#include "interfaces.h"
#include "gpio_common.h"
#include "common.h"
#include "common_timer.h"

class ProgrammCoil: public ISwitch{
	private:
		bool out;
	public:
		virtual bool isActive() override;
		virtual void setValue(bool value);
		bool isNotActive();
		void set();
		void reset();
		void toggle();
		ProgrammCoil& operator=(bool value);
};

class Coil: public GPIOcommon, public ProgrammCoil {
  public:
		Coil(GPIO_TypeDef *gpio, uint8_t pin);
	
		bool isActive() override;
	
		void setValue(bool value) override;
	
		Coil& operator=(bool value);
};

#endif //COIL_H