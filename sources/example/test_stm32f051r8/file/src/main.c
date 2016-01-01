#include "globalincludefile.h"
#include "main.h"
#include "phisic.h"
#include "hd44780.h"
#include "onewire_master.h"


//------------------------------------------------------
// Hardware initialization
//------------------------------------------------------
void Hardware_Init(void)
{
    // Initialize oscillator
    Oscillator_Init();
    // Initialization GPIO
    Port_Init();
    // enable irq
    __enable_irq();
}

struct OneWire_IO test_IO;
uint8_t data[10];

struct temp {
    int16_t temp_H : 12;
    uint8_t temp_L : 4;
    float temp_float;
};

//------------------------------------------------------
// MAIN
//------------------------------------------------------
int main(void)
{
    // Hardware initialization
    Hardware_Init();
    Timer_6_Init();
    UART_Init(SP_9600);
    xdev_out(HD44780_Write_Byte);

    test_IO.pMODER = &GPIOC->MODER;
    test_IO.pIDR = &GPIOC->IDR;
    test_IO.pODR = &GPIOC->ODR;
    test_IO.BinPinMODE = GPIO_MODER_MODER6_0;
    test_IO.BinPinData = GPIO_ODR_6;
    test_IO.pTimer_Start = Timer_Start;
    test_IO.pTimer_Stop = Timer_Stop;

    HD44780_CMD(D_SET);
    HD44780_CMD(I_D_SET);
    HD44780_CMD(CLEAR);
    HD44780_CMD(RETURN);
    HD44780_CMD(DL_SET | N_SET);

    HD44780_Cursor_Position(0);

    GPIOA->ODR &= ~GPIO_ODR_3;

    while(1) {
        HD44780_Cursor_Position(40);
        OneWire_Presence(&test_IO);
        while(OneWire_Status(&test_IO));

        if(!test_IO.Status.RxTxData) {
            OneWire_Write_Byte(&test_IO, 0xcc);
            while(OneWire_Status(&test_IO));

            OneWire_Write_Byte(&test_IO, 0x44);
            while(OneWire_Status(&test_IO));

            Deley_uS(&test_IO, 65530);
            Deley_uS(&test_IO, 65530);
            Deley_uS(&test_IO, 65530);
            Deley_uS(&test_IO, 65530);
            Deley_uS(&test_IO, 65530);


            OneWire_Presence(&test_IO);
            while(OneWire_Status(&test_IO));

            OneWire_Write_Byte(&test_IO, 0xcc);
            while(OneWire_Status(&test_IO));

            OneWire_Write_Byte(&test_IO, 0xbe);
            while(OneWire_Status(&test_IO));

            for(uint8_t counter = 0; counter < 8; counter++) {
                OneWire_Read_Byte(&test_IO);
                while(OneWire_Status(&test_IO));
                data[counter] = test_IO.Status.RxTxData;
            }


            uint16_t temp = JOIN_16(data[1], data[0]);


            struct temp Temp;
            Temp.temp_H = temp >> 4;
            Temp.temp_L = temp;

            uint16_t temperature = Temp.temp_L;
            //преобразуем в целое число
            temperature = (temperature<<1) + (temperature<<3);// Умножаем на 10
            temperature = (temperature>>4);//делим на 16 или умножаем на 0.0625

            xdev_out(HD44780_Write_Byte);
            xprintf("Temp = %d.%-4d", Temp.temp_H, Temp.temp_L);
        } else {
            xprintf("Error 1-Wire");
        }
        GPIOC->ODR ^= GPIO_ODR_8;
    }
}

