#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"



// Массив значений делителя для UART
uint16_t BR_UART[] = {
   SP_1200_CONST_UART,
    SP_2400_CONST_UART,
    SP_4800_CONST_UART,
    SP_9600_CONST_UART,
    SP_19200_CONST_UART,
    SP_38400_CONST_UART,
    SP_57600_CONST_UART,
    SP_115200_CONST_UART,
    SP_256000_CONST_UART
};



//------------------------------------------------------
// Initialize oscillator
//------------------------------------------------------
void Oscillator_Init(void)
{

}

//------------------------------------------------------
// Initialization GPIO
//------------------------------------------------------
void Port_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= (GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
}

//------------------------------------------------------
// UART
//------------------------------------------------------
void UART_Init(uint8_t Speed)
{
    // Включить тактирование порта А
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    // Включаем тактирование USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // PA10 (RX)
    // PA9  (TX)

    GPIOA->MODER   |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;          // PA9 (TX) - Alternate function mode
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9 | GPIO_OSPEEDER_OSPEEDR10;       // PA9 (TX) - High speed
    GPIOA->AFR[1]    |= 0x0110;                     // ????????????????????

    RCC->CFGR3     &= ~RCC_CFGR3_USART1SW;
    RCC->CFGR3     |=  RCC_CFGR3_USART1SW_0;        //System clock (SYSCLK) selected as USART1 clock


    USART1->CR1 &= ~USART_CR1_M;                    //Данные - 8 бит
    USART1->CR2 &= ~USART_CR2_STOP;                 //1 стоп-бит
    USART1->BRR = BR_UART[Speed];   //скорость usart
    USART1->CR1 |= USART_CR1_TE;                    //Включаем передатчик USART1
    USART1->CR1 |= USART_CR1_RE;                    //Включаем приемник USART1
    USART1->CR1 |= USART_CR1_UE;                    //Включаем USART1
    NVIC_SetPriority(USART1_IRQn, 1);
    NVIC_EnableIRQ(USART1_IRQn); // */
}

//------------------------------------------------------
// UART Write Byte
//------------------------------------------------------
void UART_Write_Byte(uint8_t data)
{
    while(!(USART1->ISR & USART_ISR_TC));
    USART1->TDR = data;
}

//------------------------------------------------------
// Timer 15 Init
//------------------------------------------------------
void Timer_6_Init(void)
{
    // Включаем тактирование
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    TIM6->PSC = 8 - 1;              // Настраиваем делитель что таймер тикал 1000 раз в секунду

    NVIC_SetPriority(TIM6_DAC_IRQn, 2);
    NVIC_EnableIRQ(TIM6_DAC_IRQn);  //Разрешение TIM6_DAC_IRQn прерывания
}

//------------------------------------------------------
// Запустить таймер
//------------------------------------------------------
void Timer_Start(uint16_t value)
{
    TIM6->CNT = 0;

    TIM6->ARR = value;              // Чтоб прерывание случалось раз в секунду

    TIM6->EGR |= TIM_EGR_UG;
    TIM6->SR &= ~TIM_SR_UIF;

    TIM6->DIER |= TIM_DIER_UIE;     // Разрешаем прерывание от таймера
    TIM6->CR1 |= TIM_CR1_CEN;       // Начать отсчёт!
}

//------------------------------------------------------
// Стоп таймер
//------------------------------------------------------
void Timer_Stop(void)
{
    TIM6->CNT = 0;
    TIM6->DIER &= ~TIM_DIER_UIE;
    TIM6->CR1 &= ~TIM_CR1_CEN;
}

//------------------------------------------------------
// Timer 15 Get Status flag
//------------------------------------------------------
void TIM6_DAC_IRQHandler(void)
{
    if((TIM6->SR & BIT0)) {
        TIM6->SR &= ~BIT0;
    }
}


