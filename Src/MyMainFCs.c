#include "MyMainFCs.h"
#include "MyVendotek.h"
#include "stm32f1xx_hal.h"
#include "MyWH1602.h"
#include "cmsis_os.h"
#include "MyCommon_FCs.h"
#include "stm32f1xx_hal_flash_ex.h"
#include "MyRTC.h"
extern DateAndTimeTypeDef CurrentDateAndTime;
/************************************************* Обработчик нажатия кнопок *******************************************************************/
void ButtonControl(ButtonStateTypeDef* BI, GPIO_TypeDef* Port, uint16_t Pin, uint32_t* BICounter)
{
	if((HAL_GPIO_ReadPin(Port,Pin) == GPIO_PIN_SET)&&(*BICounter < 100))
	{
		*BICounter += 1;
	}
	else if((HAL_GPIO_ReadPin(Port,Pin) == GPIO_PIN_RESET)&&(*BICounter > 0))
	{
		*BICounter -= 1;
	}
	if(*BICounter == 100)
	{
		*BI = ButtonSet;
	}
	if(*BICounter == 0)
	{
		*BI = ButtonReset;
	}
}

void ButtonsHandler(void)
{
	//-------------------------------------------- Кнопка Вверх --------------------------------------------------
		if((HAL_GPIO_ReadPin(ButtonUp_GPIO_Port,ButtonUp_Pin) == GPIO_PIN_RESET)&&(ButtonUpCounter < 70))
		{
			ButtonUpCounter++;
		}
		else if((HAL_GPIO_ReadPin(ButtonUp_GPIO_Port,ButtonUp_Pin) == GPIO_PIN_SET)&&(ButtonUpCounter > 0))
		{
			ButtonUpCounter--;
		}
		if(ButtonUpCounter == 70)
		{
			ButtonUp = ButtonSet;
		}
		if(ButtonUpCounter == 0)
		{
			ButtonUp = ButtonReset;
		}
		//---------------------------------------------- Кнопка Ok ----------------------------------------------------
		if((HAL_GPIO_ReadPin(ButtonOk_GPIO_Port,ButtonOk_Pin) == GPIO_PIN_RESET)&&(ButtonOkCounter < 70))
		{
			ButtonOkCounter++;
		}
		else if((HAL_GPIO_ReadPin(ButtonOk_GPIO_Port,ButtonOk_Pin) == GPIO_PIN_SET)&&(ButtonOkCounter > 0))
		{
			ButtonOkCounter--;
		}
		if(ButtonOkCounter == 70)
		{
			ButtonOk = ButtonSet;
		}
		if(ButtonOkCounter == 0)
		{
			ButtonOk = ButtonReset;
		}
		//---------------------------------------------- Кнопка Вниз ---------------------------------------------------
		if((HAL_GPIO_ReadPin(ButtonDown_GPIO_Port,ButtonDown_Pin) == GPIO_PIN_RESET)&&(ButtonDownCounter < 70))
		{
			ButtonDownCounter++;
		}
		else if((HAL_GPIO_ReadPin(ButtonDown_GPIO_Port,ButtonDown_Pin) == GPIO_PIN_SET)&&(ButtonDownCounter > 0))
		{
			ButtonDownCounter--;
		}
		if(ButtonDownCounter == 70)
		{
			ButtonDown = ButtonSet;
		}
		if(ButtonDownCounter == 0)
		{
			ButtonDown = ButtonReset;
		}
		//---------------------------------------------- Кнопка Влево ---------------------------------------------------
		if((HAL_GPIO_ReadPin(ButtonLeft_GPIO_Port,ButtonLeft_Pin) == GPIO_PIN_RESET)&&(ButtonLeftCounter < 100))
		{
			ButtonLeftCounter++;
		}
		else if((HAL_GPIO_ReadPin(ButtonLeft_GPIO_Port,ButtonLeft_Pin) == GPIO_PIN_SET)&&(ButtonLeftCounter > 0))
		{
			ButtonLeftCounter--;
		}
		if(ButtonLeftCounter == 300)
		{
			ButtonLeft = ButtonSet;
		}
		if(ButtonLeftCounter == 0)
		{
			ButtonLeft = ButtonReset;
		}
		//---------------------------------------------- Кнопка Влево ---------------------------------------------------
		if((HAL_GPIO_ReadPin(ButtonRight_GPIO_Port,ButtonRight_Pin) == GPIO_PIN_RESET)&&(ButtonRightCounter < 100))
		{
			ButtonRightCounter++;
		}
		else if((HAL_GPIO_ReadPin(ButtonRight_GPIO_Port,ButtonRight_Pin) == GPIO_PIN_SET)&&(ButtonRightCounter > 0))
		{
			ButtonRightCounter--;
		}
		if(ButtonRightCounter == 300)
		{
			ButtonRight = ButtonSet;
		}
		if(ButtonRightCounter == 0)
		{
			ButtonRight = ButtonReset;
		}
		/********************************** Дальше идут клиентские кнопки *******************************/
		
		//----------------------------------------- Кнопка Vendoteck+ -----------------------------------
		static uint32_t BI1Counter = 0;
		ButtonControl(&BI1, BI1_GPIO_Port, BI1_Pin, &BI1Counter);
		//----------------------------------------- Кнопка VendoteckOK ----------------------------------
		static uint32_t BI2Counter = 0;
		ButtonControl(&BI2, BI2_GPIO_Port, BI2_Pin, &BI2Counter);
		//----------------------------------------- Кнопка Vendoteck- -----------------------------------
		static uint32_t BI3Counter = 0;
		ButtonControl(&BI3, BI3_GPIO_Port, BI3_Pin, &BI3Counter);
		//-------------------------------------------- Кнопка Payse -------------------------------------
		static uint32_t BI4Counter = 0;
		ButtonControl(&BI4, BI4_GPIO_Port, BI4_Pin, &BI4Counter);
		//-------------------------------------------- Кнопка 5 -----------------------------------------
		static uint32_t BI5Counter = 0;
		ButtonControl(&BI5, BI5_GPIO_Port, BI5_Pin, &BI5Counter);
		//-------------------------------------------- Кнопка 6 -----------------------------------------
		static uint32_t BI6Counter = 0;
		ButtonControl(&BI6, BI6_GPIO_Port, BI6_Pin, &BI6Counter);
		//-------------------------------------------- Кнопка 7 -----------------------------------------
		static uint32_t BI7Counter = 0;
		ButtonControl(&BI7, BI7_GPIO_Port, BI7_Pin, &BI7Counter);
		//-------------------------------------------- Кнопка 8 -----------------------------------------
		static uint32_t BI8Counter = 0;
		ButtonControl(&BI8, BI8_GPIO_Port, BI8_Pin, &BI8Counter);
		//-------------------------------------------- Кнопка 9 -----------------------------------------
		static uint32_t BI9Counter = 0;
		ButtonControl(&BI9, BI9_GPIO_Port, BI9_Pin, &BI9Counter);
		//-------------------------------------------- Кнопка 10 -----------------------------------------
		static uint32_t BI10Counter = 0;
		ButtonControl(&BI10, BI10_GPIO_Port, BI10_Pin, &BI10Counter);
		//-------------------------------------------- Кнопка 11 -----------------------------------------
		static uint32_t BI11Counter = 0;
		ButtonControl(&BI11, BI11_GPIO_Port, BI11_Pin, &BI11Counter);
//		//-------------------------------------------- Кнопка 12 -----------------------------------------
//		static uint32_t BI12Counter = 0;
//		ButtonControl(&BI12, BI12_GPIO_Port, BI12_Pin, &BI12Counter);
//		//-------------------------------------------- Кнопка 13 -----------------------------------------
//		static uint32_t BI13Counter = 0;
//		ButtonControl(&BI13, BI13_GPIO_Port, BI13_Pin, &BI13Counter);
//		//-------------------------------------------- Кнопка 14 -----------------------------------------
//		static uint32_t BI14Counter = 0;
//		ButtonControl(&BI14, BI14_GPIO_Port, BI14_Pin, &BI14Counter);
//		//-------------------------------------------- Кнопка 15 -----------------------------------------
//		static uint32_t BI15Counter = 0;
//		ButtonControl(&BI15, BI15_GPIO_Port, BI15_Pin, &BI15Counter);
//		//-------------------------------------------- Кнопка 16 -----------------------------------------
//		static uint32_t BI16Counter = 0;
//		ButtonControl(&BI16, BI16_GPIO_Port, BI16_Pin, &BI16Counter);
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
// uint32_t* FirstParametr - указатель на первый редактируемый параметр. Последовательно за ним должны идти все остальные параметры
void PiMenuImplementation(uint32_t* FirstParametr)
{
	uint8_t MyTmpStr[11];
			static uint8_t Editing = 0;		// флаг того, что сейчас происходит редактирование значения в сторке 0 - нет редактирования 1 - редактирование в процессе
			static ButtonStateTypeDef OldButtonOkState = ButtonSet;
			if(((PIMenuString == 0)||(PIMenuString == 1))&&(OldButtonOkState == ButtonReset)&&(ButtonOk == ButtonSet))	// Включение/отключение редактирования параметра
			{
					if(Editing == 0)
					{
						Editing = 1;
						WH1602_Print2 ("\x18", 1, 10, 1, (void (*)())osDelay, 1);	// Отображение стрелки вверх перед редактируемой величиной
						WH1602_Print2 ("\x19", 1, 15, 1, (void (*)())osDelay, 1);	// Отображение стрелки вниз после редактируемой величины
					}
					else
					{
						Editing = 0;
						WH1602_Print2 (" ", 1, 10, 1, (void (*)())osDelay, 1);	// Стирание стрелок до и после редактируемых величин
						WH1602_Print2 (" ", 1, 15, 1, (void (*)())osDelay, 1);
					}
			}
			OldButtonOkState = ButtonOk;
			
			//************* Обработка кнопки вверх ****
			static ButtonStateTypeDef OldButtonUpState;
			if((OldButtonUpState == ButtonReset)&&(ButtonUp == ButtonSet)&&(Editing == 0))
			{
				PIMenuString = (PIMenuString > 0) ? --PIMenuString : 0 ;
			}
			OldButtonUpState = ButtonUp;
			
			static uint32_t ButtonUpCounterEditing;
			if(Editing == 1)
			{
				if(ButtonUp == ButtonSet)
				{
					ButtonUpCounterEditing = (ButtonUpCounterEditing < 100) ? ++ButtonUpCounterEditing : 0;
					if(ButtonUpCounterEditing == 0) 
					{
						*(FirstParametr+PIMenuString) += 1;
						Hex32ToDecASCII (*(FirstParametr+PIMenuString), MyTmpStr);
						WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
						WH1602_SetDDRAM_Address (0x10);
					}
				}
				else
				{
					ButtonUpCounterEditing = 0;
				}
			}
			
			//************* Обработка кнопки вниз ****		
			static ButtonStateTypeDef OldButtonDownState;
			if((OldButtonDownState == ButtonReset)&&(ButtonDown == ButtonSet)&&(Editing == 0))
			{
				PIMenuString = (PIMenuString < 2) ? ++PIMenuString : 0 ;
			}
			OldButtonDownState = ButtonDown;
			
			static uint32_t ButtonDownCounterEditing;
			if(Editing == 1)
			{
				if(ButtonDown == ButtonSet)
				{
					ButtonDownCounterEditing = (ButtonDownCounterEditing < 100) ? ++ButtonDownCounterEditing : 0;
					if(ButtonDownCounterEditing == 0) 
					{
						*(/*&Settings.ImpulsePricePI3*/FirstParametr+PIMenuString) -= 1;
						//uint8_t MyTmpStr[11];
						Hex32ToDecASCII (*(/*&Settings.ImpulsePricePI3*/FirstParametr+PIMenuString), MyTmpStr);
						WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
						WH1602_SetDDRAM_Address (0x10);
					}
				}
				else
				{
					ButtonDownCounterEditing = 0;
				}
			}
			
			
			//***************** Пролиствыание меню вверх вниз ***********
			
			static uint32_t OldPI3MenuString = 3;
			if((OldPI3MenuString != PIMenuString))
			{
				WH1602_Print ((char*)&PIMenyStrings+(16*PIMenuString), 1, (void (*)())osDelay, 1);
				WH1602_Print ((char*)&PIMenyStrings.ImpulsePricePI+(16*PIMenuString)+16, 2, (void (*)())osDelay, 1);
				
				//uint8_t MyTmpStr[11];
				if(PIMenuString < 2)
				{
					Hex32ToDecASCII (*(FirstParametr + PIMenuString), MyTmpStr);
					WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
				}
				if(PIMenuString <1)
				{
					Hex32ToDecASCII (*(FirstParametr + PIMenuString + 1), MyTmpStr);
					WH1602_Print2 ((char*)MyTmpStr, 2, 11, 4, (void (*)())osDelay, 1);
				}
				WH1602_SetDDRAM_Address (0x10);
				OldPI3MenuString = PIMenuString;
			}

			
			if((PIMenuString == 2)&&(ButtonOk == ButtonSet))	// Выход из меню настройки импульсных входов
			{
//				HAL_FLASH_Unlock();
//				// FLASH_Erase Page
//				while( FLASH->SR&FLASH_SR_BSY ) {}
//				FLASH->CR |= FLASH_CR_PER; //Page Erase Set
//				FLASH->AR = 0x0807F800;//Page_127; //Page Address
//				FLASH->CR |= FLASH_CR_STRT; //Start Page Erase
//				while( FLASH->SR&FLASH_SR_BSY ) {}
//				FLASH->CR &= ~FLASH_CR_PER; //Page Erase Clear
//				FLASH->CR |= FLASH_CR_PG; // FLASH_Program HalfWord
//				while( FLASH->SR&FLASH_SR_BSY ) {}
//				//************************************
//				uint32_t SettingsSize = sizeof(Settings) / 4;
//				for(uint32_t i = 0; i < SettingsSize; i++)
//				{
//					HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (0x0807F800 + (i*4)), *(&Settings.ImpulsePricePI3+i));
//				}
//				HAL_FLASH_Lock();
				SaveSettingsToFlash(SettingsFlashAddress, &Settings.ImpulsePricePI3, (sizeof(Settings) / 4));
					
				PIMenuString = 0;
				OldPI3MenuString = 3;
				MenuLst = SetingsMenu;
				SetingsMenuString = 0;
				OldSetingsMenuString = SetingsMenuString +1;
				ButtonOk = ButtonReset;
				ButtonOkCounter = 0;
			}
	
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
#define LastClientModeMenuStreeng 15
void ClientModeMenuImplementation(char* FirstString, uint32_t* FirstParametr)
{
	static ButtonStateTypeDef OldButtonUpState;
	static uint32_t ClientModeMenuString = 0;
	static uint32_t OldClientModeMenuString = 1;
	static uint8_t Editing_ = 0;
	uint8_t MyTmpStr1[11];
	if((OldButtonUpState == ButtonReset)&&(ButtonUp == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString > 0) ? --ClientModeMenuString : 0 ;
	}
	OldButtonUpState = ButtonUp;
	
	static ButtonStateTypeDef OldButtonDownState;
	if((OldButtonDownState == ButtonReset)&&(ButtonDown == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString < LastClientModeMenuStreeng) ? ++ClientModeMenuString : LastClientModeMenuStreeng ;
	}
	OldButtonDownState = ButtonDown;
	
	if(OldClientModeMenuString != ClientModeMenuString)
	{
		//----------- Печать первой строки -----------
		if(ClientModeMenuString == 0)
		{
			WH1602_Print (FirstString, 1, (void (*)())osDelay, 1);	// Печать названия заголовка подменю из аргумента функции
		}
		else if(ClientModeMenuString == LastClientModeMenuStreeng)
		{
			WH1602_Print ((char*)&ClM_MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);
		}
		else
		{
			WH1602_Print ((char*)&ClM_MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);
			
			if((ClientModeMenuString == 3)||(ClientModeMenuString == 6)||(ClientModeMenuString == 9)||(ClientModeMenuString == 12))
			{
				if(*(FirstParametr + ClientModeMenuString-1) == 0) WH1602_Print2 ("Откл", 1, 11, 4, (void (*)())osDelay, 1);
				else if(*(FirstParametr + ClientModeMenuString-1) == 1) WH1602_Print2 ("Реле", 1, 11, 4, (void (*)())osDelay, 1);
				else if(*(FirstParametr + ClientModeMenuString-1) == 2) WH1602_Print2 ("Доз ", 1, 11, 4, (void (*)())osDelay, 1);
			}
			else
			{
				Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString-1), MyTmpStr1);
				WH1602_Print2 ((char*)MyTmpStr1, 1, 11, 4, (void (*)())osDelay, 1);
			}
		}
		//----------- Печать второй строки -----------
		if(ClientModeMenuString < LastClientModeMenuStreeng-1)
		{
			WH1602_Print ((char*)&ClM_MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
			if((ClientModeMenuString == 2)||(ClientModeMenuString == 5)||(ClientModeMenuString == 8)||(ClientModeMenuString == 11))
			{
				if(*(FirstParametr + ClientModeMenuString) == 0) WH1602_Print2 ("Откл", 2, 11, 4, (void (*)())osDelay, 1);
				else if(*(FirstParametr + ClientModeMenuString) == 1) WH1602_Print2 ("Реле", 2, 11, 4, (void (*)())osDelay, 1);
				else if(*(FirstParametr + ClientModeMenuString) == 2) WH1602_Print2 ("Доз ", 2, 11, 4, (void (*)())osDelay, 1);
			}
			else
			{
				Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString), MyTmpStr1);
				WH1602_Print2 ((char*)MyTmpStr1, 2, 11, 4, (void (*)())osDelay, 1);
			}
		}
		else
		{
			WH1602_Print ((char*)&ClM_MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
		}
		
		if(ClientModeMenuString == 0)
		{
			WH1602_SetDDRAM_Address (0x10);
		}
		else
		{
			WH1602_SetDDRAM_Address (0x0F);
		}
		OldClientModeMenuString = ClientModeMenuString;
	}
	
	
		static ButtonStateTypeDef OldButtonOkState = ButtonReset;
		if((ClientModeMenuString > 0)&&(ClientModeMenuString < LastClientModeMenuStreeng)&&(OldButtonOkState == ButtonReset)&&(ButtonOk == ButtonSet))	// Вкл/откл режима редактирования параметра
		{
			//----------------------- Включение режима редактирования параметра ----------------------
			if(Editing_ == 0)
			{
				Editing_ = 1;
				WH1602_Print2 ("\x18", 1, 10, 1, (void (*)())osDelay, 1);	// Отображение стрелки вверх перед редактируемой величиной
				WH1602_Print2 ("\x19", 1, 15, 1, (void (*)())osDelay, 1);	// Отображение стрелки вниз после редактируемой величины
			}
			else
			{
				Editing_ = 0;
				WH1602_Print2 (" ", 1, 10, 1, (void (*)())osDelay, 1);	// Стирание стрелок до и после редактируемых величин
				WH1602_Print2 (" ", 1, 15, 1, (void (*)())osDelay, 1);
			}
		}
		OldButtonOkState = ButtonOk;

		if(Editing_ == 1)
		{
			if(ClientModeMenuString == 1)								// Кнопка активации
			{
				NumericParamEdit(FirstParametr, 5, 16);
			}
			else if(ClientModeMenuString == 2)					// Номер выхода 1
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 9);
			}
			else if(ClientModeMenuString == 3)					// Режим 0 - реле / 1 - дозирование
			{
				EnableDisableParamEdit(FirstParametr+ClientModeMenuString-1);
			}
			else if(ClientModeMenuString == 4)					// Процент дозирования
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 100);
			}
			else if(ClientModeMenuString == 5)					// Номер выхода 2
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 9);
			}
			else if(ClientModeMenuString == 6)					// Режим 0 - реле / 1 - дозирование
			{
				EnableDisableParamEdit(FirstParametr+ClientModeMenuString-1);
			}
			else if(ClientModeMenuString == 7)					// Процент дозирования
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 100);
			}
			else if(ClientModeMenuString == 8)					// Номер выхода 3
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 9);
			}
			else if(ClientModeMenuString == 9)					// Режим 0 - реле / 1 - дозирование
			{
				EnableDisableParamEdit(FirstParametr+ClientModeMenuString-1);
			}
			else if(ClientModeMenuString == 10)					// Процент дозирования
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 100);
			}
			else if(ClientModeMenuString == 11)					// Номер выхода 4
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 9);
			}
			else if(ClientModeMenuString == 12)					// Режим 0 - реле / 1 - дозирование
			{
				EnableDisableParamEdit(FirstParametr+ClientModeMenuString-1);
			}
			else if(ClientModeMenuString == 13)					// Процент дозирования
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 100);
			}
			else if(ClientModeMenuString == 14)					// Цена секунды
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 9999);
			}
		}
		
	if(ButtonOk == ButtonSet)
	{
		if(ClientModeMenuString == LastClientModeMenuStreeng)	// Выход из этого меню
		{	
			SaveSettingsToFlash(SettingsFlashAddress, &Settings.ImpulsePricePI3, (sizeof(Settings) / 4));
			ClientModeMenuString = 0;
			OldClientModeMenuString = 1;
			MenuLst = SetingsMenu;
			SetingsMenuString = 0;
			OldSetingsMenuString = SetingsMenuString +1;
			ButtonOk = ButtonReset;
			ButtonOkCounter = 0;
		}
	}
}
/**************************************************************************************************************************************************/
/******************************************************* Меню *************************************************************************************/
#define SettingsMenuStringsQuantity 14 // Количество сторк в меню настроек
void Menu(void)
{
	//------------------------- Изменение номера строки меню "Настройки" -------------------------------
	static uint32_t LogoCounter = 0; // Счетчик для отображения логотипа и времени
		if(MenuLst == SetingsMenu)
		{
			if(LogoCounter < 120000) LogoCounter++;
			static ButtonStateTypeDef OldButtonUpState;
			if((OldButtonUpState == ButtonReset)&&(ButtonUp == ButtonSet))
			{
				LogoCounter = 0;
				SetingsMenuString = (SetingsMenuString > 0) ? --SetingsMenuString : 0 ;
			}
			OldButtonUpState = ButtonUp;
			
			static ButtonStateTypeDef OldButtonDownState;
			if((OldButtonDownState == ButtonReset)&&(ButtonDown == ButtonSet))
			{
				LogoCounter = 0;
				SetingsMenuString = (SetingsMenuString < SettingsMenuStringsQuantity) ? ++SetingsMenuString : SettingsMenuStringsQuantity ;
			}
			OldButtonDownState = ButtonDown;
			
			if(OldSetingsMenuString != SetingsMenuString)
			{
				WH1602_Print ((char*)&SetsMenyStrings+(16*SetingsMenuString), 1, (void (*)())osDelay, 1);
				WH1602_Print ((char*)&SetsMenyStrings+(16*SetingsMenuString)+16, 2, (void (*)())osDelay, 1);
				if(SetingsMenuString == 0)
				{
					WH1602_SetDDRAM_Address (0x10);
				}
				else
				{
					WH1602_SetDDRAM_Address (0x0F);
				}
				OldSetingsMenuString = SetingsMenuString;
			}
			if(ButtonOk == ButtonSet)
			{
				LogoCounter = 0;
				if(SetingsMenuString == 1) MenuLst = PI1Menu;
				if(SetingsMenuString == 2) MenuLst = PI2Menu;
				if(SetingsMenuString == 3) MenuLst = PI3Menu;
				if(SetingsMenuString == 4) MenuLst = WaterMenu;
				if(SetingsMenuString == 5) MenuLst = FoamMenu;
				if(SetingsMenuString == 6) MenuLst = WaxMenu;
				if(SetingsMenuString == 7) MenuLst = OsmosMenu;
				if(SetingsMenuString == 8) MenuLst = VacuumCleanerMenu;
				if(SetingsMenuString == 9) MenuLst = AirMenu;
				if(SetingsMenuString == 10) MenuLst = PauseMenu;
				if(SetingsMenuString == 11) MenuLst = Dop1Menu;
				/*if(SetingsMenuString == 12) MenuLst = Dop2Menu;
				if(SetingsMenuString == 13) MenuLst = Dop3Menu;
				if(SetingsMenuString == 14) MenuLst = Dop4Menu;
				if(SetingsMenuString == 15) MenuLst = Dop5Menu;
				if(SetingsMenuString == 16) MenuLst = Dop6Menu;
				if(SetingsMenuString == 17) MenuLst = CardsMenu;
				if(SetingsMenuString == 18) MenuLst = VendotekMenu;*/
				if(SetingsMenuString == 12) MenuLst = CardsMenu;
				if(SetingsMenuString == 13) MenuLst = VendotekMenu;
				if(SetingsMenuString == 14) 
				{
					MenuLst = RTCMenu;
					TempRTCData.Date = CurrentDateAndTime.mday;
					TempRTCData.Month = CurrentDateAndTime.mon;
					TempRTCData.Year = CurrentDateAndTime.year;
					TempRTCData.Hours = CurrentDateAndTime.hour;
					TempRTCData.Minytes = CurrentDateAndTime.min;
					TempRTCData.Seconds = CurrentDateAndTime.sec;
				}
			}
			if(LogoCounter > 7000)
			{
				static uint8_t SecondsOld = 0;
				if(SecondsOld != CurrentDateAndTime.sec)
				{
					WH1602_Print ("ChTechnology LLC", 1, (void (*)())osDelay, 1);
					char RTC_String[17];
					sprintf(RTC_String,"%02u:%02u %02u.%02u.%02u", CurrentDateAndTime.hour, CurrentDateAndTime.min, CurrentDateAndTime.mday,\
																																											CurrentDateAndTime.mon, CurrentDateAndTime.year);
					WH1602_Print (RTC_String, 2, (void (*)())osDelay, 1);
				}
				SecondsOld = CurrentDateAndTime.sec;
				
			}
		}
//---------------------------------------- Меню Импульсный вход 3 ----------------------------------------
		if(MenuLst == PI3Menu)
		{
			PiMenuImplementation(&Settings.ImpulsePricePI3);
		}		
//---------------------------------------- Меню Импульсный вход 2 ----------------------------------------
		if(MenuLst == PI2Menu)
		{
			PiMenuImplementation(&Settings.ImpulsePricePI2);
		}
//---------------------------------------- Меню Импульсный вход 1 ----------------------------------------
		if(MenuLst == PI1Menu)
		{
			PiMenuImplementation(&Settings.ImpulsePricePI1);
		}
//---------------------------------------- Меню Вода -----------------------------------------------------
		if(MenuLst == WaterMenu)
		{
			ClientModeMenuImplementation("      Вода      ",&Settings.WaterButtonNumber);
		}
//---------------------------------------- Меню Пена -----------------------------------------------------
		if(MenuLst == FoamMenu)
		{
			ClientModeMenuImplementation("      Пена      ",&Settings.FoamButtonNumber);
		}
//---------------------------------------- Меню Воск -----------------------------------------------------
		if(MenuLst == WaxMenu)
		{
			ClientModeMenuImplementation("      Воск      ",&Settings.WaxButtonNumber);
		}
//---------------------------------------- Меню Осмос -----------------------------------------------------
		if(MenuLst == OsmosMenu)
		{
			ClientModeMenuImplementation("      Осмос     ",&Settings.OsmosButtonNumber);
		}		
//---------------------------------------- Меню Пылесос ---------------------------------------------------
		if(MenuLst == VacuumCleanerMenu)
		{
			ClientModeMenuImplementation("     Пылесос    ",&Settings.VacuumClinerButtonNumber);
		}		
//---------------------------------------- Меню Воздух ----------------------------------------------------
		if(MenuLst == AirMenu)
		{
			ClientModeMenuImplementation("     Воздух     ",&Settings.AirButtonNumber);
		}
//---------------------------------------- Меню Пауза ----------------------------------------------------
		if(MenuLst == PauseMenu)
		{
			PauseMenuImplementation("     Пауза      ",&Settings.PauseFreeMinutes, (char*) &PauseMenuStrings);
		}
//-------------------------------------- Меню Доп реж 1 ---------------------------------------------------
		if(MenuLst == Dop1Menu)
		{
			ClientModeMenuImplementation("    Доп реж 1   ",&Settings.Dop1ButtonNumber);
		}
//-------------------------------------- Меню Доп реж 2 ---------------------------------------------------
		if(MenuLst == Dop2Menu)
		{
			ClientModeMenuImplementation("    Доп реж 2   ",&Settings.Dop2ButtonNumber);
		}
//-------------------------------------- Меню Доп реж 3 ---------------------------------------------------
		if(MenuLst == Dop3Menu)
		{
			ClientModeMenuImplementation("    Доп реж 3   ",&Settings.Dop3ButtonNumber);
		}
//-------------------------------------- Меню Доп реж 4 ---------------------------------------------------
		if(MenuLst == Dop4Menu)
		{
			ClientModeMenuImplementation("    Доп реж 4   ",&Settings.Dop4ButtonNumber);
		}		
//-------------------------------------- Меню Доп реж 5 ---------------------------------------------------
		if(MenuLst == Dop5Menu)
		{
			ClientModeMenuImplementation("    Доп реж 5   ",&Settings.Dop5ButtonNumber);
		}		
//-------------------------------------- Меню Доп реж 6 ---------------------------------------------------
		if(MenuLst == Dop6Menu)
		{
			ClientModeMenuImplementation("    Доп реж 6   ",&Settings.Dop6ButtonNumber);
		}
//-------------------------------------- Меню Карты ---------------------------------------------------
		if(MenuLst == CardsMenu)
		{
			CardsMenuImplementation("  Карта клиента ",&Settings.CardKey1, (char*) &CardsMenuStrings);
		}
		//-------------------------------------- Меню Vendotek ---------------------------------------------------
		if(MenuLst == VendotekMenu)
		{
			VendotekMenuImplementation("    Vendotek    ",&Settings.VendotekStep, (char*) &VendotekMenuStrings);
		}
		//-------------------------------------- Меню Время ---------------------------------------------------
		if(MenuLst == RTCMenu)
		{
			RTCMenuImplementation("     Время      ",&TempRTCData.Date , (char*) &RTCMenuStrings, 7);
		}
}
/**************************************************************************************************************************************************/

/**************************************************************************************************************************************************/
// Чтение из FLASH-памяти 4 байт
uint32_t FLASH_Read(uint32_t Address)
{
	return (*(__IO uint32_t*)Address);
}
/**************************************************************************************************************************************************/

/************************************************* Сохранение уставок во Flash память *************************************************************/
//uint32_t FlashAddr - Адрес во Flash памяти контроллера, куда сохраняются уставки 0x0807F800
//uint32_t* SramSettingsAddr - Указатель на первый параметр уставок в контроллере (Settings)
//uint32_t SettingsSize - количество 32-х разрядных элементов из которых состоят уставки
#pragma push
#pragma O0
void SaveSettingsToFlash(uint32_t FlashAddr, uint32_t* SramSettingsAddr, uint32_t SettingsSize)
{
	HAL_FLASH_Unlock();
	// FLASH_Erase Page
	while( FLASH->SR&FLASH_SR_BSY ) {}
	FLASH->CR |= FLASH_CR_PER; //Page Erase Set
	FLASH->AR = FlashAddr;//0x0807F800; //Page Address
	FLASH->CR |= FLASH_CR_STRT; //Start Page Erase
	while( FLASH->SR&FLASH_SR_BSY ) {}
	FLASH->CR &= ~FLASH_CR_PER; //Page Erase Clear
	FLASH->CR |= FLASH_CR_PG; // FLASH_Program HalfWord
	while( FLASH->SR&FLASH_SR_BSY ) {}
	//************************************

	for(uint32_t i = 0; i < SettingsSize; i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (FlashAddr + (i*4)), *(&Settings.ImpulsePricePI3+i));
	}
	HAL_FLASH_Lock();
}
#pragma pop
/**************************************************************************************************************************************************/
/******************************** Берет данные не из кольцевого буфера и сохраняет их в виде тега в кольцевой буфер *******************************/
//uint8_t TagNum - номер тега
//uint16_t DataLen - количество байт данных, которые нужно уложить в буфер
//uint8_t* DataPointer - указатель на источник данных
//uint8_t* BufForSave - Указатель на буфер, куда сохраняется готовый тег
//uint32_t BufForSave1p - индекс буфера для сохранения
//uint32_t BufForSaveSize - Указатель размера буфера для сохранения
//#pragma push
//#pragma O0
void AddTag(uint8_t TagNum, uint16_t DataLen, uint8_t* DataPointer, uint8_t* BufForSave, uint32_t* BufForSave1p, uint32_t BufForSaveSize)
{
	/*------------------- Формирование заголовкапакета --------------------------------------------------*/
	uint32_t StartPacketIndex = *BufForSave1p; 		// Индекс начиная с которого ложится пакет в буфер
	BufForSave[*BufForSave1p] = 0xDE;				 		// Идентификатор начала пакет "222"
	*BufForSave1p += 1;
	*BufForSave1p %= BufForSaveSize;
	BufForSave[*BufForSave1p] = TagNum;			 		// Номер тега
	*BufForSave1p += 1;
	*BufForSave1p %= BufForSaveSize;
	BufForSave[*BufForSave1p] = DataLen >> 8;		//Длина данных старший байт
	*BufForSave1p += 1;
	*BufForSave1p %= BufForSaveSize;
	BufForSave[*BufForSave1p] = DataLen;				//Длина данных младший байт
	*BufForSave1p += 1;
	*BufForSave1p %= BufForSaveSize;
	BufForSave[*BufForSave1p] = 0;								// CRC8
	while(StartPacketIndex != *BufForSave1p)
	{
		CRC8n(BufForSave[StartPacketIndex], &BufForSave[*BufForSave1p]);
		StartPacketIndex++;
		StartPacketIndex %= BufForSaveSize;
	}
	*BufForSave1p += 1;
	*BufForSave1p %= BufForSaveSize;
	/*---------------------------------------------------------------------------------------------*/
	/*----------------------------- Наполнение поля данных ----------------------------------------*/
	uint32_t StartDataIndex = *BufForSave1p; 		//Индекс начиная с которого в буфер ложатся данные
	for(uint16_t i = 0; i < DataLen; i++)
	{
		BufForSave[*BufForSave1p] = DataPointer[i];
		*BufForSave1p += 1;
		*BufForSave1p %= BufForSaveSize;
	}
	uint16_t CRC16;															// CRC16 Блока данных
	Crc16Buf (BufForSave, StartDataIndex, BufForSaveSize, DataLen, 0x1021, &CRC16);
	BufForSave[*BufForSave1p] = (uint8_t) (CRC16 >> 8);
	*BufForSave1p += 1;
	*BufForSave1p %= BufForSaveSize;
	BufForSave[*BufForSave1p] = (uint8_t) CRC16;
	*BufForSave1p += 1;
	*BufForSave1p %= BufForSaveSize;
}
//#pragma pop
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
//uint32_t* Parametr - редактируемый параметр
//uint32_t ParametrLowBorder - минимальное значение
//uint32_t ParametrHighBorder - максимальное значение
void NumericParamEdit(uint32_t* Parametr, uint32_t ParametrLowBorder, uint32_t ParametrHighBorder)
{
	static uint32_t ButtonUpCounterEditing;
	uint8_t MyTmpStr[11];
	if(ButtonUp == ButtonSet)
	{
		ButtonUpCounterEditing = (ButtonUpCounterEditing < 100) ? ++ButtonUpCounterEditing : 0;
		if(ButtonUpCounterEditing == 0) 
		{
			*Parametr = (*Parametr >= ParametrHighBorder) ? ParametrHighBorder : *Parametr + 1;
			Hex32ToDecASCII (*Parametr, MyTmpStr);
			WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
		}
	}
	else
	{
		ButtonUpCounterEditing = 0;
	}
	static uint32_t ButtonDownCounterEditing;

	if(ButtonDown == ButtonSet)
	{
		ButtonDownCounterEditing = (ButtonDownCounterEditing < 100) ? ++ButtonDownCounterEditing : 0;
		if(ButtonDownCounterEditing == 0) 
		{
			*Parametr = (*Parametr <= ParametrLowBorder) ? ParametrLowBorder : *Parametr - 1;
			Hex32ToDecASCII (*Parametr, MyTmpStr);
			WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
		}
	}
	else
	{
		ButtonDownCounterEditing = 0;
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
void EnableDisableParamEdit(uint32_t* Parametr)
{
	static uint32_t ButtonUpCounterEditing;
//	uint8_t MyTmpStr[11];
	if(ButtonUp == ButtonSet)
	{
		ButtonUpCounterEditing = (ButtonUpCounterEditing < 100) ? ++ButtonUpCounterEditing : 0;
		if(ButtonUpCounterEditing == 0) 
		{
			*Parametr = (*Parametr >= 2) ? 2 : *Parametr + 1;
			if(*Parametr == 0) WH1602_Print2 ("Откл", 1, 11, 4, (void (*)())osDelay, 1);
			else if(*Parametr == 1) WH1602_Print2 ("Реле", 1, 11, 4, (void (*)())osDelay, 1);
			else if(*Parametr == 2) WH1602_Print2 ("Доз ", 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
		}
	}
	else
	{
		ButtonUpCounterEditing = 0;
	}
	static uint32_t ButtonDownCounterEditing;

	if(ButtonDown == ButtonSet)
	{
		ButtonDownCounterEditing = (ButtonDownCounterEditing < 100) ? ++ButtonDownCounterEditing : 0;
		if(ButtonDownCounterEditing == 0) 
		{
			*Parametr = (*Parametr <= 0) ? 0 : *Parametr - 1;
			if(*Parametr == 0) WH1602_Print2 ("Откл", 1, 11, 4, (void (*)())osDelay, 1);
			else if(*Parametr == 1) WH1602_Print2 ("Реле", 1, 11, 4, (void (*)())osDelay, 1);
			else if(*Parametr == 2) WH1602_Print2 ("Доз ", 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
		}
	}
	else
	{
		ButtonDownCounterEditing = 0;
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
void OffOnParamEdit(uint32_t* Parametr)
{
	static uint32_t ButtonUpCounterEditing;
//	uint8_t MyTmpStr[11];
	if(ButtonUp == ButtonSet)
	{
		ButtonUpCounterEditing = (ButtonUpCounterEditing < 100) ? ++ButtonUpCounterEditing : 0;
		if(ButtonUpCounterEditing == 0) 
		{
			*Parametr = (*Parametr >= 1) ? 1 : *Parametr + 1;
			if(*Parametr == 0) WH1602_Print2 ("Откл", 1, 11, 4, (void (*)())osDelay, 1);
			else if(*Parametr == 1) WH1602_Print2 ("Вкл", 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
		}
	}
	else
	{
		ButtonUpCounterEditing = 0;
	}
	static uint32_t ButtonDownCounterEditing;

	if(ButtonDown == ButtonSet)
	{
		ButtonDownCounterEditing = (ButtonDownCounterEditing < 100) ? ++ButtonDownCounterEditing : 0;
		if(ButtonDownCounterEditing == 0) 
		{
			*Parametr = (*Parametr <= 0) ? 0 : *Parametr - 1;
			if(*Parametr == 0) WH1602_Print2 ("Откл", 1, 11, 4, (void (*)())osDelay, 1);
			else if(*Parametr == 1) WH1602_Print2 ("Вкл", 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
		}
	}
	else
	{
		ButtonDownCounterEditing = 0;
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
//uint32_t OutputNumber - номер выхода
//uint32_t OutputState - 1 - включение выхода 0 - отключение
//uint32_t OutputMode  - 0 - выход отключен, 1 - выход в режиме реле, 2 - выход в режиме дозирования
#pragma push
#pragma O0
void OnOffOutput(uint32_t OutputNumber, uint32_t OutputState, uint32_t OutputMode, uint32_t OutPercent)
{
//	switch (OutputNumber){
//		case 1: if((OutputState == 1)&&(OutputMode != 0)) 
//							RO.Rele1State = 1; 
//						else if((OutputState == 0)&&(OutputMode != 0))
//							RO.Rele1State = 0; 
//						if(OutputMode == 3) 
//							RO.Rele1Mode = 1; 
//						else 
//							RO.Rele1Mode = 0; 
//						break;
//		case 2: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele2State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele2State = 0; if(OutputMode == 3) RO.Rele2Mode = 1; else RO.Rele2Mode = 0; break;
//		case 3: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele3State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele3State = 0; if(OutputMode == 3) RO.Rele3Mode = 1; else RO.Rele3Mode = 0; break;
//		case 4: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele4State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele4State = 0; if(OutputMode == 3) RO.Rele4Mode = 1; else RO.Rele4Mode = 0; break;
//		case 5: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele5State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele5State = 0; if(OutputMode == 3) RO.Rele5Mode = 1; else RO.Rele5Mode = 0; break;
//		case 6: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele6State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele6State = 0; if(OutputMode == 3) RO.Rele6Mode = 1; else RO.Rele6Mode = 0; break;
//		case 7: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele7State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele7State = 0; if(OutputMode == 3) RO.Rele7Mode = 1; else RO.Rele7Mode = 0; break;
//		case 8: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele8State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele8State = 0; if(OutputMode == 3) RO.Rele8Mode = 1; else RO.Rele8Mode = 0; break;
//		case 9: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele9State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele9State = 0; if(OutputMode == 3) RO.Rele9Mode = 1; else RO.Rele9Mode = 0; break;
//		case 10: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele10State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele10State = 0; if(OutputMode == 3) RO.Rele10Mode = 1; else RO.Rele10Mode = 0; break;
//		case 11: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele11State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele11State = 0; if(OutputMode == 3) RO.Rele11Mode = 1; else RO.Rele11Mode = 0; break;
//		case 12: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele12State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele12State = 0; if(OutputMode == 3) RO.Rele12Mode = 1; else RO.Rele12Mode = 0; break;
//		case 13: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele13State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele13State = 0; if(OutputMode == 3) RO.Rele13Mode = 1; else RO.Rele13Mode = 0; break;
//		case 14: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele14State = 1; else if((OutputState == 0)&&(OutputMode != 0))RO.Rele14State = 0; if(OutputMode == 3) RO.Rele14Mode = 1; else RO.Rele14Mode = 0; break;
//		case 15: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele15State = 1; else if((OutputState == 0)&&(OutputMode != 0)) RO.Rele15State = 0; if(OutputMode == 3) RO.Rele15Mode = 1; else RO.Rele15Mode = 0; break;
//		//case 16: if((OutputState == 1)&&(OutputMode != 0)) RO.Rele16State = 1; else RO.Rele16State = 0; if(OutputMode == 3) RO.Rele16Mode = 1; else RO.Rele16Mode = 0; break;
//	}

	switch (OutputNumber){
		case 1: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele1State = 1; else if(OutputState == 0)RO.Rele1State = 0; 
						if(OutputMode == 2) RO.Rele1Mode = 1; else RO.Rele1Mode = 0; 
						OutputPercent.Out1Percent = OutPercent; break;
		case 2: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele2State = 1; else if(OutputState == 0)RO.Rele2State = 0;
						if(OutputMode == 2) RO.Rele2Mode = 1; else RO.Rele2Mode = 0;
						OutputPercent.Out2Percent = OutPercent; break;
		case 3: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele3State = 1; else if(OutputState == 0)RO.Rele3State = 0;
						if(OutputMode == 2) RO.Rele3Mode = 1; else RO.Rele3Mode = 0; 
						OutputPercent.Out3Percent = OutPercent; break;
		case 4: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele4State = 1; else if(OutputState == 0)RO.Rele4State = 0;
						if(OutputMode == 2) RO.Rele4Mode = 1; else RO.Rele4Mode = 0; 
						OutputPercent.Out4Percent = OutPercent; break;
		case 5: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele5State = 1; else if(OutputState == 0)RO.Rele5State = 0;
						if(OutputMode == 2) RO.Rele5Mode = 1; else RO.Rele5Mode = 0;
						OutputPercent.Out5Percent = OutPercent; break;
		case 6: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele6State = 1; else if(OutputState == 0)RO.Rele6State = 0;
						if(OutputMode == 2) RO.Rele6Mode = 1; else RO.Rele6Mode = 0;
						OutputPercent.Out6Percent = OutPercent; break;
		case 7: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele7State = 1; else if(OutputState == 0)RO.Rele7State = 0;
						if(OutputMode == 2) RO.Rele7Mode = 1; else RO.Rele7Mode = 0;
						OutputPercent.Out7Percent = OutPercent; break;
		case 8: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele8State = 1; else if(OutputState == 0)RO.Rele8State = 0;
						if(OutputMode == 2) RO.Rele8Mode = 1; else RO.Rele8Mode = 0;
						OutputPercent.Out8Percent = OutPercent; break;
		case 9: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele9State = 1; else if(OutputState == 0)RO.Rele9State = 0;
						if(OutputMode == 2) RO.Rele9Mode = 1; else RO.Rele9Mode = 0; 
						OutputPercent.Out9Percent = OutPercent; break;
		case 10: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele10State = 1; else if(OutputState == 0)RO.Rele10State = 0;
						 if(OutputMode == 2) RO.Rele10Mode = 1; else RO.Rele10Mode = 0; 
						 OutputPercent.Out10Percent = OutPercent; break;
		case 11: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele11State = 1; else if(OutputState == 0)RO.Rele11State = 0;
						 if(OutputMode == 2) RO.Rele11Mode = 1; else RO.Rele11Mode = 0; 
						 OutputPercent.Out11Percent = OutPercent; break;
		case 12: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele12State = 1; else if(OutputState == 0)RO.Rele12State = 0;
						 if(OutputMode == 2) RO.Rele12Mode = 1; else RO.Rele12Mode = 0; 
						 OutputPercent.Out12Percent = OutPercent; break;
		case 13: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele13State = 1; else if(OutputState == 0)RO.Rele13State = 0;
						 if(OutputMode == 2) RO.Rele13Mode = 1; else RO.Rele13Mode = 0; 
						 OutputPercent.Out13Percent = OutPercent; break;
		case 14: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele14State = 1; else if(OutputState == 0)RO.Rele14State = 0;
						 if(OutputMode == 2) RO.Rele14Mode = 1; else RO.Rele14Mode = 0; 
						 OutputPercent.Out14Percent = OutPercent; break;
		case 15: if((OutputState == 1)&&(OutputMode !=0)) RO.Rele15State = 1; else if(OutputState == 0)RO.Rele15State = 0;
						 if(OutputMode == 2) RO.Rele15Mode = 1; else RO.Rele15Mode = 0; 
						 OutputPercent.Out15Percent = OutPercent; break;
	}
}
#pragma pop
/**************************************************************************************************************************************************/

void OffOutput(uint32_t OutputNumber)
{
	switch (OutputNumber){
		case 1: RO.Rele1State = 0; break;
		case 2: RO.Rele2State = 0; break;
		case 3: RO.Rele3State = 0; break;
		case 4: RO.Rele4State = 0; break;
		case 5: RO.Rele5State = 0; break;
		case 6: RO.Rele6State = 0; break;
		case 7: RO.Rele7State = 0; break;
		case 8: RO.Rele8State = 0; break;
		case 9: RO.Rele9State = 0; break;
		case 10: RO.Rele10State = 0; break;
		case 11: RO.Rele11State = 0; break;
		case 12: RO.Rele12State = 0; break;
		case 13: RO.Rele13State = 0; break;
		case 14: RO.Rele14State = 0; break;
		case 15: RO.Rele15State = 0; break;
	}
}

/**************************************************************************************************************************************************/
WorkModeTypeDef ReleSwitch(uint32_t Button)
{
		if(Settings.WaterButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.WaterOut1 != i)&&(Settings.WaterOut2 != i)&&(Settings.WaterOut3 != i)&&(Settings.WaterOut4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.WaterOut1, 1, Settings.WaterMode1, Settings.WaterPercent1);
			OnOffOutput(Settings.WaterOut2, 1, Settings.WaterMode2, Settings.WaterPercent2);
			OnOffOutput(Settings.WaterOut3, 1, Settings.WaterMode3, Settings.WaterPercent3);
			OnOffOutput(Settings.WaterOut4, 1, Settings.WaterMode4, Settings.WaterPercent4);
			return Water;
		}
		else if(Settings.FoamButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)
			{
				if((Settings.FoamOut1 != i)&&(Settings.FoamOut2 != i)&&(Settings.FoamOut3 != i)&&(Settings.FoamOut4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.FoamOut1, 1, Settings.FoamMode1, Settings.FoamPercent1);
			OnOffOutput(Settings.FoamOut2, 1, Settings.FoamMode2, Settings.FoamPercent2);
			OnOffOutput(Settings.FoamOut3, 1, Settings.FoamMode3, Settings.FoamPercent3);
			OnOffOutput(Settings.FoamOut4, 1, Settings.FoamMode4, Settings.FoamPercent4);
			return Foam;
		}
		else if(Settings.WaxButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.WaxOut1 != i)&&(Settings.WaxOut2 != i)&&(Settings.WaxOut3 != i)&&(Settings.WaxOut4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.WaxOut1, 1, Settings.WaxMode1, Settings.WaxPercent1);
			OnOffOutput(Settings.WaxOut2, 1, Settings.WaxMode2, Settings.WaxPercent2);
			OnOffOutput(Settings.WaxOut3, 1, Settings.WaxMode3, Settings.WaxPercent3);
			OnOffOutput(Settings.WaxOut4, 1, Settings.WaxMode4, Settings.WaxPercent4);
			return Wax;
		}
		else if(Settings.OsmosButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.OsmosOut1 != i)&&(Settings.OsmosOut2 != i)&&(Settings.OsmosOut3 != i)&&(Settings.OsmosOut4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.OsmosOut1, 1, Settings.OsmosMode1, Settings.OsmosPercent1);
			OnOffOutput(Settings.OsmosOut2, 1, Settings.OsmosMode2, Settings.OsmosPercent2);
			OnOffOutput(Settings.OsmosOut3, 1, Settings.OsmosMode3, Settings.OsmosPercent3);
			OnOffOutput(Settings.OsmosOut4, 1, Settings.OsmosMode4, Settings.OsmosPercent4);
			return Osmos;
		}
		else if(Settings.VacuumClinerButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.VacuumClinerOut1 != i)&&(Settings.VacuumClinerOut2 != i)&&(Settings.VacuumClinerOut3 != i)&&(Settings.VacuumClinerOut4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.VacuumClinerOut1, 1, Settings.VacuumClinerMode1, Settings.VacuumClinerPercent1);
			OnOffOutput(Settings.VacuumClinerOut2, 1, Settings.VacuumClinerMode2, Settings.VacuumClinerPercent2);
			OnOffOutput(Settings.VacuumClinerOut3, 1, Settings.VacuumClinerMode3, Settings.VacuumClinerPercent3);
			OnOffOutput(Settings.VacuumClinerOut4, 1, Settings.VacuumClinerMode4, Settings.VacuumClinerPercent4);
			return VacuumCliner;
		}
		else if(Settings.AirButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.AirOut1 != i)&&(Settings.AirOut2 != i)&&(Settings.AirOut3 != i)&&(Settings.AirOut4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.AirOut1, 1, Settings.AirMode1, Settings.AirPercent1);
			OnOffOutput(Settings.AirOut2, 1, Settings.AirMode2, Settings.AirPercent2);
			OnOffOutput(Settings.AirOut3, 1, Settings.AirMode3, Settings.AirPercent3);
			OnOffOutput(Settings.AirOut4, 1, Settings.AirMode4, Settings.AirPercent4);
			return Air;
		}
		else if(Settings.Dop1ButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.Dop1Out1 != i)&&(Settings.Dop1Out2 != i)&&(Settings.Dop1Out3 != i)&&(Settings.Dop1Out4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.Dop1Out1, 1, Settings.Dop1Mode1, Settings.Dop1Percent1);
			OnOffOutput(Settings.Dop1Out2, 1, Settings.Dop1Mode2, Settings.Dop1Percent2);
			OnOffOutput(Settings.Dop1Out3, 1, Settings.Dop1Mode3, Settings.Dop1Percent3);
			OnOffOutput(Settings.Dop1Out4, 1, Settings.Dop1Mode4, Settings.Dop1Percent4);
			return Dop1Mode;
		}
		else if(Settings.Dop2ButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.Dop2Out1 != i)&&(Settings.Dop2Out2 != i)&&(Settings.Dop2Out3 != i)&&(Settings.Dop2Out4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.Dop2Out1, 1, Settings.Dop2Mode1, Settings.Dop2Percent1);
			OnOffOutput(Settings.Dop2Out2, 1, Settings.Dop2Mode2, Settings.Dop2Percent2);
			OnOffOutput(Settings.Dop2Out3, 1, Settings.Dop2Mode3, Settings.Dop2Percent3);
			OnOffOutput(Settings.Dop2Out4, 1, Settings.Dop2Mode4, Settings.Dop2Percent4);
			return Dop2Mode;
		}
		else if(Settings.Dop3ButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.Dop3Out1 != i)&&(Settings.Dop3Out2 != i)&&(Settings.Dop3Out3 != i)&&(Settings.Dop3Out4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.Dop3Out1, 1, Settings.Dop3Mode1, Settings.Dop3Percent1);
			OnOffOutput(Settings.Dop3Out2, 1, Settings.Dop3Mode2, Settings.Dop3Percent2);
			OnOffOutput(Settings.Dop3Out3, 1, Settings.Dop3Mode3, Settings.Dop3Percent3);
			OnOffOutput(Settings.Dop3Out4, 1, Settings.Dop3Mode4, Settings.Dop3Percent4);
			return Dop3Mode;
		}
		else if(Settings.Dop4ButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.Dop4Out1 != i)&&(Settings.Dop4Out2 != i)&&(Settings.Dop4Out3 != i)&&(Settings.Dop4Out4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.Dop4Out1, 1, Settings.Dop4Mode1, Settings.Dop4Percent1);
			OnOffOutput(Settings.Dop4Out2, 1, Settings.Dop4Mode2, Settings.Dop4Percent2);
			OnOffOutput(Settings.Dop4Out3, 1, Settings.Dop4Mode3, Settings.Dop4Percent3);
			OnOffOutput(Settings.Dop4Out4, 1, Settings.Dop4Mode4, Settings.Dop4Percent4);
			return Dop4Mode;
		}
		else if(Settings.Dop5ButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.Dop5Out1 != i)&&(Settings.Dop5Out2 != i)&&(Settings.Dop5Out3 != i)&&(Settings.Dop5Out4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.Dop5Out1, 1, Settings.Dop5Mode1, Settings.Dop5Percent1);
			OnOffOutput(Settings.Dop5Out2, 1, Settings.Dop5Mode2, Settings.Dop5Percent2);
			OnOffOutput(Settings.Dop5Out3, 1, Settings.Dop5Mode3, Settings.Dop5Percent3);
			OnOffOutput(Settings.Dop5Out4, 1, Settings.Dop5Mode4, Settings.Dop5Percent4);
			return Dop5Mode;
		}
		else if(Settings.Dop6ButtonNumber == Button)
		{
			for(uint32_t i = 1; i <= 15; i++)	// Отключение всех ненужных реле
			{
				if((Settings.Dop6Out1 != i)&&(Settings.Dop6Out2 != i)&&(Settings.Dop6Out3 != i)&&(Settings.Dop6Out4 != i))
				{
					OffOutput(i);
				}
			}
			OnOffOutput(Settings.Dop6Out1, 1, Settings.Dop6Mode1, Settings.Dop6Percent1);
			OnOffOutput(Settings.Dop6Out2, 1, Settings.Dop6Mode2, Settings.Dop6Percent2);
			OnOffOutput(Settings.Dop6Out3, 1, Settings.Dop6Mode3, Settings.Dop6Percent3);
			OnOffOutput(Settings.Dop6Out4, 1, Settings.Dop6Mode4, Settings.Dop6Percent4);
			return Dop6Mode;
		}
		return ReadyToWash;//CashPaymentRecieveMode;
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
#pragma push
#pragma O0
void ClientButtonsControl(WorkModeTypeDef* CurrentMode, uint32_t *KeepaliveTimer_)
{
	//------------------------------------ Получение чека при наличной оплате -------------------------------------------------
	if((*CurrentMode == CashPaymentRecieveMode)||(*CurrentMode == ClientCardIsRead))
	{
		static ButtonStateTypeDef OldBI5 = ButtonReset;
		static ButtonStateTypeDef OldBI6 = ButtonReset;
		static ButtonStateTypeDef OldBI7 = ButtonReset;
		static ButtonStateTypeDef OldBI8 = ButtonReset;
		static ButtonStateTypeDef OldBI9 = ButtonReset;
		static ButtonStateTypeDef OldBI10 = ButtonReset;
		static ButtonStateTypeDef OldBI11 = ButtonReset;
		static ButtonStateTypeDef OldBI12 = ButtonReset;
		static ButtonStateTypeDef OldBI13 = ButtonReset;
		static ButtonStateTypeDef OldBI14 = ButtonReset;
		static ButtonStateTypeDef OldBI15 = ButtonReset;
		static ButtonStateTypeDef OldBI16 = ButtonReset;
		if((BI5 == ButtonSet)&&(OldBI5 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI6 == ButtonSet)&&(OldBI6 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI7 == ButtonSet)&&(OldBI7 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI8 == ButtonSet)&&(OldBI8 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI9 == ButtonSet)&&(OldBI9 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI10 == ButtonSet)&&(OldBI10 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI11 == ButtonSet)&&(OldBI11 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI12 == ButtonSet)&&(OldBI12 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI13 == ButtonSet)&&(OldBI13 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI14 == ButtonSet)&&(OldBI14 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI15 == ButtonSet)&&(OldBI15 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		else if((BI16 == ButtonSet)&&(OldBI16 == ButtonReset))
		{
			GetCheck(1, CashSum, KeepaliveTimer_);
			*CurrentMode = ReadyToWash;	
			Sum = SumFromClientCard + CashSum;
			CashSum = 0;
			SumFromClientCard = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
		}
		OldBI5 = BI5;
		OldBI6 = BI6;
		OldBI7 = BI7;
		OldBI8 = BI8;
		OldBI9 = BI9;
		OldBI10 = BI10;
		OldBI11 = BI11;
		OldBI12 = BI12;
		OldBI13 = BI13;
		OldBI14 = BI14;
		OldBI15 = BI15;
		OldBI16 = BI16;
	}
	//--------------------------------------------------------------------------------------------------------------------------------
	
	// Кнопки выбора режимов
	if(((*CurrentMode == ReadyToWash)||(*CurrentMode == PauseMode)||((*CurrentMode >= Water)&&(*CurrentMode <= Dop6Mode))) /*&& (Sum > 0)*/)
	{																			
		if(BI5 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(5);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
			//OldCashSum = 0;
		}
		else if(BI6 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(6);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI7 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(7);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI8 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(8);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI9 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(9);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI10 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(10);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI11 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(11);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI12 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(12);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI13 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(13);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI14 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(14);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI15 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(15);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
		else if(BI16 == ButtonSet)
		{
			*CurrentMode = ReleSwitch(16);
			GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		}
	}
	//--------------------------------------- Кнопка паузы --------------------------------------- 
	static uint32_t StopWashDelay;
	if((BI4 == ButtonSet)&&(*CurrentMode != PauseMode)&&(*CurrentMode != CashlessPaymentRecieveMode)&&(*CurrentMode != IdlMode)) // Переход в режим паузы из любого другого режима
	{
		RO.Rele1State = 0;
		RO.Rele2State = 0;
		RO.Rele3State = 0;
		RO.Rele4State = 0;
		RO.Rele5State = 0;
		RO.Rele6State = 0;
		RO.Rele7State = 0;
		RO.Rele8State = 0;
		RO.Rele9State = 0;
		RO.Rele10State = 0;
		RO.Rele11State = 0;
		RO.Rele12State = 0;
		RO.Rele13State = 0;
		RO.Rele14State = 0;
		RO.Rele15State = 0;
		//GPIOE->ODR &= 0x0000; // Очистка подсветки всех кнопок
		GPIOE->ODR &= 0xE01F;																				// Очистка подсветки всех кнопок кроме кнопок Vendotek
		*CurrentMode = PauseMode;
		//if(*CurrentMode == PauseMode)
		StopWashDelay = 2000;
	}
	if((BI4 == ButtonSet)&&(*CurrentMode == CashlessPaymentRecieveMode)) // Если клиент выбирал сумму безналичной оплаты, но передумал и нажал паузу, то пережодит в IdlMode
	{
		MoneyForCashlessPaymentRequest = 0;
		GPIOE->ODR &= 0xC01F;																				// Очистка подсветки всех кнопок кроме кнопок Vendotek
		*CurrentMode = IdlMode;
	}
	
	if(StopWashDelay > 0) StopWashDelay--;
	if((BI4 == ButtonSet)&&(StopWashDelay == 0)&&(*CurrentMode == PauseMode))	// Если система уже находится в режиме паузы, то повторное нажатие приведет к остановке мойки
	{
		*CurrentMode = IdlMode;
		GPIOE->ODR &= 0xE01F;																				// Очистка подсветки всех кнопок кроме кнопок Vendotek
		//HAL_GPIO_WritePin(LB9_GPIO_Port, LB9_Pin, GPIO_PIN_RESET);	// Очистка подсветки всех кнопок
		Sum = 0;
	}

	//---------------------------------- Работа с кнопками Vendotek ----------------------------------------------------------------------
	static ButtonStateTypeDef OldBI1 = ButtonReset;
	static ButtonStateTypeDef OldBI2 = ButtonReset;
	static ButtonStateTypeDef OldBI3 = ButtonReset;
	if((*CurrentMode == IdlMode)||(*CurrentMode == CashlessPaymentRecieveMode)||(*CurrentMode == ClientCardIsRead))
	{
		// Обработка кнопки 1 (+)
		if((OldBI1 == ButtonReset)&&(BI1 == ButtonSet))	// Увеличение запрашивоемой безналичной оплаты через вендотек
		{
			MoneyForCashlessPaymentRequest = (MoneyForCashlessPaymentRequest < 99900) ? MoneyForCashlessPaymentRequest + Settings.VendotekStep*100 : 99900;	// Деньги, которые клиент хочет оплатить через вендотек в копейках. Выбирается кнопками.
		}
		OldBI1 = BI1;
		// Обработка кнопки 2 (-)
		if((OldBI2 == ButtonReset)&&(BI2 == ButtonSet))	// Уменьшение запрашивоемой безналичной оплаты через вендотек
		{
			MoneyForCashlessPaymentRequest = (MoneyForCashlessPaymentRequest >= Settings.VendotekStep*100) ? MoneyForCashlessPaymentRequest - Settings.VendotekStep*100 : 0;	// Деньги, которые клиент хочет оплатить через вендотек в копейках. Выбирается кнопками.
			if(MoneyForCashlessPaymentRequest == 0)
			{
				*CurrentMode = IdlMode;																					// Отмена безналичной оплаты
				GPIOE->ODR &= 0x001F;																				// Очистка подсветки всех кнопок
			}
		}
		OldBI2 = BI2;
	}
	if((*CurrentMode == CashlessPaymentRecieveMode)||(*CurrentMode == WaitBankCard))
	{	
		// Обработка кнопки 3 (Ок)
		if((OldBI3 == ButtonReset)&&(BI3 == ButtonSet))
		{
			if(MoneyForCashlessPaymentRequest == 0)
			{
				*CurrentMode = IdlMode;																					// Отмена безналичной оплаты
				//HAL_GPIO_WritePin(LB3_GPIO_Port, LB3_Pin, GPIO_PIN_RESET);
				GPIOE->ODR &= 0x001F;																				// Очистка подсветки всех кнопок
			}
			else
			{
				if(VRP_State == NoVRP)
				{
					VRP_State = VRP_Request;																	// Запуск процелуры безналичной оплаты через функцию CashlessPayment(1, 100);
				}
			}

		}
		OldBI3 = BI3;
		
		static CashlessPaymentStateTypeDef CashlessPaymentState = CP_NoPayment;
		static CashlessPaymentStateTypeDef CashlessPaymentStateOld = CP_NoPayment;
		CashlessPaymentState = CashlessPayment(1, MoneyForCashlessPaymentRequest); 						// Процедура безналичной оплаты
		if((CashlessPaymentStateOld == CP_InProcess)&&(CashlessPaymentState == CP_InProcess))	// Ожидание, когда пройдет платеж
		{
			*CurrentMode = WaitBankCard;
			HAL_GPIO_WritePin(LB1_GPIO_Port, LB1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LB2_GPIO_Port, LB2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LB3_GPIO_Port, LB3_Pin, GPIO_PIN_RESET);
		}
		if((CashlessPaymentStateOld == CP_InProcess)&&(CashlessPaymentState == CP_Ok))				// Платеж прошел успешно
		{
//			CashlessSum = MoneyForCashlessPaymentRequest;
//			MoneyForCashlessPaymentRequest = 0;
			//CashlessSum = 0;
			Sum = SumFromClientCard + MoneyForCashlessPaymentRequest;
			SumFromClientCard = 0;
			MoneyForCashlessPaymentRequest = 0;
			FreePauseSeconds = Settings.PauseFreeMinutes*60;
			*CurrentMode = ReadyToWash;
		}	
		if((CashlessPaymentStateOld == CP_InProcess)&&(CashlessPaymentState == CP_Error))			// Платеж не прошел
		{
			MoneyForCashlessPaymentRequest = 0;
			if(SumFromClientCard > 0)
			{
				Sum = SumFromClientCard;
				SumFromClientCard = 0;
				MoneyForCashlessPaymentRequest = 0;
				FreePauseSeconds = Settings.PauseFreeMinutes*60;
				*CurrentMode = ReadyToWash;
			}
			else
			{
				*CurrentMode = IdlMode;
				MoneyForCashlessPaymentRequest = 0;
			}
			
			HAL_GPIO_WritePin(LB3_GPIO_Port, LB3_Pin, GPIO_PIN_RESET);
		}
		CashlessPaymentStateOld = CashlessPaymentState;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------
	
}
#pragma pop
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void ButtonLedControl(WorkModeTypeDef* CurrentMode)
{
	static uint32_t ButtonLedBlinkCounter = 0;
	if((*CurrentMode == CashPaymentRecieveMode)||(*CurrentMode == ClientCardIsRead)||(*CurrentMode == ReadyToWash)) // Моргание кнопками выбора режимов
	{
		ButtonLedBlinkCounter++;
		if(ButtonLedBlinkCounter >= 1000)
		{
			GPIOE->ODR ^= 0x0FE0;//0x0F7F;
			//HAL_GPIO_TogglePin(LB9_GPIO_Port, LB9_Pin);
			ButtonLedBlinkCounter = 0;
		}
	}
	else if(*CurrentMode == Water)
	{
		GPIOE->ODR |= (0x10000>>Settings.WaterButtonNumber);
	}
	else if(*CurrentMode == Foam)
	{
		GPIOE->ODR |= (0x10000>>Settings.FoamButtonNumber);
	}
	else if(*CurrentMode == Wax)
	{
		GPIOE->ODR |= (0x10000>>Settings.WaxButtonNumber);
	}
	else if(*CurrentMode == Osmos)
	{
		GPIOE->ODR |= (0x10000>>Settings.OsmosButtonNumber);
	}
	else if(*CurrentMode == VacuumCliner)
	{
		GPIOE->ODR |= (0x10000>>Settings.VacuumClinerButtonNumber);
	}
	else if(*CurrentMode == Air)
	{
		GPIOE->ODR |= (0x10000>>Settings.AirButtonNumber);
	}
	else if(*CurrentMode == PauseMode)
	{
		GPIOE->ODR |= (0x10000>>4);
	}
	static uint32_t VendotekButtonBlinkTimetCounter = 0;
	if((WashMode == IdlMode)||(WashMode == ClientCardIsRead)) // Мигание кнопками Vendotek в ждущем режиме
	{
		VendotekButtonBlinkTimetCounter ++;
		if(VendotekButtonBlinkTimetCounter >= 1000)
		{
			HAL_GPIO_TogglePin(LB1_GPIO_Port, LB1_Pin);
			HAL_GPIO_TogglePin(LB2_GPIO_Port, LB2_Pin);
			VendotekButtonBlinkTimetCounter = 0;
		}
	}
	if(WashMode == CashlessPaymentRecieveMode) // Мигание кнопками Vendotek в режиме безналичного платежа
	{
		VendotekButtonBlinkTimetCounter ++;
		if(VendotekButtonBlinkTimetCounter >= 1000)
		{
			HAL_GPIO_TogglePin(LB1_GPIO_Port, LB1_Pin);
			HAL_GPIO_TogglePin(LB2_GPIO_Port, LB2_Pin);
			HAL_GPIO_TogglePin(LB3_GPIO_Port, LB3_Pin);
			HAL_GPIO_TogglePin(LB4_GPIO_Port, LB4_Pin);
			VendotekButtonBlinkTimetCounter = 0;
		}
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
#pragma push
#pragma O0
void MoneySubtraction(WorkModeTypeDef* CurrentMode, uint32_t* CurrentSum)
{
	static uint32_t SecondsCounter = 0;
	if(*CurrentMode == Water)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.WaterPriceOfSecond)
			{
				* CurrentSum -= (Settings.WaterPriceOfSecond - (Settings.WaterPriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Foam)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.FoamPriceOfSecond)
			{
				//* CurrentSum -= Settings.FoamPriceOfSecond;
				* CurrentSum -= (Settings.FoamPriceOfSecond - (Settings.FoamPriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Wax)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.WaxPriceOfSecond)
			{
				//* CurrentSum -= Settings.WaxPriceOfSecond;
				* CurrentSum -= (Settings.WaxPriceOfSecond - (Settings.WaxPriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Osmos)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.OsmosPriceOfSecond)
			{
				//* CurrentSum -= Settings.OsmosPriceOfSecond;
				* CurrentSum -= (Settings.OsmosPriceOfSecond - (Settings.OsmosPriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == VacuumCliner)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.VacuumClinerPriceOfSecond)
			{
				//* CurrentSum -= Settings.VacuumClinerPriceOfSecond;
				* CurrentSum -= (Settings.VacuumClinerPriceOfSecond - (Settings.VacuumClinerPriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Air)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.AirPriceOfSecond)
			{
				//* CurrentSum -= Settings.AirPriceOfSecond;
				* CurrentSum -= (Settings.AirPriceOfSecond - (Settings.AirPriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == PauseMode)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(FreePauseSeconds > 0)
			{
				FreePauseSeconds -= 1;
			}
			else
			{
				if(*CurrentSum >= Settings.PausePriceOfSecond)
				{
					//* CurrentSum -= Settings.PausePriceOfSecond;
					* CurrentSum -= (Settings.PausePriceOfSecond - (Settings.PausePriceOfSecond* Settings.CardDiscount / 100));
				}
				else
				{
					*CurrentSum = 0;
				}
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Dop1Mode)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.Dop1PriceOfSecond)
			{
				//* CurrentSum -= Settings.Dop1PriceOfSecond;
				* CurrentSum -= (Settings.Dop1PriceOfSecond - (Settings.Dop1PriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Dop2Mode)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.Dop2PriceOfSecond)
			{
				//* CurrentSum -= Settings.Dop2PriceOfSecond;
				* CurrentSum -= (Settings.Dop2PriceOfSecond - (Settings.Dop2PriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Dop3Mode)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.Dop3PriceOfSecond)
			{
				//* CurrentSum -= Settings.Dop3PriceOfSecond;
				* CurrentSum -= (Settings.Dop3PriceOfSecond - (Settings.Dop3PriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Dop4Mode)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.Dop4PriceOfSecond)
			{
				//* CurrentSum -= Settings.Dop4PriceOfSecond;
				* CurrentSum -= (Settings.Dop4PriceOfSecond - (Settings.Dop4PriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Dop5Mode)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.Dop5PriceOfSecond)
			{
				//* CurrentSum -= Settings.Dop5PriceOfSecond;
				* CurrentSum -= (Settings.Dop5PriceOfSecond - (Settings.Dop5PriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
	else if(*CurrentMode == Dop6Mode)
	{
		SecondsCounter++;
		if(SecondsCounter >= 1000)
		{
			if(*CurrentSum >= Settings.Dop6PriceOfSecond)
			{
				//* CurrentSum -= Settings.Dop6PriceOfSecond;
				* CurrentSum -= (Settings.Dop6PriceOfSecond - (Settings.Dop6PriceOfSecond * Settings.CardDiscount / 100));
			}
			else
			{
				*CurrentSum = 0;
			}
			SecondsCounter = 0;
		}
	}
}
#pragma pop
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
#define LastPauseMenuStreeng 3
void PauseMenuImplementation(char* FirstString, uint32_t* FirstParametr, char* MenuStrings)
{
	static ButtonStateTypeDef OldButtonUpState;
	static uint32_t ClientModeMenuString = 0;
	static uint32_t OldClientModeMenuString = 1;
	static uint8_t Editing_ = 0;
	uint8_t MyTmpStr1[11];
	if((OldButtonUpState == ButtonReset)&&(ButtonUp == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString > 0) ? --ClientModeMenuString : 0 ;
	}
	OldButtonUpState = ButtonUp;
	
	static ButtonStateTypeDef OldButtonDownState;
	if((OldButtonDownState == ButtonReset)&&(ButtonDown == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString < LastPauseMenuStreeng) ? ++ClientModeMenuString : LastPauseMenuStreeng ;
	}
	OldButtonDownState = ButtonDown;
	
	if(OldClientModeMenuString != ClientModeMenuString)
	{
		//----------- Печать первой строки -----------
		if(ClientModeMenuString == 0)
		{
			WH1602_Print (FirstString, 1, (void (*)())osDelay, 1);	// Печать названия заголовка подменю из аргумента функции
		}
		else if(ClientModeMenuString == LastPauseMenuStreeng)
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);
		}
		else
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);

				Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString-1), MyTmpStr1);
				WH1602_Print2 ((char*)MyTmpStr1, 1, 11, 4, (void (*)())osDelay, 1);
		}
		//----------- Печать второй строки -----------
		if(ClientModeMenuString < LastPauseMenuStreeng-1)
		{
			WH1602_Print ((char*)MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
			Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString), MyTmpStr1);
			WH1602_Print2 ((char*)MyTmpStr1, 2, 11, 4, (void (*)())osDelay, 1);
		}
		else
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
		}
		
		if(ClientModeMenuString == 0)
		{
			WH1602_SetDDRAM_Address (0x10);
		}
		else
		{
			WH1602_SetDDRAM_Address (0x0F);
		}
		OldClientModeMenuString = ClientModeMenuString;
	}
	
	
		static ButtonStateTypeDef OldButtonOkState = ButtonReset;
		if((ClientModeMenuString > 0)&&(ClientModeMenuString < LastPauseMenuStreeng)&&(OldButtonOkState == ButtonReset)&&(ButtonOk == ButtonSet))	// Вкл/откл режима редактирования параметра
		{
			//----------------------- Включение режима редактирования параметра ----------------------
			if(Editing_ == 0)
			{
				Editing_ = 1;
				WH1602_Print2 ("\x18", 1, 10, 1, (void (*)())osDelay, 1);	// Отображение стрелки вверх перед редактируемой величиной
				WH1602_Print2 ("\x19", 1, 15, 1, (void (*)())osDelay, 1);	// Отображение стрелки вниз после редактируемой величины
			}
			else
			{
				Editing_ = 0;
				WH1602_Print2 (" ", 1, 10, 1, (void (*)())osDelay, 1);	// Стирание стрелок до и после редактируемых величин
				WH1602_Print2 (" ", 1, 15, 1, (void (*)())osDelay, 1);
			}
		}
		OldButtonOkState = ButtonOk;

		if(Editing_ == 1)
		{
			if(ClientModeMenuString == 1)								// Количество бесплатных минут
			{
				NumericParamEdit(FirstParametr, 0, 100);
			}
			else if(ClientModeMenuString == 2)					// Цена платной секунды
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 9999);
			}
		}
		
	if(ButtonOk == ButtonSet)
	{
		if(ClientModeMenuString == LastPauseMenuStreeng)	// Выход из этого меню
		{	
			SaveSettingsToFlash(SettingsFlashAddress, &Settings.ImpulsePricePI3, (sizeof(Settings) / 4));
			ClientModeMenuString = 0;
			OldClientModeMenuString = 1;
			MenuLst = SetingsMenu;
			SetingsMenuString = 0;
			OldSetingsMenuString = SetingsMenuString +1;
			ButtonOk = ButtonReset;
			ButtonOkCounter = 0;
		}
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
#define LastCardsMenuStreeng 10
// char* MenuStrings - указатель на названия строк меню
void CardsMenuImplementation(char* FirstString, uint32_t* FirstParametr, char* MenuStrings)
{
	static ButtonStateTypeDef OldButtonUpState;
	static uint32_t ClientModeMenuString = 0;
	static uint32_t OldClientModeMenuString = 1;
	static uint8_t Editing_ = 0;
	uint8_t MyTmpStr1[11];
	static uint32_t TmpParameter = 0;
	static uint8_t TmpParameterWasEdited = 0;
	
	//------------- Пролистывание строк меню вверх вниз ------
	if((OldButtonUpState == ButtonReset)&&(ButtonUp == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString > 0) ? --ClientModeMenuString : 0 ;
	}
	OldButtonUpState = ButtonUp;
	
	static ButtonStateTypeDef OldButtonDownState;
	if((OldButtonDownState == ButtonReset)&&(ButtonDown == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString < LastCardsMenuStreeng) ? ++ClientModeMenuString : LastCardsMenuStreeng ;
	}
	OldButtonDownState = ButtonDown;
	//---------------------------------------------------------
	
	
	if(OldClientModeMenuString != ClientModeMenuString)
	{
		//----------- Печать первой строки -----------
		if(ClientModeMenuString == 0)
		{
			WH1602_Print (FirstString, 1, (void (*)())osDelay, 1);	// Печать названия заголовка подменю из аргумента функции
		}
		else if(ClientModeMenuString == LastCardsMenuStreeng)
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);
		}
		else
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);
			if((ClientModeMenuString >6)&&(ClientModeMenuString < 9))
			{
				Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString-1), MyTmpStr1);
				WH1602_Print2 ((char*)MyTmpStr1, 1, 11, 4, (void (*)())osDelay, 1);
			}
			else if(ClientModeMenuString == 9)
			{
				if(Settings.RFID_OnOff == 0)
					WH1602_Print2 ("Откл", 1, 11, 4, (void (*)())osDelay, 1);
				else
					WH1602_Print2 ("Вкл ", 1, 11, 4, (void (*)())osDelay, 1);
			}
			else
			{
				WH1602_Print2 ("    ", 1, 11, 4, (void (*)())osDelay, 1);
			}
				
		}
		//----------- Печать второй строки -----------
		if(ClientModeMenuString < LastCardsMenuStreeng-1)
		{
			WH1602_Print ((char*)MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
			if((ClientModeMenuString >5)&&(ClientModeMenuString < 8))
			{
				Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString), MyTmpStr1);
				WH1602_Print2 ((char*)MyTmpStr1, 2, 11, 4, (void (*)())osDelay, 1);
			}
			else if(ClientModeMenuString == 8)
			{
				if(Settings.RFID_OnOff == 0)
					WH1602_Print2 ("Откл", 2, 11, 4, (void (*)())osDelay, 1);
				else
					WH1602_Print2 ("Вкл ", 2, 11, 4, (void (*)())osDelay, 1);
			}
			else
			{
				WH1602_Print2 ("    ", 2, 11, 4, (void (*)())osDelay, 1);
			}
		}
		else
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
		}
		
		if(ClientModeMenuString == 0)
		{
			WH1602_SetDDRAM_Address (0x10);
		}
		else
		{
			WH1602_SetDDRAM_Address (0x0F);
		}
		OldClientModeMenuString = ClientModeMenuString;
	}
	
	
		static ButtonStateTypeDef OldButtonOkState = ButtonReset;
		if((ClientModeMenuString > 0)&&(ClientModeMenuString < LastCardsMenuStreeng)&&(OldButtonOkState == ButtonReset)&&(ButtonOk == ButtonSet))	// Вкл/откл режима редактирования параметра
		{
			//----------------------- Включение режима редактирования параметра ----------------------
			if(Editing_ == 0)
			{
				Editing_ = 1;
				WH1602_Print2 ("\x18", 1, 10, 1, (void (*)())osDelay, 1);	// Отображение стрелки вверх перед редактируемой величиной
				WH1602_Print2 ("\x19", 1, 15, 1, (void (*)())osDelay, 1);	// Отображение стрелки вниз после редактируемой величины
				TmpParameter = 0;
				TmpParameterWasEdited = 0;
			}
			else
			{
				Editing_ = 0;
				WH1602_Print2 (" ", 1, 10, 1, (void (*)())osDelay, 1);	// Стирание стрелок до и после редактируемых величин
				WH1602_Print2 (" ", 1, 15, 1, (void (*)())osDelay, 1);
				if((ClientModeMenuString >=1)&&(ClientModeMenuString <= 6)&&(TmpParameterWasEdited == 1))	//Сохранение скрытых параметров (Ключей шифрования)
				{
					*(FirstParametr+ClientModeMenuString-1) = TmpParameter;
				}
			}
		}
		OldButtonOkState = ButtonOk;

		if(Editing_ == 1)
		{
			if(ClientModeMenuString == 1)								// Ключ 1
			{
				HiddenNumericParamEdit(&TmpParameter, 0, 255, &TmpParameterWasEdited);
			}
			else if(ClientModeMenuString == 2)					// Ключ 2
			{
				HiddenNumericParamEdit(&TmpParameter, 0, 255, &TmpParameterWasEdited);
			}
			else if(ClientModeMenuString == 3)					// Ключ 3
			{
				HiddenNumericParamEdit(&TmpParameter, 0, 255, &TmpParameterWasEdited);
			}
			else if(ClientModeMenuString == 4)					// Ключ 4
			{
				HiddenNumericParamEdit(&TmpParameter, 0, 255, &TmpParameterWasEdited);
			}
			else if(ClientModeMenuString == 5)					// Ключ 5
			{
				HiddenNumericParamEdit(&TmpParameter, 0, 255, &TmpParameterWasEdited);
			}
			else if(ClientModeMenuString == 6)					// Ключ 6
			{
				HiddenNumericParamEdit(&TmpParameter, 0, 255, &TmpParameterWasEdited);
			}
			else if(ClientModeMenuString == 7)					// Скидка
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 100);
			}
			else if(ClientModeMenuString == 8)					// Бонус
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 5000);
			}
			else if(ClientModeMenuString == 9)					// RFID Вкл/Откл
			{
				//NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 5000);
				OffOnParamEdit(FirstParametr+ClientModeMenuString-1);
			}
		}
		
	if(ButtonOk == ButtonSet)
	{
		if(ClientModeMenuString == LastCardsMenuStreeng)	// Выход из этого меню
		{	
			SaveSettingsToFlash(SettingsFlashAddress, &Settings.ImpulsePricePI3, (sizeof(Settings) / 4));
			ClientModeMenuString = 0;
			OldClientModeMenuString = 1;
			MenuLst = SetingsMenu;
			SetingsMenuString = 0;
			OldSetingsMenuString = SetingsMenuString +1;
			ButtonOk = ButtonReset;
			ButtonOkCounter = 0;
		}
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
#define LastVendotekMenuStreeng 2
void VendotekMenuImplementation(char* FirstString, uint32_t* FirstParametr, char* MenuStrings)
{
	static ButtonStateTypeDef OldButtonUpState;
	static uint32_t ClientModeMenuString = 0;
	static uint32_t OldClientModeMenuString = 1;
	static uint8_t Editing_ = 0;
	uint8_t MyTmpStr1[11];
	if((OldButtonUpState == ButtonReset)&&(ButtonUp == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString > 0) ? --ClientModeMenuString : 0 ;
	}
	OldButtonUpState = ButtonUp;
	
	static ButtonStateTypeDef OldButtonDownState;
	if((OldButtonDownState == ButtonReset)&&(ButtonDown == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString < LastVendotekMenuStreeng) ? ++ClientModeMenuString : LastVendotekMenuStreeng ;
	}
	OldButtonDownState = ButtonDown;
	
	if(OldClientModeMenuString != ClientModeMenuString)
	{
		//----------- Печать первой строки -----------
		if(ClientModeMenuString == 0)
		{
			WH1602_Print (FirstString, 1, (void (*)())osDelay, 1);	// Печать названия заголовка подменю из аргумента функции
		}
		else if(ClientModeMenuString == LastVendotekMenuStreeng)
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);
		}
		else
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);

				Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString-1), MyTmpStr1);
				WH1602_Print2 ((char*)MyTmpStr1, 1, 11, 4, (void (*)())osDelay, 1);
		}
		//----------- Печать второй строки -----------
		if(ClientModeMenuString < LastVendotekMenuStreeng-1)
		{
			WH1602_Print ((char*)MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
			Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString), MyTmpStr1);
			WH1602_Print2 ((char*)MyTmpStr1, 2, 11, 4, (void (*)())osDelay, 1);
		}
		else
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
		}
		
		if(ClientModeMenuString == 0)
		{
			WH1602_SetDDRAM_Address (0x10);
		}
		else
		{
			WH1602_SetDDRAM_Address (0x0F);
		}
		OldClientModeMenuString = ClientModeMenuString;
	}
	
	
		static ButtonStateTypeDef OldButtonOkState = ButtonReset;
		if((ClientModeMenuString > 0)&&(ClientModeMenuString < LastVendotekMenuStreeng)&&(OldButtonOkState == ButtonReset)&&(ButtonOk == ButtonSet))	// Вкл/откл режима редактирования параметра
		{
			//----------------------- Включение режима редактирования параметра ----------------------
			if(Editing_ == 0)
			{
				Editing_ = 1;
				WH1602_Print2 ("\x18", 1, 10, 1, (void (*)())osDelay, 1);	// Отображение стрелки вверх перед редактируемой величиной
				WH1602_Print2 ("\x19", 1, 15, 1, (void (*)())osDelay, 1);	// Отображение стрелки вниз после редактируемой величины
			}
			else
			{
				Editing_ = 0;
				WH1602_Print2 (" ", 1, 10, 1, (void (*)())osDelay, 1);	// Стирание стрелок до и после редактируемых величин
				WH1602_Print2 (" ", 1, 15, 1, (void (*)())osDelay, 1);
			}
		}
		OldButtonOkState = ButtonOk;

		if(Editing_ == 1)
		{
			if(ClientModeMenuString == 1)								// Количество бесплатных минут
			{
				NumericParamEdit(FirstParametr, 0, 100);
			}
			else if(ClientModeMenuString == 2)					// Цена платной секунды
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 0, 9999);
			}
		}
		
	if(ButtonOk == ButtonSet)
	{
		if(ClientModeMenuString == LastVendotekMenuStreeng)	// Выход из этого меню
		{	
			SaveSettingsToFlash(SettingsFlashAddress, &Settings.ImpulsePricePI3, (sizeof(Settings) / 4));
			ClientModeMenuString = 0;
			OldClientModeMenuString = 1;
			MenuLst = SetingsMenu;
			SetingsMenuString = 0;
			OldSetingsMenuString = SetingsMenuString +1;
			ButtonOk = ButtonReset;
			ButtonOkCounter = 0;
		}
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
//#define LastRTCMenuStreeng 7
void RTCMenuImplementation(char* FirstString, uint32_t* FirstParametr, char* MenuStrings, uint8_t LastMenuStreeng)
{
	static ButtonStateTypeDef OldButtonUpState;
	static uint32_t ClientModeMenuString = 0;
	static uint32_t OldClientModeMenuString = 1;
	static uint8_t Editing_ = 0;
	uint8_t MyTmpStr1[11];
	if((OldButtonUpState == ButtonReset)&&(ButtonUp == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString > 0) ? --ClientModeMenuString : 0 ;
	}
	OldButtonUpState = ButtonUp;
	
	static ButtonStateTypeDef OldButtonDownState;
	if((OldButtonDownState == ButtonReset)&&(ButtonDown == ButtonSet)&&(Editing_ == 0))
	{
		ClientModeMenuString = (ClientModeMenuString < LastMenuStreeng) ? ++ClientModeMenuString : LastMenuStreeng ;
	}
	OldButtonDownState = ButtonDown;
	
	if(OldClientModeMenuString != ClientModeMenuString)
	{
		//----------- Печать первой строки -----------
		if(ClientModeMenuString == 0)
		{
			WH1602_Print (FirstString, 1, (void (*)())osDelay, 1);	// Печать названия заголовка подменю из аргумента функции
		}
		else if(ClientModeMenuString == LastMenuStreeng)
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);
		}
		else
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString), 1, (void (*)())osDelay, 1);

				Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString-1), MyTmpStr1);
				WH1602_Print2 ((char*)MyTmpStr1, 1, 11, 4, (void (*)())osDelay, 1);
		}
		//----------- Печать второй строки -----------
		if(ClientModeMenuString < LastMenuStreeng-1)
		{
			WH1602_Print ((char*)MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
			Hex32ToDecASCII (*(FirstParametr + ClientModeMenuString), MyTmpStr1);
			WH1602_Print2 ((char*)MyTmpStr1, 2, 11, 4, (void (*)())osDelay, 1);
		}
		else
		{
			WH1602_Print (MenuStrings+(16*ClientModeMenuString)+16, 2, (void (*)())osDelay, 1);
		}
		
		if(ClientModeMenuString == 0)
		{
			WH1602_SetDDRAM_Address (0x10);
		}
		else
		{
			WH1602_SetDDRAM_Address (0x0F);
		}
		OldClientModeMenuString = ClientModeMenuString;
	}
	
	
		static ButtonStateTypeDef OldButtonOkState = ButtonReset;
		if((ClientModeMenuString > 0)&&(ClientModeMenuString < LastMenuStreeng)&&(OldButtonOkState == ButtonReset)&&(ButtonOk == ButtonSet))	// Вкл/откл режима редактирования параметра
		{
			//----------------------- Включение режима редактирования параметра ----------------------
			if(Editing_ == 0)
			{
				Editing_ = 1;
				WH1602_Print2 ("\x18", 1, 10, 1, (void (*)())osDelay, 1);	// Отображение стрелки вверх перед редактируемой величиной
				WH1602_Print2 ("\x19", 1, 15, 1, (void (*)())osDelay, 1);	// Отображение стрелки вниз после редактируемой величины
			}
			else
			{
				Editing_ = 0;
				WH1602_Print2 (" ", 1, 10, 1, (void (*)())osDelay, 1);	// Стирание стрелок до и после редактируемых величин
				WH1602_Print2 (" ", 1, 15, 1, (void (*)())osDelay, 1);
			}
		}
		OldButtonOkState = ButtonOk;

		if(Editing_ == 1)
		{
			if(ClientModeMenuString == 1)								// Число
			{
				NumericParamEdit(FirstParametr, 1, 31);
			}
			else if(ClientModeMenuString == 2)					// Месяц
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 1, 12);
			}
			else if(ClientModeMenuString == 3)					// Год
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 2021, 2099);
			}
			else if(ClientModeMenuString == 4)					// Часы
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 00, 23);
			}
			else if(ClientModeMenuString == 5)					// Минуты
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 00, 59);
			}
			else if(ClientModeMenuString == 6)					// Секунды
			{
				NumericParamEdit(FirstParametr+ClientModeMenuString-1, 00, 59);
			}
		}
		
	if(ButtonOk == ButtonSet)
	{
		if(ClientModeMenuString == LastMenuStreeng)	// Выход из этого меню
		{	
//			CurrentDate.Date = *FirstParametr;
//			CurrentDate.Month = *(FirstParametr + 1);
//			CurrentDate.Year = *(FirstParametr + 2);
//			//HAL_RTC_SetDate(&hrtc, &CurrentDate, RTC_FORMAT_BIN);
//			CurrentTime.Hours = *(FirstParametr + 3);
//			CurrentTime.Minutes = *(FirstParametr + 4);
//			CurrentTime.Seconds = *(FirstParametr + 5);
//			//HAL_RTC_SetTime(&hrtc, &CurrentTime, RTC_FORMAT_BIN);
			DateAndTimeTypeDef TT;
			TT.mday = *FirstParametr;
			TT.mon = *(FirstParametr + 1);
			TT.year = *(FirstParametr + 2);
			TT.hour = *(FirstParametr + 3);
			TT.min = *(FirstParametr + 4);
			TT.sec = *(FirstParametr + 5);
			uint32_t UTT= ConvertHRFtimeToUnixTime(&TT);
			SetUnixTime(UTT);
			ClientModeMenuString = 0;
			OldClientModeMenuString = 1;
			MenuLst = SetingsMenu;
			SetingsMenuString = 0;
			OldSetingsMenuString = SetingsMenuString +1;
			ButtonOk = ButtonReset;
			ButtonOkCounter = 0;
		}
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
//uint32_t* Parametr - редактируемый параметр
//uint32_t ParametrLowBorder - минимальное значение
//uint32_t ParametrHighBorder - максимальное значение
void HiddenNumericParamEdit(uint32_t* Parametr, uint32_t ParametrLowBorder, uint32_t ParametrHighBorder, uint8_t* HiddenParameterWasEdited)
{
	static uint32_t ButtonUpCounterEditing;
	uint8_t MyTmpStr[11];
	if(ButtonUp == ButtonSet)
	{
		ButtonUpCounterEditing = (ButtonUpCounterEditing < 100) ? ++ButtonUpCounterEditing : 0;
		if(ButtonUpCounterEditing == 0) 
		{
			*Parametr = (*Parametr >= ParametrHighBorder) ? ParametrLowBorder : *Parametr + 1;
			Hex32ToDecASCII (*Parametr, MyTmpStr);
			WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
			*HiddenParameterWasEdited = 1;
		}
	}
	else
	{
		ButtonUpCounterEditing = 0;
	}
	static uint32_t ButtonDownCounterEditing;

	if(ButtonDown == ButtonSet)
	{
		ButtonDownCounterEditing = (ButtonDownCounterEditing < 100) ? ++ButtonDownCounterEditing : 0;
		if(ButtonDownCounterEditing == 0) 
		{
			*Parametr = (*Parametr <= ParametrLowBorder) ? ParametrHighBorder : *Parametr - 1;
			Hex32ToDecASCII (*Parametr, MyTmpStr);
			WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
			*HiddenParameterWasEdited = 1;
		}
	}
	else
	{
		ButtonDownCounterEditing = 0;
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
//extern PulseInParametersTupeDef PI3;
//extern PulseInParametersTupeDef PI2;
//extern PulseInParametersTupeDef PI1;
typedef struct {
	uint32_t PulseTimeMs;				// —уммарное врем¤ импульсов в мс.
	GPIO_PinState State;				// —осот¤ние импульсного входа 1 или 0
	uint32_t HighStateCounter;	// —четчик времени нахождени¤ пина в высоком состо¤нии
}PulseInParametersTupeDef;
PulseInParametersTupeDef PI3;
PulseInParametersTupeDef PI2;
PulseInParametersTupeDef PI1;

void PulseInputControl(uint32_t* Sum_)
{
	PI3.State = HAL_GPIO_ReadPin(PulseIn3_GPIO_Port,PulseIn3_Pin);
	if(PI3.State == GPIO_PIN_RESET)
	{
		PI3.PulseTimeMs++;
	}
	if((PI3.PulseTimeMs > 0)&&(PI3.State == GPIO_PIN_SET))
	{
		PI3.HighStateCounter = (PI3.HighStateCounter < 500) ? ++PI3.HighStateCounter : 500;
	}
	else
	{
		PI3.HighStateCounter = 0;
	}
	if(PI3.HighStateCounter == 500)
	{
		*Sum_ += (PI3.PulseTimeMs / Settings.PulseDurationPI3)*Settings.ImpulsePricePI3*100;
		if(PI3.PulseTimeMs % Settings.PulseDurationPI3 > Settings.PulseDurationPI3 * 0.9)
		{
			*Sum_ += Settings.ImpulsePricePI3*100;
		}
		
		PI3.PulseTimeMs = 0;
	}
	
	PI2.State = HAL_GPIO_ReadPin(PulseIn2_GPIO_Port,PulseIn2_Pin);
	if(PI2.State == GPIO_PIN_RESET)
	{
		PI2.PulseTimeMs++;
	}
	if((PI2.PulseTimeMs > 0)&&(PI2.State == GPIO_PIN_SET))
	{
		PI2.HighStateCounter = (PI2.HighStateCounter < 500) ? ++PI2.HighStateCounter : 500;
	}
	else
	{
		PI2.HighStateCounter = 0;
	}
	if(PI2.HighStateCounter == 500)
	{
		*Sum_ += (PI2.PulseTimeMs / Settings.PulseDurationPI2)*Settings.ImpulsePricePI2*100;
		if(PI2.PulseTimeMs % Settings.PulseDurationPI2 > Settings.PulseDurationPI2 * 0.9)
		{
			*Sum_ += Settings.ImpulsePricePI2*100;
		}
		
		PI2.PulseTimeMs = 0;
	}
	
	PI1.State = HAL_GPIO_ReadPin(PulseIn1_GPIO_Port,PulseIn1_Pin);
	if(PI1.State == GPIO_PIN_RESET)
	{
		PI1.PulseTimeMs++;
	}
	if((PI1.PulseTimeMs > 0)&&(PI1.State == GPIO_PIN_SET))
	{
		PI1.HighStateCounter = (PI1.HighStateCounter < 500) ? ++PI1.HighStateCounter : 500;
	}
	else
	{
		PI1.HighStateCounter = 0;
	}
	if(PI1.HighStateCounter == 500)
	{
		*Sum_ += (PI1.PulseTimeMs / Settings.PulseDurationPI1)*Settings.ImpulsePricePI1*100;
		if(PI1.PulseTimeMs % Settings.PulseDurationPI1 > Settings.PulseDurationPI1 * 0.9)
		{
			*Sum_ += Settings.ImpulsePricePI1*100;
		}
		
		PI1.PulseTimeMs = 0;
	}
	
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
// 0 - Режим реле, 1 - режим дозирования
// 0 - Откл, 1 - Вкл
void DOControlFc(unsigned ReleMode, unsigned ReleState, GPIO_TypeDef *Port, uint16_t Pin, uint8_t Percent, uint32_t* Counter)
{
	if(ReleMode == 0)
	{
		if(ReleState == 1)
		{
			HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
		}
	}
	if(ReleMode == 1)
	{
		
		if(ReleState == 1)
		{
			*Counter += 1;
			if(*Counter < Percent * 5)
				HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
			*Counter = 0;
		}
			
	
		if(*Counter > 1000)
			*Counter = 0;
	}
}

/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
//uint8_t* Parametr - редактируемый параметр
//uint8_t ParametrLowBorder - минимальное значение
//uint8_t ParametrHighBorder - максимальное значение
void NumericParamEdit8bit(uint8_t* Parametr, uint8_t ParametrLowBorder, uint8_t ParametrHighBorder)
{
	static uint32_t ButtonUpCounterEditing;
	uint8_t MyTmpStr[11];
	if(ButtonUp == ButtonSet)
	{
		ButtonUpCounterEditing = (ButtonUpCounterEditing < 100) ? ++ButtonUpCounterEditing : 0;
		if(ButtonUpCounterEditing == 0) 
		{
			*Parametr = (*Parametr >= ParametrHighBorder) ? ParametrHighBorder : *Parametr + 1;
			Hex32ToDecASCII (*Parametr, MyTmpStr);
			WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
		}
	}
	else
	{
		ButtonUpCounterEditing = 0;
	}
	static uint32_t ButtonDownCounterEditing;

	if(ButtonDown == ButtonSet)
	{
		ButtonDownCounterEditing = (ButtonDownCounterEditing < 100) ? ++ButtonDownCounterEditing : 0;
		if(ButtonDownCounterEditing == 0) 
		{
			*Parametr = (*Parametr <= ParametrLowBorder) ? ParametrLowBorder : *Parametr - 1;
			Hex32ToDecASCII (*Parametr, MyTmpStr);
			WH1602_Print2 ((char*)MyTmpStr, 1, 11, 4, (void (*)())osDelay, 1);
			WH1602_SetDDRAM_Address (0x10);
		}
	}
	else
	{
		ButtonDownCounterEditing = 0;
	}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
void SetDefaults(void)
{
	Settings.ImpulsePricePI3 = 1;		// Цена импульса
	Settings.PulseDurationPI3 = 50;	// Длительность одного импульса
	Settings.ImpulsePricePI2 = 1;		// Цена импульса
	Settings.PulseDurationPI2 = 50;	// Длительность одного импульса
	Settings.ImpulsePricePI1 = 1;		// Цена импульса
	Settings.PulseDurationPI1 = 50;	// Длительность одного импульса
	Settings.WaterButtonNumber = 5; // Номер кнопки включения режима
	Settings.WaterOut1 = 1;					// Номер выхода, включающегося при нажатии кнопки
	Settings.WaterMode1 = 1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.WaterPercent1 = 0;			// Процент в случае дозирования
	Settings.WaterOut2 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.WaterMode2 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.WaterPercent2 = 0;			// Процент в случае дозирования
	Settings.WaterOut3 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.WaterMode3 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.WaterPercent3 = 0;			// Процент в случае дозирования
	Settings.WaterOut4 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.WaterMode4 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.WaterPercent4 = 0;			// Процент в случае дозирования
	Settings.WaterPriceOfSecond = 1;// Стоимость секунды в десятых долях рубля
	Settings.FoamButtonNumber = 6;  // Номер кнопки включения режима
	Settings.FoamOut1 = 2;					// Номер выхода, включающегося при нажатии кнопки
	Settings.FoamMode1 = 1;				  // Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.FoamPercent1 = 0;			// Процент в случае дозирования
	Settings.FoamOut2 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.FoamMode2 = 0;				  // Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.FoamPercent2 = 0;			// Процент в случае дозирования
	Settings.FoamOut3 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.FoamMode3 = 0;				  // Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.FoamPercent3 = 0;			// Процент в случае дозирования
	Settings.FoamOut4 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.FoamMode4 = 0;				  // Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.FoamPercent4 = 0;			// Процент в случае дозирования
	Settings.FoamPriceOfSecond = 1; // Стоимость секунды в десятых долях рубля
	Settings.WaxButtonNumber = 7; 	// Номер кнопки включения режима
	Settings.WaxOut1 = 3;						// Номер выхода, включающегося при нажатии кнопки
	Settings.WaxMode1 = 1;					// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.WaxPercent1 = 0;				// Процент в случае дозирования
	Settings.WaxOut2 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.WaxMode2 = 0;					// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.WaxPercent2 = 0;				// Процент в случае дозирования
	Settings.WaxOut3 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.WaxMode3 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.WaxPercent3 = 0;			// Процент в случае дозирования
	Settings.WaxOut4 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.WaxMode4 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.WaxPercent4 = 0;			// Процент в случае дозирования
	Settings.WaxPriceOfSecond = 1;// Стоимость секунды в десятых долях рубля
	Settings.OsmosButtonNumber = 8; // Номер кнопки включения режима
	Settings.OsmosOut1 = 4;					// Номер выхода, включающегося при нажатии кнопки
	Settings.OsmosMode1 = 1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.OsmosPercent1 = 0;			// Процент в случае дозирования
	Settings.OsmosOut2 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.OsmosMode2 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.OsmosPercent2 = 0;			// Процент в случае дозирования
	Settings.OsmosOut3 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.OsmosMode3 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.OsmosPercent3 = 0;			// Процент в случае дозирования
	Settings.OsmosOut4 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.OsmosMode4 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.OsmosPercent4 = 0;			// Процент в случае дозирования
	Settings.OsmosPriceOfSecond = 1;// Стоимость секунды в десятых долях рубля
	Settings.VacuumClinerButtonNumber = 9; // Номер кнопки включения режима
	Settings.VacuumClinerOut1 = 5;					// Номер выхода, включающегося при нажатии кнопки
	Settings.VacuumClinerMode1 = 1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.VacuumClinerPercent1 = 0;			// Процент в случае дозирования
	Settings.VacuumClinerOut2 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.VacuumClinerMode2 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.VacuumClinerPercent2 = 0;			// Процент в случае дозирования
	Settings.VacuumClinerOut3 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.VacuumClinerMode3 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.VacuumClinerPercent3 = 0;			// Процент в случае дозирования
	Settings.VacuumClinerOut4 = 0;					// Номер выхода, включающегося при нажатии кнопки
	Settings.VacuumClinerMode4 = 0;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.VacuumClinerPercent4 = 0;			// Процент в случае дозирования
	Settings.VacuumClinerPriceOfSecond = 1;// Стоимость секунды в десятых долях рубля
	Settings.AirButtonNumber = 10; // Номер кнопки включения режима
	Settings.AirOut1 = 6;					// Номер выхода, включающегося при нажатии кнопки
	Settings.AirMode1 = 1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.AirPercent1 = 0;			// Процент в случае дозирования
	Settings.AirOut2 = 0;							// Номер выхода, включающегося при нажатии кнопки
	Settings.AirMode2 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.AirPercent2 = 0;					// Процент в случае дозирования
	Settings.AirOut3 = 0;							// Номер выхода, включающегося при нажатии кнопки
	Settings.AirMode3 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.AirPercent3 = 0;					// Процент в случае дозирования
	Settings.AirOut4 = 0;							// Номер выхода, включающегося при нажатии кнопки
	Settings.AirMode4 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.AirPercent4 = 0;					// Процент в случае дозирования
	Settings.AirPriceOfSecond = 1;		// Стоимость секунды в десятых долях рубля
	Settings.PauseFreeMinutes = 1;		// Бесплатные минуты
	Settings.PausePriceOfSecond = 1;	// Цена секунды
	Settings.Dop1ButtonNumber = 11; 	// Номер кнопки включения режима
	Settings.Dop1Out1 = 7;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop1Mode1 = 1;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop1Percent1 = 0;				// Процент в случае дозирования
	Settings.Dop1Out2 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop1Mode2 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop1Percent2 = 0;				// Процент в случае дозирования
	Settings.Dop1Out3 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop1Mode3 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop1Percent3 = 0;				// Процент в случае дозирования
	Settings.Dop1Out4 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop1Mode4 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop1Percent4 = 0;				// Процент в случае дозирования
	Settings.Dop1PriceOfSecond = 1;		// Стоимость секунды в десятых долях рубля
	Settings.Dop2ButtonNumber = 12; 	// Номер кнопки включения режима
	Settings.Dop2Out1 = 8;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop2Mode1 = 1;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop2Percent1 = 0;				// Процент в случае дозирования
	Settings.Dop2Out2 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop2Mode2 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop2Percent2 = 0;				// Процент в случае дозирования
	Settings.Dop2Out3 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop2Mode3 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop2Percent3 = 0;				// Процент в случае дозирования
	Settings.Dop2Out4 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop2Mode4 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop2Percent4 = 0;				// Процент в случае дозирования
	Settings.Dop2PriceOfSecond = 1;		// Стоимость секунды в десятых долях рубля
	Settings.Dop3ButtonNumber = 13; 	// Номер кнопки включения режима
	Settings.Dop3Out1 = 8;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop3Mode1 = 1;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop3Percent1 = 0;				// Процент в случае дозирования
	Settings.Dop3Out2 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop3Mode2 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop3Percent2 = 0;				// Процент в случае дозирования
	Settings.Dop3Out3 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop3Mode3 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop3Percent3 = 0;				// Процент в случае дозирования
	Settings.Dop3Out4 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop3Mode4 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop3Percent4 = 0;				// Процент в случае дозирования
	Settings.Dop3PriceOfSecond = 0;		// Стоимость секунды в десятых долях рубля
	Settings.Dop4ButtonNumber = 14; 	// Номер кнопки включения режима
	Settings.Dop4Out1 = 9;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop4Mode1 = 1;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop4Percent1 = 0;				// Процент в случае дозирования
	Settings.Dop4Out2 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop4Mode2 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop4Percent2 = 0;				// Процент в случае дозирования
	Settings.Dop4Out3 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop4Mode3 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop4Percent3 = 0;				// Процент в случае дозирования
	Settings.Dop4Out4 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop4Mode4 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop4Percent4 = 0;				// Процент в случае дозирования
	Settings.Dop4PriceOfSecond = 1;		// Стоимость секунды в десятых долях рубля
	Settings.Dop5ButtonNumber = 15; 	// Номер кнопки включения режима
	Settings.Dop5Out1 = 10;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop5Mode1 = 1;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop5Percent1 = 0;				// Процент в случае дозирования
	Settings.Dop5Out2 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop5Mode2 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop5Percent2 = 0;				// Процент в случае дозирования
	Settings.Dop5Out3 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop5Mode3 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop5Percent3 = 0;				// Процент в случае дозирования
	Settings.Dop5Out4 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop5Mode4 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop5Percent4 = 0;				// Процент в случае дозирования
	Settings.Dop5PriceOfSecond = 1;		// Стоимость секунды в десятых долях рубля
	Settings.Dop6ButtonNumber = 16; 	// Номер кнопки включения режима
	Settings.Dop6Out1 = 11;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop6Mode1 = 1;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop6Percent1 = 0;				// Процент в случае дозирования
	Settings.Dop6Out2 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop6Mode2 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop6Percent2 = 0;				// Процент в случае дозирования
	Settings.Dop6Out3 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop6Mode3 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop6Percent3 = 0;				// Процент в случае дозирования
	Settings.Dop6Out4 = 0;						// Номер выхода, включающегося при нажатии кнопки
	Settings.Dop6Mode4 = 0;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	Settings.Dop6Percent4 = 0;				// Процент в случае дозирования
	Settings.Dop6PriceOfSecond = 1;		// Стоимость секунды в десятых долях рубля
	Settings.CardKey1 = 0xFE;					// Ключ шифрования карты Mifare
	Settings.CardKey2 = 0xFF;
	Settings.CardKey3 = 0xFF;
	Settings.CardKey4 = 0xFF;
	Settings.CardKey5 = 0xFF;
	Settings.CardKey6 = 0xFF;
	Settings.CardDiscount = 0;				// Сика по карте лояльности
	Settings.CardBonus = 100;					// Бонус при активации карты лоятьности
	Settings.RFID_OnOff = 0;					// Считыватель RFID отключен
	Settings.VendotekStep = 1;				// Шаг изменения денег в рублях при нажатии кнопки +/-
}
























/**/
