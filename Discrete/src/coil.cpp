#include "coil.h"

//ProgrammCoil
bool ProgrammCoil::isActive(){
	return out;
}
void ProgrammCoil::setValue(bool value){
	out = value;
}
bool ProgrammCoil::isNotActive(){
	return !isActive();
}
void ProgrammCoil::set(){
	setValue(true);
}
void ProgrammCoil::reset(){
	setValue(false);
}
void ProgrammCoil::toggle(){
	setValue(!isActive());
}
ProgrammCoil& ProgrammCoil::operator=(bool value){
	setValue(value);
	return *this;
}

//Coil
Coil::Coil(GPIO_TypeDef *gpio, uint8_t pin): GPIOcommon(gpio, pin) {
	if(pin < 8){
		setBitsInRegister(&gpio->CRL, 0b1111 << (4 * pin), 0b0001);
	} else {
		setBitsInRegister(&gpio->CRH, 0b1111 << (4 * pin - 32), 0b0001);
	}
}
bool Coil::isActive(){
	return (gpio->ODR & (1 << pin)) > 0;
}
void Coil::setValue(bool value){
	ProgrammCoil::setValue(value);
	if(value){
		//if(isNotActive()) 
		gpio->BSRR |= (1 << pin);
		return;
	}
	//if(isActive())
	gpio->BRR |= (1 << pin);
}
Coil& Coil::operator=(bool value){
	setValue(value);
	return *this;
}
