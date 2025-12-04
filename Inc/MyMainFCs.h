/**
  ******************************************************************************
  * @file    MyMainFCs.h
  * @brief   This file contains headers of my functions.
  ******************************************************************************
*/

 /* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __MYMAINFCS_H
#define __MYMAINFCS_H

#include "stdint.h"
#include "MyDefines.h"
//#include "cmsis_os.h"
#include "stm32f1xx_hal.h"

//#define ClearAllLeds GPIOE->ODR &= 0x0FFF; //HAL_GPIO_WritePin(LB9_GPIO_Port, LB9_Pin, GPIO_PIN_RESET);

void ButtonsHandler(void);	// Обработчик нажатия кнопок
//void PiMenuImplementation(void);
void Menu(void);						// Меню
uint32_t FLASH_Read(uint32_t Address); // Чтение из FLASH-памяти 4 байт
void SaveSettingsToFlash(uint32_t FlashAddr, uint32_t* SramSettingsAddr, uint32_t SettingsSize); // Сохранение уставок во Flash память
void AddTag(uint8_t TagNum, uint16_t DataLen, uint8_t* DataPointer, uint8_t* BufForSave, uint32_t* BufForSave1p, uint32_t BufForSaveSize);

void NumericParamEdit(uint32_t* Parametr, uint32_t ParametrLowBorder, uint32_t ParametrHighBorder);
void EnableDisableParamEdit(uint32_t* Parametr);
void OffOnParamEdit(uint32_t* Parametr);
void OnOffOutput(uint32_t OutputNumber, uint32_t OutputState, uint32_t OutputMode, uint32_t OutPercent);
void ClientButtonsControl(WorkModeTypeDef* CurrentMode, uint32_t *KeepaliveTimer_);
void ButtonLedControl(WorkModeTypeDef* CurrentMode);
void MoneySubtraction(WorkModeTypeDef* CurrentMode, uint32_t* CurrentSum);
void PauseMenuImplementation(char* FirstString, uint32_t* FirstParametr, char* MenuStrings);
void CardsMenuImplementation(char* FirstString, uint32_t* FirstParametr, char* MenuStrings);
void HiddenNumericParamEdit(uint32_t* Parametr, uint32_t ParametrLowBorder, uint32_t ParametrHighBorder, uint8_t* HiddenParameterWasEdited);
void PulseInputControl(uint32_t* Sum_);
void DOControlFc(unsigned ReleMode, unsigned ReleState, GPIO_TypeDef *Port, uint16_t Pin, uint8_t Percent, uint32_t* Counter);
void NumericParamEdit8bit(uint8_t* Parametr, uint8_t ParametrLowBorder, uint8_t ParametrHighBorder);
void SetDefaults(void);
void VendotekMenuImplementation(char* FirstString, uint32_t* FirstParametr, char* MenuStrings);
void RTCMenuImplementation(char* FirstString, uint32_t* FirstParametr, char* MenuStrings, uint8_t LastMenuStreeng);

#endif /* __MYMAINFCS_H */
