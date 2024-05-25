#include "HAL_GPIO.h"
#include "stdint.h"
#include <cstdio>
#include <cstring>
#include <cstdarg>



uint32_t PINPOS[16]={

	(0x00),
	(0x02),
	(0x04),
	(0x06),
	(0x08),
	(0x0A),
	(0x0C),
	(0x0E),
	(0x10),
	(0x12),
	(0x14),
	(0x16),
	(0x18),
	(0x1A),
	(0x1C),
	(0x1E),
	
};

static void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mood)
{
	switch(mood)
	{
		case INPUT_MODE:
			port->MODER &=~ ( 1<<(PINPOS[pinNumber]) |  1<<(PINPOS[pinNumber]+1));
		  port->MODER |=  ( 0<<(PINPOS[pinNumber]) |  0<<(PINPOS[pinNumber]+1));
		break;
		
		case GEN_PUR_OUTPUT_MODE:
			port->MODER &=~ ( 1<<(PINPOS[pinNumber]) |  1<<(PINPOS[pinNumber]+1));
		  port->MODER |=  ( 1<<(PINPOS[pinNumber]) |  0<<(PINPOS[pinNumber]+1));
	  break;
		
		case ALT_FUN_MODE:
			port->MODER &=~ ( 1<<(PINPOS[pinNumber]) |  1<<(PINPOS[pinNumber]+1));
		  port->MODER |=  ( 0<<(PINPOS[pinNumber]) |  1<<(PINPOS[pinNumber]+1));
	  break;

		case ANALOG_MODE:
			port->MODER &=~ ( 1<<(PINPOS[pinNumber]) |  1<<(PINPOS[pinNumber]+1));
		  port->MODER |=  ( 1<<(PINPOS[pinNumber]) |  1<<(PINPOS[pinNumber]+1));
	  break;		
		
	}
	
}

void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state)
{
	if(state)
	{
		port->BSRR =(1<<pinNumber);
	}
	else
	{
		port->BSRR =(1<<(pinNumber+16));
	}

}

void gpio_toggel(GPIO_TypeDef *port, uint32_t pinNumber)
{
	port->ODR ^=(1<<pinNumber);

}

void gpio_init(GPIO_TYPE gpio_type)
{
	if(gpio_type.port == PORTA)
		CLOCK_EN_PORTA;
	
	if(gpio_type.port == PORTB)
		CLOCK_EN_PORTB;
	
	if(gpio_type.port == PORTC)
		CLOCK_EN_PORTC;
	
	if(gpio_type.port == PORTD)
		CLOCK_EN_PORTD;
	
	if(gpio_type.port == PORTE)
		CLOCK_EN_PORTE;
	
	if(gpio_type.port == PORTF)
		CLOCK_EN_PORTF;
	
	if(gpio_type.port == PORTG)
		CLOCK_EN_PORTG;
	
	if(gpio_type.port == PORTH)
		CLOCK_EN_PORTH;

config_pin(gpio_type.port,gpio_type.pin,gpio_type.mood);	
}


//**********************************************************************

void gpio_config_interrupt(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge)
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	if(port == PORTA)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA;
			break;
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PA;
			break;
			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PA;
			break;
			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PA;
			break;
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PA;
			break;
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PA;
			break;
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PA;
			break;
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PA;
			break;
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PA;
			break;
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PA;
			break;
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PA;
			break;
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PA;
			break;
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PA;
			break;
			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PA;
			break;
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PA;
			break;
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PA;
			break;
			
		}
	}
		
		if(port == PORTB)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PB;
			break;
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PB;
			break;
			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PB;
			break;
			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PB;
			break;
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PB;
			break;
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PB;
			break;
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PB;
			break;
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PB;
			break;
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PB;
			break;
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PB;
			break;
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PB;
			break;
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PB;
			break;
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PB;
			break;
			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PB;
			break;
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PB;
			break;
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PB;
			break;
			
		}
	}
		
		if(port == PORTC)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PC;
			break;
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PC;
			break;
			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PC;
			break;
			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PC;
			break;
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PC;
			break;
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PC;
			break;
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PC;
			break;
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PC;
			break;
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PC;
			break;
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PC;
			break;
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PC;
			break;
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PC;
			break;
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PC;
			break;
			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PC;
			break;
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PC;
			break;
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PC;
			break;
			
		}
	}
		
		if(port == PORTD)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PD;
			break;
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PD;
			break;
			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PD;
			break;
			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PD;
			break;
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PD;
			break;
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PD;
			break;
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PD;
			break;
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PD;
			break;
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PD;
			break;
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PD;
			break;
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PD;
			break;
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PD;
			break;
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PD;
			break;
			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PD;
			break;
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PD;
			break;
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PD;
			break;
			
		}
	}
		
		if(port == PORTE)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PE;
			break;
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PE;
			break;
			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PE;
			break;
			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PE;
			break;
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PE;
			break;
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PE;
			break;
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PE;
			break;
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PE;
			break;
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PE;
			break;
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PE;
			break;
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PE;
			break;
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PE;
			break;
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PE;
			break;
			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PE;
			break;
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PE;
			break;
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PE;
			break;
			
		}
	}
		
		if(port == PORTF)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PF;
			break;
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PF;
			break;
			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PF;
			break;
			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PF;
			break;
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PF;
			break;
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PF;
			break;
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PF;
			break;
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PF;
			break;
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PF;
			break;
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PF;
			break;
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PF;
			break;
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PF;
			break;
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PF;
			break;
			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PF;
			break;
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PF;
			break;
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PF;
			break;
			
		}
	}
	
		if(port == PORTG)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PG;
			break;
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PG;
			break;
			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PG;
			break;
			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PG;
			break;
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PG;
			break;
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PG;
			break;
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PG;
			break;
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PG;
			break;
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PG;
			break;
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PG;
			break;
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PG;
			break;
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PG;
			break;
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PG;
			break;
			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PG;
			break;
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PG;
			break;
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PG;
			break;
		}
	}
	
	if(edge ==RISING_EDGE)
		EXTI->RTSR1 |=(1<<pinNumber);
	
	if(edge==FALLING_EDGE)
		EXTI->FTSR1 |= (1<<pinNumber);
	
	if(edge==FALLING_RISING_EDGE)
	{
		EXTI->RTSR1 |=1<<pinNumber;
		EXTI->FTSR1 |= 1<<pinNumber;
	}
	
}


void enable_gpio_interrupt(uint32_t pinNumber,IRQn_Type irqNumber)
{
	EXTI->IMR1 |=(1<<pinNumber);
	NVIC_EnableIRQ(irqNumber);
}


void clear_gpio_interrupt(uint32_t pinNumber)
{
	EXTI->PR1 |=(1<<pinNumber);
}

void printm(const char *m, ...) {
    char b[80];
    #ifdef DEBUG_UART
    va_list arg;
    va_start(arg, m);
	  vsprintf(b, m, arg);

    for (int i = 0; i < strlen(b); i++) {
        while (!(USART2->ISR & USART_ISR_TXE));
			  USART2->TDR = b[i];
    }
    #endif
}
