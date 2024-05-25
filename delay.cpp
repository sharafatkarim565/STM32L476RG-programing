#include "stm32l476xx.h"
#include "HAL_GPIO.h"

void dUs(uint32_t us);
void dMs(uint32_t ms);
volatile uint32_t myT = 0;
void delay_ms(uint32_t ms);
//int s=0;

int main()
{
    SysTick_Config(SystemCoreClock / 1000);
    
    //****************UART*************************//
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
    RCC->AHB2ENR |= (1 << 0);
    
    GPIO_TYPE gpio1;
    gpio1.port = PORTA;
    gpio1.pin = 2;
    gpio1.mood = ALT_FUN_MODE;
    gpio_init(gpio1);
    
    GPIOA->AFR[0] |= (0x7 << GPIO_AFRL_AFSEL2_Pos); 
    USART2->BRR = 0x1A0;
    USART2->CR1 |= 0x00;
    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE;
    printm("connection established \n");
    
    //******************TIMER*************************//
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
    
    TIM4->PSC = 4 - 1;  // Prescaler: divides clock by 4 (4 MHz / 4 = 1 MHz)
    TIM4->ARR = 1000 - 1;   // Auto-reload value: 1 count
    TIM4->CR1 |= TIM_CR1_URS;
    TIM4->DIER |= TIM_DIER_UIE;
    TIM4->EGR |= TIM_EGR_UG;
    
    NVIC_EnableIRQ(TIM4_IRQn);

    while (1) 
    {
        printm("hi\n");
        dMs(1000); // Delay for 1 second
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

//*****************************delay using Timer******************
void dUs(uint32_t us)
{
    myT = 0;
    TIM4->CR1 |= TIM_CR1_CEN;  // Enable timer
    while (myT < us);
    TIM4->CR1 &= ~TIM_CR1_CEN; // Disable timer
}

void dMs(uint32_t ms)
{
    dUs(ms * 1000);
}

extern "C" void TIM4_IRQHandler(void)
{
    if (TIM4->SR & TIM_SR_UIF) // Update interrupt flag
    {
        TIM4->SR &= ~TIM_SR_UIF; // Clear the update interrupt flag
        myT+= 1000;
			//s++;
    }
}
