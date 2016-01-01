#ifndef HD44780_PORTMACRO
#define HD44780_PORTMACRO

#define DELAY_VALUE_ALL 500

#define PIN_RS_H    GPIOC->ODR |= GPIO_ODR_0;
#define PIN_RS_L    GPIOC->ODR &= ~GPIO_ODR_0;

#define PIN_E_H     GPIOC->ODR |= GPIO_ODR_1;
#define PIN_E_L     GPIOC->ODR &= ~GPIO_ODR_1;

#define PIN_SH_H    GPIOA->ODR |= GPIO_ODR_0;
#define PIN_SH_L    GPIOA->ODR &= ~GPIO_ODR_0;

#define PIN_ST_H    GPIOA->ODR |= GPIO_ODR_1;
#define PIN_ST_L    GPIOA->ODR &= ~GPIO_ODR_1;

#define PIN_DS_H    GPIOA->ODR |= GPIO_ODR_2;
#define PIN_DS_L    GPIOA->ODR &= ~GPIO_ODR_2;

#define ASM_NOP     __ASM("nop")



// Delay
//------------------------------------------------------
void HD44780_Delay(uint32_t value);
// 74hc595 out byte
//------------------------------------------------------
void HC595_Write(uint8_t data);

#endif // HD44780_PORTMACRO
