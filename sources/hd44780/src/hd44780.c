#include "globalincludefile.h"
#include "hd44780_portmacro.h"
#include "hd44780.h"



//------------------------------------------------------
// HD44780 Init command
//------------------------------------------------------
void HD44780_CMD(uint8_t command)
{
    PIN_RS_L;
    HD44780_Delay(DELAY_VALUE_ALL);
    HC595_Write(command);
    PIN_E_H;
    HD44780_Delay(DELAY_VALUE_ALL);
    PIN_E_L;
}

//------------------------------------------------------
// HD44780 Write Byte
//------------------------------------------------------
void HD44780_Write_Byte(uint8_t data)
{
    PIN_RS_H;
    HD44780_Delay(DELAY_VALUE_ALL);
    PIN_E_H;
    HD44780_Delay(DELAY_VALUE_ALL);
    HC595_Write(data);
    PIN_RS_H;
    HD44780_Delay(DELAY_VALUE_ALL);
    PIN_E_L;
}

//------------------------------------------------------
// HD44780 Cursor Position
//------------------------------------------------------
void HD44780_Cursor_Position(uint8_t position)
{
    HD44780_CMD(position | BIT7);
}

//------------------------------------------------------
// HD44780 Line Position
//------------------------------------------------------
void HD44780_Line_Position(uint8_t line_position)
{
    if(line_position == 0) HD44780_Cursor_Position(ADDR_LINE_0);
    if(line_position == 1) HD44780_Cursor_Position(ADDR_LINE_1);
    if(line_position == 2) HD44780_Cursor_Position(ADDR_LINE_2);
    if(line_position == 3) HD44780_Cursor_Position(ADDR_LINE_3);
}
