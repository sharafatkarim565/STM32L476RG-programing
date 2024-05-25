#include "stm32l4xx.h"
#include "HAL_GPIO.h"

volatile uint32_t myT = 0;
void delay_ms(uint32_t ms);


int main()
{
	SysTick_Config(SystemCoreClock / 1000);
	
	//****************UART*************************//
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
  RCC->AHB2ENR |= (1 << 0);
	
	GPIO_TYPE gpio1;
	gpio1.port=PORTA;
	gpio1.pin=2;
	gpio1.mood=ALT_FUN_MODE;
	gpio_init(gpio1);
	
	
	GPIOA->AFR[0] |= (0x7 << GPIO_AFRL_AFSEL2_Pos) ; 
	USART2->BRR =0x1A0;//for 9600 baud rate
	USART2->CR1 |= 0x00;
	USART2->CR1 |=USART_CR1_UE | USART_CR1_TE;
	
	
 while(1)
 {
	 
	 printm("HELLO WORLD!\n");
	 delay_ms(1000);
	  
 }	

}

//***********************Ms Delay using SysTick*******************
void delay_ms(uint32_t ms)
{
    myT = 0;
    while (myT < ms);
}

extern "C" void SysTick_Handler(void)
{
    myT++;
}
