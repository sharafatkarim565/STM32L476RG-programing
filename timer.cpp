#include "stm32l4xx.h"
#include "HAL_GPIO.h"


int main()
{
	//****************UART*************************//
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
  RCC->AHB2ENR |= (1 << 0);
	
	GPIO_TYPE gpio1;
	gpio1.port=PORTA;
	gpio1.pin=2;
	gpio1.mood=ALT_FUN_MODE;
	gpio_init(gpio1);
	
	
	GPIOA->AFR[0] |= (0x7 << GPIO_AFRL_AFSEL2_Pos) ; 
	USART2->BRR =0x1A0;
	USART2->CR1 |= 0x00;
	USART2->CR1 |=USART_CR1_UE | USART_CR1_TE;
	
	
	//******************TIMER*************************//
	RCC->APB1ENR1 |=RCC_APB1ENR1_TIM4EN;
	
	TIM4->CCER |=TIM_CCER_CC4E;
	TIM4->CR1 |=TIM_CR1_ARPE;
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
	
	TIM4->PSC =4;
	TIM4->ARR=1000;
	TIM4->CCR4 =250;
	TIM4->EGR |= TIM_EGR_UG;
	TIM4->CR1|=TIM_CR1_CEN;
	
	
 while(1)
 {
	 
	 printm("%d\n",TIM4->CNT);
	  
 }	

}






