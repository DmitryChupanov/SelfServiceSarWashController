/**
  ******************************************************************************
  * @file    MyWH1602.h
  * @brief   This file contains headers of my functions.
  ******************************************************************************
*/

 /* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __MYWH1602_H
#define __MYWH1602_H

#include "stdint.h"

void WH1602Init(void (*msDelay)(uint32_t ms));
void MT_WH1602_Delay(uint32_t us);
typedef enum {
	RS_Comand = 0,
	RS_Data = 1,
} RSTypedef;
typedef enum {
	RW_Write = 0,
	RW_Read = 1,
} RWTypedef;
typedef enum {
	AdrDecrease = 0,
	AdrIncrease = 1,
} IncDecAdrTypedef;
typedef enum {
	ShiftNotPerform = 0,
	ShiftPerform = 1,
} ShiftTypedef;
typedef enum {
	DisplayOff = 0,
	DisplayOn = 1,
} DisplayOnOff;
typedef enum {
	CursorOff = 0,
	CursorOn = 1,
} CursorOnOff;
typedef enum {
	BlinkOff = 0,
	BlinkOn = 1,
} BlinkOnOff;
typedef enum {
	ShiftCursor = 0,
	ShiftDisplay = 1,
}SCbitTypedef;
typedef enum {
	ShiftLeft = 0,
	ShiftRight = 1,
}RLbitTypedef;
typedef enum {
	InterfaceData4bit = 0,
	InterfaceData8bit = 1,
}InterfaceDataTypedef;
typedef enum {
	DisplayOneLine = 0,
	DisplayTwoLine = 1,
}DisplayLineNumberTypedef;
typedef enum {
	Font5x8 = 0,
	Font5x11 = 1,
}FontTypeTypedef;


void WH1602_CursorOrDisplayShift(SCbitTypedef SCbit, RLbitTypedef RLbit);
void WH1602_EntryModeSet(IncDecAdrTypedef IDaddress, ShiftTypedef shift);
void WH1602SendByte(uint8_t DataByte, RSTypedef RS, RWTypedef RW);
void WH1602_ClearDisplay(void);
void WH1602_DisplayOnOff(DisplayOnOff Dbit, CursorOnOff Cbit, BlinkOnOff Bbit);
void WH1602_FunctionSet(InterfaceDataTypedef DLbit, DisplayLineNumberTypedef Nbit, FontTypeTypedef Fbit);
void WH1602_SetDDRAM_Address (uint8_t Address);
char WH1602_CodingSheme1(char Symbol);
void WH1602_Print (char *Str, uint8_t StringNumber, void (*DelayFc)(uint32_t Time), uint32_t DelTime);
void WH1602_Print2 (char *Str, uint8_t StringNumber, uint8_t SymbolNumber, uint8_t Len, void (*DelayFc)(uint32_t Time), uint32_t DelTime);




















#endif /* __MYWH1602_H */
