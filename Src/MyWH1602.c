#include "MyWH1602.h"
#include "stm32f103xe.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"


// void (*msDelay)(uint32_t ms) - Указатель на функцию, которой осуществляется милисекундная задержка 
// 
void WH1602Init(void (*msDelay)(uint32_t ms))
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;	// Включение тактирования порта F
	GPIOF->CRL = GPIO_CRL_MODE0_1|GPIO_CRL_MODE1_1|GPIO_CRL_MODE2_1|GPIO_CRL_MODE3_1|GPIO_CRL_MODE4_1|GPIO_CRL_MODE5_1|GPIO_CRL_MODE6_1|GPIO_CRL_MODE7_1; //10: Output mode, max speed 2 MHz.
	GPIOF->CRH |= GPIO_CRH_MODE8_1| GPIO_CRH_MODE9_1; //10: Output mode, max speed 2 MHz.
	GPIOF->CRH &= ~GPIO_CRH_CNF8_Msk;	// Режим Push Pull
	GPIOF->CRH &= ~GPIO_CRH_CNF9_Msk;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	// Включение тактирования порта A
	GPIOA->CRL |= GPIO_CRL_MODE1_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF1_Msk;
	msDelay(1000);
	//WH1602SendByte(0x3C, RS_Comand, RW_Write);
	WH1602_FunctionSet(InterfaceData8bit, DisplayTwoLine, Font5x11);
	msDelay(1);
	//WH1602SendByte(0x3C, RS_Comand, RW_Write);
	WH1602_FunctionSet(InterfaceData8bit, DisplayTwoLine, Font5x11);
	msDelay(1);
	//WH1602SendByte(0x0F, RS_Comand, RW_Write);
	WH1602_DisplayOnOff(DisplayOn, CursorOn, BlinkOn);
	msDelay(1);
	//WH1602SendByte(0x01, RS_Comand, RW_Write);
	WH1602_ClearDisplay();
	msDelay(2);
	//WH1602SendByte(0x06, RS_Comand, RW_Write);
	WH1602_EntryModeSet(AdrIncrease, ShiftNotPerform);
	msDelay(1);
}

//**************************************************************************************************
// Function      MT_WH1602_Delay()
// Description   Delay function
// Parameters    time - number of microseconds to wait
// RetVal	     	 None
//**************************************************************************************************
// Delay us function constants
#define MT_WH1602_DELAY_uS						(10000000)
#pragma push																						//Запоминаем уровень оптимизации
#pragma O0
void MT_WH1602_Delay(uint32_t us) 
{
  volatile uint32_t i;
  uint32_t HCLK_Frequency;
	
  HCLK_Frequency = HAL_RCC_GetHCLKFreq();
  i = (HCLK_Frequency/MT_WH1602_DELAY_uS)*us;
	
  for (; i != 0; i--);
}
#pragma pop	
//--------------------------------------------------------------------------------------------------------
//#pragma push																						//Запоминаем уровень оптимизации
//#pragma O0
// uint8_t DataByte - байт, который передается в дисплей
// RS = RS_Comand (0) значит в дисплей передается команда
// RS = RS_Data (1) значит в дисплей передаются данные
// RW = RW_Write (0) запись в дисплей
// RW = RW_Куфв (1) чтение из дисплея
// Delay value for strob impulse
#define MT_WH1602_DATA_RW_DELAY				2  //200
void WH1602SendByte(uint8_t DataByte, RSTypedef RS, RWTypedef RW)
{
	GPIOF->ODR &= 0xFFFFFC00;
	GPIOF->ODR |= (uint32_t) RS << 9;
	GPIOF->ODR |= (uint32_t) RW << 8;
	GPIOF->ODR |= (uint32_t) DataByte;
	
	GPIOA->ODR |= GPIO_ODR_ODR1;			// Тактовый импульс
	MT_WH1602_Delay(MT_WH1602_DATA_RW_DELAY);
	//osDelay(1);
	GPIOA->ODR &= ~GPIO_ODR_ODR1;
}
//#pragma pop	
//--------------------------------------------------------------------------------------------------------

//--------------------------------------- Очистка дисплея ------------------------------------------------
void WH1602_ClearDisplay(void)
{
	WH1602SendByte(0x01, RS_Comand, RW_Write);
}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
void MT_WH1602_ReturnHome(void)
{
	WH1602SendByte(0x02, RS_Comand, RW_Write);
}
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
// Function      MT_WH1602_EntryModeSet()
// Description   Sets the moving direction of cursor and display
// Parameters    IDaddress - increase or decrease DDRAM address
//													 if IDaddress is "High" - DDRAM address is increased by 1
//													 if IDaddress is "Low" - DDRAM address is decreased by 1	
//							 shift		 - shift of entire display
//													 if shift is "Low" - shift of entire display is not performed
//													 if shift is "High" and IDaddress is "High" - shift the display to the left
//													 if shift is "High" and IDaddress is "Low" - shift the display to the right
// RetVal	       None
void WH1602_EntryModeSet(IncDecAdrTypedef IDaddress, ShiftTypedef shift)
{
	uint8_t DataByte = 0x04;
	if (IDaddress == AdrIncrease)	DataByte |= 0x02;
	if (shift == ShiftPerform) DataByte |= 0x01;
	WH1602SendByte(DataByte, RS_Comand, RW_Write);
}
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
// Function      MT_WH1602_DisplayOnOff()
// Description   Controls display/cursor/blink ON/OFF
// Parameters    Dbit - display ON/OFF control bit
//							 Cbit - cursor ON/OFF control bit 
//							 Bbit - cursor blink ON/OFF control bit
// RetVal	       None
//**************************************************************************************************
void WH1602_DisplayOnOff(DisplayOnOff Dbit, CursorOnOff Cbit, BlinkOnOff Bbit)
{
	uint8_t DataByte = 0x08;
	if (Dbit == DisplayOn)
	{
		DataByte |= 0x04;
	}
	if (Cbit == CursorOn)
	{
		DataByte |= 0x02;
	}
	if (Bbit == BlinkOn)
	{
		DataByte |= 0x01;
	}
	WH1602SendByte(DataByte, RS_Comand, RW_Write);
}
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
// Function      MT_WH1602_CursorOrDisplayShift()
// Description   Cursor return home instruction
// Parameters    SCbit 
//    					 RLbit 
//							 ----------------------------------------------------------------------------------
//							 SCbit | RLbit | Description 																										
//							 Low	 | Low   | Shift cursor to the left																							
//							 Low	 | High  | Shift cursor to the right
//							 High	 | Low   | Shift display to the left. Cursor follows the display shift		
//							 High	 | High  | Shift display to the right. Cursor follows the display shift	
//							 ----------------------------------------------------------------------------------			
// RetVal	       None
//**************************************************************************************************
void WH1602_CursorOrDisplayShift(SCbitTypedef SCbit, RLbitTypedef RLbit)
{
	uint8_t DataByte = 0x10;
	if (SCbit == ShiftDisplay) DataByte |= 0x08;
	if (RLbit == ShiftRight) DataByte |= 0x04;
	WH1602SendByte(DataByte, RS_Comand, RW_Write);
}
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
// Function      MT_WH1602_FunctionSet()
// Description   Sets interface data length and controls display line number and font type
// Parameters    DLbit - interface data length control bit 
//    					 Nbit  - display line number control bit
//         			 Fbit  - display font type control bit
//							 ----------------------------------------------------------------------------------
//							 SCbit | RLbit | Display Lines | Font | Duty factor 																								
//							 Low	 | Low   |		   1			 | 5x8	|			 1/8																
//							 Low	 | High  |		   1			 | 5x11 |			 1/11
//							 High	 | Low   |		   2			 | 5x8  |      1/16
//							 ----------------------------------------------------------------------------------			
// RetVal	       None
//**************************************************************************************************
void WH1602_FunctionSet(InterfaceDataTypedef DLbit, DisplayLineNumberTypedef Nbit, FontTypeTypedef Fbit)
{
	uint8_t DataByte = 0x30;
	if (DLbit == InterfaceData8bit) DataByte |= 0x10;
	if (Nbit == DisplayTwoLine) DataByte |= 0x08;
	if (Fbit == Font5x11) DataByte |= 0x04;
	WH1602SendByte(DataByte, RS_Comand, RW_Write);
}
//*********************************************************************************************************
//************************* Устанавливает куда писать символ на дисплее ***********************************
// 0x00 - первая строка
// 0x40 - вторая строка
void WH1602_SetDDRAM_Address (uint8_t Address)
{
	Address |= 0x80;
	WH1602SendByte(Address, RS_Comand, RW_Write);
}
//*********************************************************************************************************
//*************************** Возвращант символ в кодировке WH1602D-TML-CT# *******************************
char WH1602_CodingSheme1(char Symbol)
{
	static char RetVal = 0;
	RetVal = 0;
	switch (Symbol){
		case ' ' : RetVal = 0x20; break;
		case 'А' : RetVal = 65; break;
		case 'а' : RetVal = 97; break;
		case 'Б' : RetVal = 160; break;
		case 'б' : RetVal = 178; break;
		case 'В' : RetVal = 66; break;
		case 'в' : RetVal = 179; break;
		case 'Г' : RetVal = 161; break;
		case 'г' : RetVal = 180; break;
		case 'Д' : RetVal = 224; break;
		case 'д' : RetVal = 227; break;
		case 'Е' : RetVal = 69; break;
		case 'е' : RetVal = 101; break;
		case 'Ж' : RetVal = 163; break;
		case 'ж' : RetVal = 182; break;
		case 'З' : RetVal = 164; break;
		case 'з' : RetVal = 183; break;
		case 'И' : RetVal = 165; break;
		case 'и' : RetVal = 184; break;
		case 'К' : RetVal = 75; break;
		case 'к' : RetVal = 186; break;
		case 'Л' : RetVal = 167; break;
		case 'л' : RetVal = 187; break;
		case 'М' : RetVal = 77; break;
		case 'м' : RetVal = 188; break;
		case 'Н' : RetVal = 72; break;
		case 'н' : RetVal = 189; break;
		case 'О' : RetVal = 79; break;
		case 'о' : RetVal = 111; break;
		case 'П' : RetVal = 168; break;
		case 'п' : RetVal = 190; break;
		case 'Р' : RetVal = 80; break;
		case 'р' : RetVal = 112; break;
		case 'С' : RetVal = 67; break;
		case 'с' : RetVal = 99; break;
		case 'Т' : RetVal = 84; break;
		case 'т' : RetVal = 191; break;
		case 'У' : RetVal = 89; break;
		case 'у' : RetVal = 121; break;
		case 'Ф' : RetVal = 170; break;
		case 'ф' : RetVal = 228; break;
		case 'Х' : RetVal = 88; break;
		case 'х' : RetVal = 120; break;
		case 'Ц' : RetVal = 225; break;
		case 'ц' : RetVal = 229; break;
		case 'Ч' : RetVal = 171; break;
		case 'ч' : RetVal = 192; break;
		case 'Ш' : RetVal = 172; break;
		case 'ш' : RetVal = 193; break;
		case 'Щ' : RetVal = 226; break;
		case 'щ' : RetVal = 230; break;
		case 'Ъ' : RetVal = 173; break;
		case 'ъ' : RetVal = 194; break;
		case 'Ы' : RetVal = 174; break;
		case 'ы' : RetVal = 195; break;
		case 'Ь' : RetVal = 196; break;
		case 'ь' : RetVal = 196; break;
		case 'Э' : RetVal = 175; break;
		case 'э' : RetVal = 197; break;
		case 'Ю' : RetVal = 176; break;
		case 'ю' : RetVal = 198; break;
		case 'Я' : RetVal = 177; break;
		case 'я' : RetVal = 199; break;
		case '0' : RetVal = 48; break;
		case '1' : RetVal = 49; break;
		case '2' : RetVal = 50; break;
		case '3' : RetVal = 51; break;
		case '4' : RetVal = 52; break;
		case '5' : RetVal = 53; break;
		case '6' : RetVal = 54; break;
		case '7' : RetVal = 55; break;
		case '8' : RetVal = 56; break;
		case '9' : RetVal = 57; break;
		case '\x18' : RetVal = 217; break;
		case '\x19' : RetVal = 218; break;
		default : RetVal = Symbol;
	}
	
	return RetVal;
}
//*********************************************************************************************************
//*********************************************************************************************************
//char *Str - указатель на сторку, которую нужно печатать
//uint8_t StringNumber - номер строки дисплея, куда нужно печатать
//void (*DelayFc)(uint32_t Time) - указатель на функцию задержки
//uint32_t DelTime - задержка. 1 хватит
void WH1602_Print (char *Str, uint8_t StringNumber, void (*DelayFc)(uint32_t Time), uint32_t DelTime)
{
	if(StringNumber == 1)
	{
		WH1602_SetDDRAM_Address (0x00);
		DelayFc(DelTime);
	}
	else if(StringNumber == 2)
	{
		WH1602_SetDDRAM_Address (0x40);
		DelayFc(DelTime);
	}
	uint8_t i = 0;
	for(; i < 16; i++)
	{
		char Smb = WH1602_CodingSheme1(*(Str + i));
		if (Smb == 0) break;
		WH1602SendByte(Smb, RS_Data, RW_Write);
		DelayFc(DelTime);
	}
	while (i<16)
	{
		WH1602SendByte(' ', RS_Data, RW_Write);
		i++;
		DelayFc(DelTime);
	}
}
//*********************************************************************************************************
//*********************************************************************************************************
// char *Str - надпись, которую нужно печатать на дисплей
// uint8_t StringNumber - номер строки дисплея (1 или 2) куда выводятся данные
// uint8_t SymbolNumber - номер символа на дисплее, начиная с которого нужно выводить данные (столбец)
// uint8_t Len - количество символов, которые нужно вывести
// void (*DelayFc)(uint32_t Time) - указатель на функцию с помощью которой осуществляется задержка в 1 мс
// uint32_t DelTime - величина этой задержки
void WH1602_Print2 (char *Str, uint8_t StringNumber, uint8_t SymbolNumber, uint8_t Len, void (*DelayFc)(uint32_t Time), uint32_t DelTime)
{
	if(StringNumber == 1)
	{
		WH1602_SetDDRAM_Address (SymbolNumber);
		DelayFc(DelTime);
	}
	else if(StringNumber == 2)
	{
		WH1602_SetDDRAM_Address (SymbolNumber | 0x40);
		DelayFc(DelTime);
	}
	uint8_t i = 0;
	for(; i < Len; i++)
	{
		char Smb = WH1602_CodingSheme1(*(Str + i));
		if (Smb == 0) Smb = ' ';
		WH1602SendByte(Smb, RS_Data, RW_Write);
		DelayFc(DelTime);
	}
}
//*********************************************************************************************************
//*********************************************************************************************************











//*
