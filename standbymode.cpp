#include "stm32l4xx.h"
#include "HAL_GPIO.h"

void gotosleep();

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
	
	//**************************LPR MODE (SATNDBY)******************************//
	
	if(((PWR->SR1)&(PWR_SR1_SBF)))
	{
		PWR->SCR |= PWR_SCR_CSBF_Msk;
		printm("..i have awaken from standby..\r\n");
	}
	else
	{
		printm("..i have waken from power cylce..\r\n");
	}
	
	while(1)
	{
		printm("..going to sleep..\r\n");
		gotosleep();
		printm("fail\n");
	}

}

void gotosleep(){
	RCC->APB1ENR1 |=RCC_APB1ENR1_PWREN;
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	
	PWR->CR1 |=PWR_CR1_LPMS_STANDBY;
	PWR->SR1 |= PWR_SR1_WUF_Msk;

  // Set SLEEPDEEP bit in Cortex-M4 System Control register
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  // Ensure no interrupt or event is pending

  // Wait for interrupt (WFI)
  __WFI();

}
