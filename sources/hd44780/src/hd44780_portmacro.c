#include "globalincludefile.h"
#include "hd44780_portmacro.h"
#include "hd44780.h"



//------------------------------------------------------
// Delay
//------------------------------------------------------
void HD44780_Delay(uint32_t value)
{
    while(value--) ASM_NOP;
}



//------------------------------------------------------
// 74hc595 out byte
//------------------------------------------------------
void HC595_Write(uint8_t data)
{
    PIN_SH_L;
    PIN_ST_L;
    PIN_DS_L;

    for(uint8_t counter = 0; counter < 8; counter++) {
        if((data&1)) {
            PIN_DS_H;
            PIN_SH_H;
            PIN_SH_L;
        } else {
            PIN_DS_L;
            PIN_SH_H;
            PIN_SH_L;
        }
        data >>= 1;
    }

    PIN_ST_H;
}
