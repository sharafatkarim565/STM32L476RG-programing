#include "stm32l476xx.h"
#include "HAL_GPIO.h"


int b=0;

int main()
{
	GPIO_TYPE gpio;
	gpio.port = PORTA;
	gpio.pin = 5;
	gpio.mood =GEN_PUR_OUTPUT_MODE;
	gpio_init(gpio);
	
	gpio.port = PORTC;
  gpio.pin = 13;
  gpio.mood = INPUT_MODE;
  gpio_init(gpio);
	
	gpio_config_interrupt(PORTC,13,FALLING_EDGE);
	enable_gpio_interrupt(13,EXTI15_10_IRQn);

	
	while(1)
	{
		if(b)
	 {
		 gpio_toggel(PORTA,5);
		 b=0;
	 }
	}

}

extern "C" void EXTI15_10_IRQHandler()
{
	clear_gpio_interrupt(13);
	b=1;

}

