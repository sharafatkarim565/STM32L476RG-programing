#include "stm32l476xx.h"
#include "HAL_GPIO.h"

void delay_ms(uint32_t ms);
volatile uint32_t tick=0;

int main()
{
	SysTick_Config(SystemCoreClock / 1000);
	
	//****************LED**********************//
 /* RCC->AHB2ENR |= (1 << 0); //Enable GPIOA
	
  GPIOA->MODER &=~((1<<10) | (1<<11));
	GPIOA->MODER |=((1<<10) | (0<<11));*/ // set pin A5 to output mode
	
	GPIO_TYPE gpio;
	gpio.port=PORTA;
	gpio.pin=5;
	gpio.mood=GEN_PUR_OUTPUT_MODE;
	gpio_init(gpio);

	while(1)
	{
	 /*GPIOA->ODR |=(1<<5);
	 delay(100000);
	 GPIOA->ODR &=~(1<<5);
	 delay(100000);*/
		
		gpio_toggel(PORTA,5);
	  delay_ms(1000);
	}

}

//***********************Ms Delay using SysTick*******************
void delay_ms(uint32_t ms)
{
    tick = 0;
    while (tick < ms);
}

extern "C" void SysTick_Handler(void)
{
    tick++;
}
