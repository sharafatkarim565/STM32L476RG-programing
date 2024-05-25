#ifndef HAL_GPIO
#define HAL_GPIO

#include "stm32l4xx.h"

#define DEBUG_UART

#define LOW   0
#define HIGH  1


//define gpio as port 
#define PORTA			GPIOA
#define PORTB			GPIOB  
#define PORTC			GPIOC  
#define PORTD			GPIOD  
#define PORTE			GPIOE  
#define PORTF			GPIOF  
#define PORTG			GPIOG 
#define PORTH			GPIOH 

//pin mode
#define INPUT_MODE			        ((uint32_t) 0x00)
#define GEN_PUR_OUTPUT_MODE			((uint32_t) 0x01)
#define ALT_FUN_MODE						((uint32_t) 0x02)
#define ANALOG_MODE 						((uint32_t) 0x03)

//clocl enable
#define CLOCK_EN_PORTA          (RCC->AHB2ENR |=(1<<0))
#define CLOCK_EN_PORTB          (RCC->AHB2ENR |=(1<<1))
#define CLOCK_EN_PORTC          (RCC->AHB2ENR |=(1<<2))
#define CLOCK_EN_PORTD          (RCC->AHB2ENR |=(1<<3))
#define CLOCK_EN_PORTE          (RCC->AHB2ENR |=(1<<4))
#define CLOCK_EN_PORTF          (RCC->AHB2ENR |=(1<<5))
#define CLOCK_EN_PORTG          (RCC->AHB2ENR |=(1<<6))
#define CLOCK_EN_PORTH          (RCC->AHB2ENR |=(1<<7))



typedef struct
{
	GPIO_TypeDef *port;
	uint32_t        pin;
	uint32_t       mood;
	
}GPIO_TYPE ;

typedef enum
{
	RISING_EDGE,
	FALLING_EDGE,
	FALLING_RISING_EDGE
}edge_select ;



//***********************************************

static void config_pin(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mood);

void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state);
void gpio_toggel(GPIO_TypeDef *port, uint32_t pinNumber);
void gpio_init(GPIO_TYPE gpio_type);

void gpio_config_interrupt(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge);
void enable_gpio_interrupt(uint32_t pinNumber,IRQn_Type irqNumber);
void clear_gpio_interrupt(uint32_t pinNumber);
void printm(const char *m, ...);





#endif