/**
  ******************************************************************************
  * @file    MyDefines.h
  * @brief   This file contains headers of my functions.
  ******************************************************************************
*/

 /* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __MYDEFINES_H
#define __MYDEFINES_H

//#include "stdint.h"
#include "stm32f1xx_hal.h"

//#define CardsFactoryReset

#define MatrixStreeng 16
#define MatrixColumn	4
extern volatile uint8_t MainMatrixArray[MatrixStreeng][MatrixColumn];

#define SetA HAL_GPIO_WritePin(MatrixA_GPIO_Port, MatrixA_Pin, GPIO_PIN_SET)
#define SetB HAL_GPIO_WritePin(MatrixB_GPIO_Port, MatrixB_Pin, GPIO_PIN_SET)
#define ResetA HAL_GPIO_WritePin(MatrixA_GPIO_Port, MatrixA_Pin, GPIO_PIN_RESET)
#define ResetB HAL_GPIO_WritePin(MatrixB_GPIO_Port, MatrixB_Pin, GPIO_PIN_RESET)

extern uint32_t Sum;
extern uint32_t CashSum;
//extern uint32_t CashlessSum;
extern uint32_t SumFromClientCard;

typedef struct {
	uint32_t ImpulsePricePI3;		// Цена импульса
	uint32_t PulseDurationPI3;	// Длительность одного импульса
	uint32_t ImpulsePricePI2;		// Цена импульса
	uint32_t PulseDurationPI2;	// Длительность одного импульса
	uint32_t ImpulsePricePI1;		// Цена импульса
	uint32_t PulseDurationPI1;	// Длительность одного импульса
	uint32_t WaterButtonNumber; // Номер кнопки включения режима
	uint32_t WaterOut1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t WaterMode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t WaterPercent1;			// Процент в случае дозирования
	uint32_t WaterOut2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t WaterMode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t WaterPercent2;			// Процент в случае дозирования
	uint32_t WaterOut3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t WaterMode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t WaterPercent3;			// Процент в случае дозирования
	uint32_t WaterOut4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t WaterMode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t WaterPercent4;			// Процент в случае дозирования
	uint32_t WaterPriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t FoamButtonNumber;  // Номер кнопки включения режима
	uint32_t FoamOut1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t FoamMode1;				  // Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t FoamPercent1;			// Процент в случае дозирования
	uint32_t FoamOut2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t FoamMode2;				  // Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t FoamPercent2;			// Процент в случае дозирования
	uint32_t FoamOut3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t FoamMode3;				  // Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t FoamPercent3;			// Процент в случае дозирования
	uint32_t FoamOut4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t FoamMode4;				  // Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t FoamPercent4;			// Процент в случае дозирования
	uint32_t FoamPriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t WaxButtonNumber; // Номер кнопки включения режима
	uint32_t WaxOut1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t WaxMode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t WaxPercent1;			// Процент в случае дозирования
	uint32_t WaxOut2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t WaxMode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t WaxPercent2;			// Процент в случае дозирования
	uint32_t WaxOut3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t WaxMode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t WaxPercent3;			// Процент в случае дозирования
	uint32_t WaxOut4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t WaxMode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t WaxPercent4;			// Процент в случае дозирования
	uint32_t WaxPriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t OsmosButtonNumber; // Номер кнопки включения режима
	uint32_t OsmosOut1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t OsmosMode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t OsmosPercent1;			// Процент в случае дозирования
	uint32_t OsmosOut2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t OsmosMode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t OsmosPercent2;			// Процент в случае дозирования
	uint32_t OsmosOut3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t OsmosMode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t OsmosPercent3;			// Процент в случае дозирования
	uint32_t OsmosOut4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t OsmosMode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t OsmosPercent4;			// Процент в случае дозирования
	uint32_t OsmosPriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t VacuumClinerButtonNumber; // Номер кнопки включения режима
	uint32_t VacuumClinerOut1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t VacuumClinerMode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t VacuumClinerPercent1;			// Процент в случае дозирования
	uint32_t VacuumClinerOut2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t VacuumClinerMode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t VacuumClinerPercent2;			// Процент в случае дозирования
	uint32_t VacuumClinerOut3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t VacuumClinerMode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t VacuumClinerPercent3;			// Процент в случае дозирования
	uint32_t VacuumClinerOut4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t VacuumClinerMode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t VacuumClinerPercent4;			// Процент в случае дозирования
	uint32_t VacuumClinerPriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t AirButtonNumber; // Номер кнопки включения режима
	uint32_t AirOut1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t AirMode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t AirPercent1;			// Процент в случае дозирования
	uint32_t AirOut2;							// Номер выхода, включающегося при нажатии кнопки
	uint32_t AirMode2;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t AirPercent2;					// Процент в случае дозирования
	uint32_t AirOut3;							// Номер выхода, включающегося при нажатии кнопки
	uint32_t AirMode3;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t AirPercent3;					// Процент в случае дозирования
	uint32_t AirOut4;							// Номер выхода, включающегося при нажатии кнопки
	uint32_t AirMode4;						// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t AirPercent4;					// Процент в случае дозирования
	uint32_t AirPriceOfSecond;		// Стоимость секунды в десятых долях рубля
	uint32_t PauseFreeMinutes;		// Бесплатные минуты
	uint32_t PausePriceOfSecond;	// Цена секунды
	uint32_t Dop1ButtonNumber; // Номер кнопки включения режима
	uint32_t Dop1Out1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop1Mode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop1Percent1;			// Процент в случае дозирования
	uint32_t Dop1Out2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop1Mode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop1Percent2;			// Процент в случае дозирования
	uint32_t Dop1Out3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop1Mode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop1Percent3;			// Процент в случае дозирования
	uint32_t Dop1Out4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop1Mode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop1Percent4;			// Процент в случае дозирования
	uint32_t Dop1PriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t Dop2ButtonNumber; // Номер кнопки включения режима
	uint32_t Dop2Out1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop2Mode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop2Percent1;			// Процент в случае дозирования
	uint32_t Dop2Out2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop2Mode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop2Percent2;			// Процент в случае дозирования
	uint32_t Dop2Out3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop2Mode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop2Percent3;			// Процент в случае дозирования
	uint32_t Dop2Out4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop2Mode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop2Percent4;			// Процент в случае дозирования
	uint32_t Dop2PriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t Dop3ButtonNumber; // Номер кнопки включения режима
	uint32_t Dop3Out1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop3Mode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop3Percent1;			// Процент в случае дозирования
	uint32_t Dop3Out2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop3Mode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop3Percent2;			// Процент в случае дозирования
	uint32_t Dop3Out3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop3Mode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop3Percent3;			// Процент в случае дозирования
	uint32_t Dop3Out4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop3Mode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop3Percent4;			// Процент в случае дозирования
	uint32_t Dop3PriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t Dop4ButtonNumber; // Номер кнопки включения режима
	uint32_t Dop4Out1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop4Mode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop4Percent1;			// Процент в случае дозирования
	uint32_t Dop4Out2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop4Mode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop4Percent2;			// Процент в случае дозирования
	uint32_t Dop4Out3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop4Mode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop4Percent3;			// Процент в случае дозирования
	uint32_t Dop4Out4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop4Mode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop4Percent4;			// Процент в случае дозирования
	uint32_t Dop4PriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t Dop5ButtonNumber; // Номер кнопки включения режима
	uint32_t Dop5Out1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop5Mode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop5Percent1;			// Процент в случае дозирования
	uint32_t Dop5Out2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop5Mode2;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop5Percent2;			// Процент в случае дозирования
	uint32_t Dop5Out3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop5Mode3;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop5Percent3;			// Процент в случае дозирования
	uint32_t Dop5Out4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop5Mode4;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop5Percent4;			// Процент в случае дозирования
	uint32_t Dop5PriceOfSecond;// Стоимость секунды в десятых долях рубля
	uint32_t Dop6ButtonNumber; // Номер кнопки включения режима
	uint32_t Dop6Out1;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop6Mode1;				// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop6Percent1;			// Процент в случае дозирования
	uint32_t Dop6Out2;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop6Mode2;					// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop6Percent2;			// Процент в случае дозирования
	uint32_t Dop6Out3;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop6Mode3;					// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop6Percent3;			// Процент в случае дозирования
	uint32_t Dop6Out4;					// Номер выхода, включающегося при нажатии кнопки
	uint32_t Dop6Mode4;					// Режим выхода, включающегося при нажатии кнопки (реле/дозирование)
	uint32_t Dop6Percent4;			// Процент в случае дозирования
	uint32_t Dop6PriceOfSecond;	// Стоимость секунды в десятых долях рубля
	uint32_t CardKey1;					// Ключ шифрования карты Mifare
	uint32_t CardKey2;
	uint32_t CardKey3;
	uint32_t CardKey4;
	uint32_t CardKey5;
	uint32_t CardKey6;
	uint32_t CardDiscount;			// Сика по карте лояльности
	uint32_t CardBonus;					// Бонус при активации карты лоятьности
	uint32_t RFID_OnOff;				// Считыватель карт 0 - отключен/ 1 - включен
	uint32_t VendotekStep;			// Шаг изменения денег в рублях при нажатии кнопки +/-
} SettingsTypedef;
extern SettingsTypedef Settings;

typedef enum{
	ButtonReset,
	ButtonSet,
}ButtonStateTypeDef;

extern ButtonStateTypeDef ButtonUp;
extern ButtonStateTypeDef ButtonDown;
extern ButtonStateTypeDef ButtonOk;
extern ButtonStateTypeDef ButtonLeft;
extern ButtonStateTypeDef ButtonRight;
extern uint32_t ButtonUpCounter;
extern uint32_t ButtonDownCounter;
extern uint32_t ButtonOkCounter;
extern uint32_t ButtonLeftCounter;
extern uint32_t ButtonRightCounter;

extern ButtonStateTypeDef BI1;
extern ButtonStateTypeDef BI2;
extern ButtonStateTypeDef BI3;
extern ButtonStateTypeDef BI4;
extern ButtonStateTypeDef BI5;
extern ButtonStateTypeDef BI6;
extern ButtonStateTypeDef BI7;
extern ButtonStateTypeDef BI8;
extern ButtonStateTypeDef BI9;
extern ButtonStateTypeDef BI10;
extern ButtonStateTypeDef BI11;
extern ButtonStateTypeDef BI12;
extern ButtonStateTypeDef BI13;
extern ButtonStateTypeDef BI14;
extern ButtonStateTypeDef BI15;
extern ButtonStateTypeDef BI16;

typedef enum{
	SetingsMenu,
	PI1Menu,
	PI2Menu,
	PI3Menu,
	WaterMenu,
	FoamMenu,
	WaxMenu,
	OsmosMenu,
	VacuumCleanerMenu,
	AirMenu,
	PauseMenu,
	Dop1Menu,
	Dop2Menu,
	Dop3Menu,
	Dop4Menu,
	Dop5Menu,
	Dop6Menu,
	CardsMenu,
	VendotekMenu,
	RTCMenu,
}MenuLstTypeDef;
extern MenuLstTypeDef MenuLst;
extern uint32_t SetingsMenuString;
extern uint32_t OldSetingsMenuString;
extern uint32_t PIMenuString;
extern uint32_t MenuString;

typedef struct {
	char StrSets[16];				//"   Настройки    "
	char StrPI1Sets[16];		//"Имп.вход.1      "
	char StrPI2Sets[16];		//"Имп.вход.2      "
	char StrPI3Sets[16];		//"Имп.вход.3      "
	char WaterSets[16];
	char Foam[16];
	char Wax[16];
	char Osmos[16];
	char VacuumCleaner[16];
	char Air[16];
	char Pause[16];					//"     Пауза      "
	char Dop1[16];					//"Доп реж 1       "
	/*char Dop2[16];					//"Доп реж 2       "
	char Dop3[16];					//"Доп реж 3       "
	char Dop4[16];					//"Доп реж 4       "
	char Dop5[16];					//"Доп реж 5       "
	char Dop6[16];					//"Доп реж 6       "*/
	char Cards[16];					//"Карты           "
	char Vendotek[16];			//"Vendotek        "
	char RealTime[16];			//"Время        "
	char EmptyStr[16];			// Пустая строка
}SetsMenyStringsTypeDef;
extern SetsMenyStringsTypeDef SetsMenyStrings;

typedef struct {
	char ImpulsePricePI[16];		//"Цена имп.       "
	char PulseDurationPI[16];		//"Длит.имп        "
	char Back[16];							//"Выход           "
	char EmptyStr[16];					// Пустая строка
}PIMenyStringsTypeDef;
extern PIMenyStringsTypeDef PIMenyStrings;

typedef struct {
	char MenuMame[16];					//"                "Название меню Вода, Пена, Воск ...
	char ButtonNum[16];					//"Номер кнопки    "
	char Output1[16];						//"Выход 1         "
	char Mode1[16];							//"Режим           "
	char Percent1[16];					//"Процент         "
	char Output2[16];						//"Выход 2         "
	char Mode2[16];							//"Режим           "
	char Percent2[16];					//"Процент         "
	char Output3[16];						//"Выход 3         "
	char Mode3[16];							//"Режим           "
	char Percent3[16];					//"Процент         "
	char Output4[16];						//"Выход 4         "
	char Mode4[16];							//"Режим           "
	char Percent4[16];					//"Процент         "
	char PriceOfSecond[16];			//"Цена сек        "
	char Exit[16];							//"Выход           "
	char EmptyStr[16];					// Пустая строка
}Cl_ModeMenuTypeDef;
extern Cl_ModeMenuTypeDef ClM_MenuStrings;

#define SettingsFlashAddress 0x0807F800

typedef enum{
	IdlMode,
	PauseMode,
	CashPaymentRecieveMode,
	Water,
	Foam,
	Wax,
	Osmos,
	VacuumCliner,
	Air,
	Dop1Mode,
	Dop2Mode,
	Dop3Mode,
	Dop4Mode,
	Dop5Mode,
	Dop6Mode,
	CashlessPaymentRecieveMode,
	ReadyToWash,
	WaitBankCard,
	ClientCardIsRead,
}WorkModeTypeDef;

extern WorkModeTypeDef WashMode;

#define ReleModuleTxBufSize 50
extern volatile uint8_t ReleModuleTxBuf[ReleModuleTxBufSize];
extern volatile uint32_t ReleModuleTxBuf1p;
extern volatile uint32_t ReleModuleTxBuf2p;

typedef struct{
	unsigned Rele1Mode: 	1;		// 0 - Режим реле, 1 - режим дозирования
	unsigned Rele1State: 	1;		// 0 - Откл, 1 - Вкл
	unsigned Rele2Mode: 	1;		// 0 - Режим реле, 1 - режим дозирования
	unsigned Rele2State: 	1;		// 0 - Откл, 1 - Вкл
	unsigned Rele3Mode: 	1;		// 0 - Режим реле, 1 - режим дозирования
	unsigned Rele3State: 	1;		// 0 - Откл, 1 - Вкл
	unsigned Rele4Mode: 	1;		// 0 - Режим реле, 1 - режим дозирования
	unsigned Rele4State: 	1;		// 0 - Откл, 1 - Вкл
	unsigned Rele5Mode: 	1;
	unsigned Rele5State: 	1;
	unsigned Rele6Mode: 	1;
	unsigned Rele6State: 	1;
	unsigned Rele7Mode: 	1;
	unsigned Rele7State: 	1;
	unsigned Rele8Mode: 	1;
	unsigned Rele8State: 	1;
	unsigned Rele9Mode: 	1;
	unsigned Rele9State: 	1;
	unsigned Rele10Mode: 	1;
	unsigned Rele10State: 1;
	unsigned Rele11Mode: 	1;
	unsigned Rele11State: 1;
	unsigned Rele12Mode: 	1;
	unsigned Rele12State: 1;
	unsigned Rele13Mode: 	1;
	unsigned Rele13State: 1;
	unsigned Rele14Mode: 	1;
	unsigned Rele14State: 1;
	unsigned Rele15Mode: 	1;
	unsigned Rele15State: 1;
	unsigned Rele16Mode: 	1;
	unsigned Rele16State: 1;
}ReleOutputStateTypedef;

extern volatile ReleOutputStateTypedef RO;

typedef enum{
	NoTransmission,
	TransmissionInProcess
}TransmissionStateTypedef;
extern TransmissionStateTypedef TransmissionToReleModuleState;

typedef struct {
	char MenuMame[16];					//"                "Название меню Вода, Пена, Воск ...
	char FreeMinutes[16];				//"Бесплатн мин    "
	char PriceOfSecond[16];			//"Цена секунды    "
	char Exit[16];							//"Выход           "
	char EmptyStr[16];					// Пустая строка
}PauseMenuTypeDef;
extern PauseMenuTypeDef PauseMenuStrings;

extern uint32_t FreePauseSeconds;

#define RS485PC_TransmitON HAL_GPIO_WritePin(RS485TxEn_PC_GPIO_Port, RS485TxEn_PC_Pin, GPIO_PIN_SET);		//Переключает микросхему RS485 в состояние передачи
#define RS485PC_ReceiveON HAL_GPIO_WritePin(RS485TxEn_PC_GPIO_Port, RS485TxEn_PC_Pin, GPIO_PIN_RESET);	//Переключает микросхему RS485 в состояние приема

extern uint8_t RS485PC_TransferCompleted; // Установка бита завершения передачи

#define PC_TxBufSize 300
extern uint8_t PC_TxBuf[PC_TxBufSize];
extern volatile uint32_t PC_TxBuf1p;
extern volatile uint32_t PC_TxBuf2p;
#define PC_RxBufSize 300
extern uint8_t PC_RxBuf[PC_RxBufSize];
extern volatile uint32_t PC_RxBuf1p;
extern volatile uint32_t PC_RxBuf2p;


typedef struct {
	char MenuMame[16];					//"                "Название меню Вода, Пена, Воск ...
	char Key1[16];							//"Ключ 1          "
	char Key2[16];							//"Ключ 2          "
	char Key3[16];							//"Ключ 3          "
	char Key4[16];							//"Ключ 4          "
	char Key5[16];							//"Ключ 4          "
	char Key6[16];							//"Ключ 4          "
	char Discount[16];					//"Скидка          "
	char Bonus[16];							//"Бонус           "
	char Exit[16];							//"Выход           "
	char Cardreader[16];				//"Считыватель  	 "
	char EmptyStr[16];					// Пустая строка
}CardsMenuTypeDef;
extern CardsMenuTypeDef CardsMenuStrings;

extern uint8_t DiscountReadFromCard;
extern uint32_t CardDelay;

#define VendotekRxBufSize 500
extern uint8_t VendotekRxBuf[VendotekRxBufSize];
extern uint32_t VendotekRxBuf1p;
extern uint32_t VendotekRxBuf2p;

#define VendotekTxBufSize 500
extern uint8_t VendotekTxBuf[VendotekTxBufSize];
extern uint32_t VendotekTxBuf1p;
extern uint32_t VendotekTxBuf2p;

extern uint8_t VendotekTxBufAdd[VendotekTxBufSize];
//extern uint32_t VendotekTxBufAdd1p;
//extern uint32_t VendotekTxBufAdd2p;
extern uint32_t MoneyForCashlessPaymentRequest;

typedef struct{
	uint8_t Out1Percent;
	uint8_t Out2Percent;
	uint8_t Out3Percent;
	uint8_t Out4Percent;
	uint8_t Out5Percent;
	uint8_t Out6Percent;
	uint8_t Out7Percent;
	uint8_t Out8Percent;
	uint8_t Out9Percent;
	uint8_t Out10Percent;
	uint8_t Out11Percent;
	uint8_t Out12Percent;
	uint8_t Out13Percent;
	uint8_t Out14Percent;
	uint8_t Out15Percent;
	//uint8_t Out16Percent;
}OutputPercentTypeDef;

extern OutputPercentTypeDef OutputPercent;

typedef struct {
	char MenuMame[16];					//"                "Название меню Вода, Пена, Воск ...
	char Step[16];							//"Шаг             "
	char Exit[16];							//"Выход           "
	char EmptyStr[16];					// Пустая строка
}VendotekMenuTypeDef;
extern VendotekMenuTypeDef VendotekMenuStrings;

#define VFD_TxBufSize 100
extern uint8_t VFD_TxBuf[VFD_TxBufSize];
extern volatile uint32_t VFD_TxBuf1p;
extern volatile uint32_t VFD_TxBuf2p;
#define VFD_RxBufSize 100
extern uint8_t VFD_RxBuf[VFD_RxBufSize];
extern volatile uint32_t VFD_RxBuf1p;
extern volatile uint32_t VFD_RxBuf2p;
#define VFD_TransmitON HAL_GPIO_WritePin(RS_485ReleTxEn_GPIO_Port, RS_485ReleTxEn_Pin, GPIO_PIN_SET);		//Переключает микросхему RS485 в состояние передачи
#define VFD_ReceiveON HAL_GPIO_WritePin(RS_485ReleTxEn_GPIO_Port, RS_485ReleTxEn_Pin, GPIO_PIN_RESET);	//Переключает микросхему RS485 в состояние приема

typedef struct {
	char MenuMame[16];					//"                "Название меню Вода, Пена, Воск ...
	char Date[16];							//"Число           "
	char Month[16];							//"Месяц           "
	char Year[16];							//"Год             "
	char Hours[16];							//"Часы            "
	char Minytes[16];						//"Минуты          "
	char Seconds[16];						//"Секунды         "
	char Exit[16];							//"Выход           "
	char EmptyStr[16];					// Пустая строка
}RTCMenuTypeDef;
extern RTCMenuTypeDef RTCMenuStrings;
	
typedef struct {
	uint32_t Date;
	uint32_t Month;
	uint32_t Year;
	uint32_t Hours;
	uint32_t Minytes;
	uint32_t Seconds;
}TempRTCDataTypeDef;
extern TempRTCDataTypeDef TempRTCData;
//extern RTC_TimeTypeDef CurrentTime;
//extern RTC_DateTypeDef CurrentDate;



#endif /* __MYDEFINES_H */
