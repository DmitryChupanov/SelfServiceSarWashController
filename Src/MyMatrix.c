#include "MyMatrix.h"
#include "stm32f103xe.h"
//#include "MyDefines.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "MyCommon_FCs.h"

#define RuningStringSpeed 70

#pragma push
#pragma O0
void Welcom (WorkModeTypeDef* CurrentMode)
{
	if(*CurrentMode != IdlMode) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Well[8] =
	{477359900,
	613025954,
	613025954,
	613142306,
	613034018,
	2122983458,
	1114884124,
	0};

	uint32_t Come1[8]=
	{0,
	4190708238,
	2317952274,
	2317699218,
	2317584530,
	2317701010,
	2317953170,
	2311661730};

	uint32_t Come2[8]=
	{0,
	1942109825,
	2317682817,
	2317912193,
	2345175265,
	2318370961,
	2317912208,
	1942522081};
	
	uint32_t* Target = (uint32_t *) &MainMatrixArray[8][0];
//	uint64_t TmpVar;
	
	for(uint8_t i = 0; i < 8; i++)
	{
		*(Target+i) = 0;
	}
	
	Target = (uint32_t *) MainMatrixArray;	// Вывод надписи "Добро"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)				// Пробегает строки с 0 по 7
		{
			*(Target+i) = htonl(Well[i] >> j);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	
	
	Target = (uint32_t *) &MainMatrixArray[8][0];	// Вывод надписи "Пожаловать"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = htonl(*(Target+i)) << 1;
//			*(Target+i) |= ((Come1[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Come2[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come2[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	//--------------------------- Очистка матрицы ----------------------------------------
	Target = (uint32_t *) MainMatrixArray;	// Очистка матрицы
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 16; i++)				// Пробегает строки с 0 по 15
		{
			*(Target+i) = htonl(htonl(*(Target+i)) << 1);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	//---------------------------- Вывод "Внесите оплату" -----------------------------------------
	Come1[0]= 3837577406;
	Come1[1]= 2493589640;
	Come1[2]= 2493581704;
	Come1[3]= 3887925896;
	Come1[4]= 2493582472;
	Come1[5]= 2493589640;
	Come1[6]=	3837577352;
	Come1[7]= 0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "Внесит"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Come1[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}

	Come1[0]= 4034126728;
	Come1[1]= 2156536980;
	Come1[2]= 2156536994;
	Come1[3]= 4035585186;
	Come1[4]= 2156537022;
	Come1[5]= 2156536994;
	Come1[6]=	4034013346;
	Come1[7]= 0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "е опла"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Come1[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}	

	if(Settings.RFID_OnOff == 0) // Если считыватель RFID отключен в настройках
	{
		Come1[0]=4198498304;
		Come1[1]=574619648;
		Come1[2]=574619648;
		Come1[3]=566231040;
		Come1[4]=541065216;
		Come1[5]=541065216;
		Come1[6]=595591168;
		Come1[7]=0;
		Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "ту или"
		for(int8_t j = 31; j >= 0; j--)
		{
			if(*CurrentMode != IdlMode) return;
			for(uint8_t i = 0; i < 8; i++)
			{
				uint32_t TmpVar = htonl(*(Target+i)) << 1;
				TmpVar |= (Come1[i] >> j)& 0x00000001;
				*(Target+i) = htonl(TmpVar);
			}
			if(*CurrentMode != IdlMode) return;
			osDelay(RuningStringSpeed);
		}	
	}
	
	if(Settings.RFID_OnOff == 1)  //Если считыватель RFID включен в настройках
	{
	Come1[0]=4198568913;
	Come1[1]=574689873;
	Come1[2]=574698067;
	Come1[3]=566317653;
	Come1[4]=541168217;
	Come1[5]=541135441;
	Come1[6]=595661905;
	Come1[7]=0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "ту или"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}	
	
	Come1[0]=263787470;
	Come1[1]=145035857;
	Come1[2]=145044049;
	Come1[3]=146362961;
	Come1[4]=144806481;
	Come1[5]=144773713;
	Come1[6]=144774222;
	Come1[7]=0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "прило"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	
	Come1[0]=1427627785;
	Come1[1]=1427181578;
	Come1[2]=959516684;
	Come1[3]=290529032;
	Come1[4]=965808140;
	Come1[5]=1427181578;
	Come1[6]=1427185417;
	Come1[7]=0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "жите к"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	
	Come1[0]=597640228;
	Come1[1]=1380205608;
	Come1[2]=2319729712;
	Come1[3]=2340699168;
	Come1[4]=4194567216;
	Come1[5]=2315535400;
	Come1[6]=2315532325;
	Come1[7]=0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "арту к"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	
	Come1[0]=4099884529;
	Come1[1]=2488288322;
	Come1[2]=2496676932;
	Come1[3]=2506062916;
	Come1[4]=2521842759;
	Come1[5]=2488288324;
	Come1[6]=341787716;
	Come1[7]=0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "лиента"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	
	
	Come1[0]=37865634;
	Come1[1]=2189568162;
	Come1[2]=1124206758;
	Come1[3]=1107431338;
	Come1[4]=3271688370;
	Come1[5]=1115824290;
	Come1[6]=1111605410;
	Come1[7]=0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "к счи"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	
	Come1[0]=4195813627;
	Come1[1]=571773986;
	Come1[2]=571777570;
	Come1[3]=597107235;
	Come1[4]=575979042;
	Come1[5]=575971874;
	Come1[6]=597107235;
	Come1[7]=0;
	Target = (uint32_t *) &MainMatrixArray[5][0];	// Вывол надписи "тывате"
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	
	Come1[0]=3886481408;
	Come1[1]=78151680;
	Come1[2]=78151680;
	Come1[3]=3837296640;
	Come1[4]=78151680;
	Come1[5]=78151680;
	Come1[6]=3903258624;
	Come1[7]=0;
	for(int8_t j = 31; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 8; i++)
		{
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Come1[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(RuningStringSpeed);
	}
	}
	
	
	//--------------------------- Очистка матрицы ----------------------------------------
	Target = (uint32_t *) MainMatrixArray;	// Очистка матрицы
	for(int8_t j = 16; j >= 0; j--)
	{
		if(*CurrentMode != IdlMode) return;
		for(uint8_t i = 0; i < 16; i++)				// Пробегает строки с 0 по 15
		{
			*(Target+i) = htonl(htonl(*(Target+i)) << 1);
		}
		if(*CurrentMode != IdlMode) return;
		osDelay(100);
	}
	if(*CurrentMode != IdlMode) return;
	osDelay(2000);

}
#pragma pop
/**************************************************************************************************************************************************/

/**************************************************************************************************************************************************/
void ClearMatrix(uint32_t* Target_)
{
		for(uint8_t i = 0; i < 16; i++)				// Пробегает строки с 0 по 15
		{
			*(Target_+i) = 0;
		}
}
/**************************************************************************************************************************************************/

/**************************************************************************************************************************************************/
void ClearUpHalfMatrix(uint32_t* Target_)
{
		for(uint8_t i = 0; i < 8; i++)				// Пробегает строки с 0 по 8
		{
			*(Target_+i) = 0;
		}
}
/**************************************************************************************************************************************************/

/**************************************************************************************************************************************************/
void ClearDownHalfMatrix(uint32_t* Target_)
{
		for(uint8_t i = 8; i < 16; i++)				// Пробегает строки с 8 по 15
		{
			*(Target_+i) = 0;
		}
}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
//uint32_t* Target_ - указатель на начало массива, из которого отображается изображение на матрице
//uint32_t PrintStartColumnTarget - стартовая колонка массива, начиная с которой печатается начертание символа в массиве, на который указывает uint32_t* Target_ 
//uint32_t* Source - указатель на начертание печатаемого символа
void PrintUpHalfMatrix(uint32_t* Target_,uint32_t PrintStartColumnTarget, uint32_t* Source)
{
	for(uint8_t i = 0; i < 8; i++)				// Пробегает строки с 0 по 15
	{
		*(Target_+i) |= htonl(*(Source+i)>>PrintStartColumnTarget);
	}

}
/**************************************************************************************************************************************************/
/**************************************************************************************************************************************************/
void Money(WorkModeTypeDef* CurrentMode, uint32_t MoneyKop, uint32_t* Target)
{
	//static uint32_t OldMoney;
	//uint32_t MoneyToDisplay = MoneyKop / 10;
	uint32_t Money_ = MoneyKop / 100;
//	if(*CurrentMode != PaymentRecieveMode) 
//	{
//		OldMoney = 0;
//		return;
//	}
	static uint32_t Zero [8] = {1879048192, 2281701376, 2281701376, 2281701376, 2281701376, 2281701376, 2281701376, 1879048192};
	static uint32_t One  [8] = {268435456, 805306368, 1879048192, 2952790016, 805306368, 805306368, 805306368, 805306368};
	static uint32_t Two  [8] = {1879048192, 2281701376, 2281701376, 134217728, 268435456, 536870912, 1073741824, 4160749568};
	static uint32_t Three[8] = {1879048192, 2281701376, 134217728, 805306368, 134217728, 134217728, 2281701376, 1879048192};
	static uint32_t Four [8] = {2281701376, 2281701376, 2281701376, 2281701376, 4160749568, 134217728, 134217728, 134217728};
	static uint32_t Five [8] = {4160749568, 2147483648, 2147483648, 4026531840, 134217728, 134217728, 2281701376, 1879048192};
	static uint32_t Six	 [8] = {1879048192, 2281701376, 2147483648, 4026531840, 2281701376, 2281701376, 2281701376, 1879048192};
	static uint32_t Seven[8] = {4160749568, 2281701376, 134217728, 268435456, 536870912, 1073741824, 1073741824, 1073741824};
	static uint32_t Eight[8] = {1879048192, 2281701376, 2281701376, 1879048192, 2281701376, 2281701376, 2281701376, 1879048192};
	static uint32_t Nine [8] = {1879048192, 2281701376, 2281701376, 2281701376, 2013265920, 134217728, 2281701376, 1879048192};
	static uint32_t Ruble[8] = {1879048192,1207959552,1207959552,1207959552,4026531840,1073741824,4026531840,1073741824};

	
//	if((OldMoney != Money_)||((Money_ == 0)&&(*CurrentMode == CashPaymentRecieveMode)))
//	{
		uint32_t Remainder;
		uint32_t Thousands;
		uint32_t Hundreds;
		uint32_t Tens;
		uint32_t Ones;
		Thousands = Money_ / 1000;
		Remainder =	Money_ % 1000;
		Hundreds = Remainder / 100;
		Remainder = Remainder % 100;
		Tens = Remainder / 10;
		Ones = Remainder % 10;
		
		for(uint8_t i = 0; i < 8; i++)
		{
			if((Thousands == 0)&&(Hundreds == 0)&&(Tens == 0))	// Отображение рублей
			{
				ClearUpHalfMatrix(Target);
				switch(Ones)
				{
					case 0: PrintUpHalfMatrix(Target,10, Zero); break;
					case 1: PrintUpHalfMatrix(Target,10, One); break;
					case 2: PrintUpHalfMatrix(Target,10, Two); break;
					case 3: PrintUpHalfMatrix(Target,10, Three); break;
					case 4: PrintUpHalfMatrix(Target,10, Four); break;
					case 5: PrintUpHalfMatrix(Target,10, Five); break;
					case 6: PrintUpHalfMatrix(Target,10, Six); break;
					case 7: PrintUpHalfMatrix(Target,10, Seven); break;
					case 8: PrintUpHalfMatrix(Target,10, Eight); break;
					case 9: PrintUpHalfMatrix(Target,10, Nine); break;
				}
				PrintUpHalfMatrix(Target,16, Ruble);
			}
			else if((Thousands == 0)&&(Hundreds == 0))		// Отображение десятков и единиц рублей
			{
				ClearUpHalfMatrix(Target);
				switch(Tens)
				{
					case 0: PrintUpHalfMatrix(Target,9, Zero); break;
					case 1: PrintUpHalfMatrix(Target,9, One); break;
					case 2: PrintUpHalfMatrix(Target,9, Two); break;
					case 3: PrintUpHalfMatrix(Target,9, Three); break;
					case 4: PrintUpHalfMatrix(Target,9, Four); break;
					case 5: PrintUpHalfMatrix(Target,9, Five); break;
					case 6: PrintUpHalfMatrix(Target,9, Six); break;
					case 7: PrintUpHalfMatrix(Target,9, Seven); break;
					case 8: PrintUpHalfMatrix(Target,9, Eight); break;
					case 9: PrintUpHalfMatrix(Target,9, Nine); break;
				}
				switch(Ones)
				{
					case 0: PrintUpHalfMatrix(Target,15, Zero); break;
					case 1: PrintUpHalfMatrix(Target,15, One); break;
					case 2: PrintUpHalfMatrix(Target,15, Two); break;
					case 3: PrintUpHalfMatrix(Target,15, Three); break;
					case 4: PrintUpHalfMatrix(Target,15, Four); break;
					case 5: PrintUpHalfMatrix(Target,15, Five); break;
					case 6: PrintUpHalfMatrix(Target,15, Six); break;
					case 7: PrintUpHalfMatrix(Target,15, Seven); break;
					case 8: PrintUpHalfMatrix(Target,15, Eight); break;
					case 9: PrintUpHalfMatrix(Target,15, Nine); break;
				}
				PrintUpHalfMatrix(Target,21, Ruble);
			}
			else if(Thousands == 0)	// Отображение сотен, десятков и единиц рублей
			{
				ClearUpHalfMatrix(Target);
				switch(Hundreds)
				{
					case 0: PrintUpHalfMatrix(Target,5, Zero); break;
					case 1: PrintUpHalfMatrix(Target,5, One); break;
					case 2: PrintUpHalfMatrix(Target,5, Two); break;
					case 3: PrintUpHalfMatrix(Target,5, Three); break;
					case 4: PrintUpHalfMatrix(Target,5, Four); break;
					case 5: PrintUpHalfMatrix(Target,5, Five); break;
					case 6: PrintUpHalfMatrix(Target,5, Six); break;
					case 7: PrintUpHalfMatrix(Target,5, Seven); break;
					case 8: PrintUpHalfMatrix(Target,5, Eight); break;
					case 9: PrintUpHalfMatrix(Target,5, Nine); break;
				}
				switch(Tens)
				{
					case 0: PrintUpHalfMatrix(Target,11, Zero); break;
					case 1: PrintUpHalfMatrix(Target,11, One); break;
					case 2: PrintUpHalfMatrix(Target,11, Two); break;
					case 3: PrintUpHalfMatrix(Target,11, Three); break;
					case 4: PrintUpHalfMatrix(Target,11, Four); break;
					case 5: PrintUpHalfMatrix(Target,11, Five); break;
					case 6: PrintUpHalfMatrix(Target,11, Six); break;
					case 7: PrintUpHalfMatrix(Target,11, Seven); break;
					case 8: PrintUpHalfMatrix(Target,11, Eight); break;
					case 9: PrintUpHalfMatrix(Target,11, Nine); break;
				}
				switch(Ones)
				{
					case 0: PrintUpHalfMatrix(Target,17, Zero); break;
					case 1: PrintUpHalfMatrix(Target,17, One); break;
					case 2: PrintUpHalfMatrix(Target,17, Two); break;
					case 3: PrintUpHalfMatrix(Target,17, Three); break;
					case 4: PrintUpHalfMatrix(Target,17, Four); break;
					case 5: PrintUpHalfMatrix(Target,17, Five); break;
					case 6: PrintUpHalfMatrix(Target,17, Six); break;
					case 7: PrintUpHalfMatrix(Target,17, Seven); break;
					case 8: PrintUpHalfMatrix(Target,17, Eight); break;
					case 9: PrintUpHalfMatrix(Target,17, Nine); break;
				}
				PrintUpHalfMatrix(Target,23, Ruble);
			}
			else												// Отображение тысяч, сотен, десятков и единиц рублей
			{
				ClearUpHalfMatrix(Target);
				switch(Thousands)
				{
					case 0: PrintUpHalfMatrix(Target,1, Zero); break;
					case 1: PrintUpHalfMatrix(Target,1, One); break;
					case 2: PrintUpHalfMatrix(Target,1, Two); break;
					case 3: PrintUpHalfMatrix(Target,1, Three); break;
					case 4: PrintUpHalfMatrix(Target,1, Four); break;
					case 5: PrintUpHalfMatrix(Target,1, Five); break;
					case 6: PrintUpHalfMatrix(Target,1, Six); break;
					case 7: PrintUpHalfMatrix(Target,1, Seven); break;
					case 8: PrintUpHalfMatrix(Target,1, Eight); break;
					case 9: PrintUpHalfMatrix(Target,1, Nine); break;
				}
				switch(Hundreds)
				{
					case 0: PrintUpHalfMatrix(Target,7, Zero); break;
					case 1: PrintUpHalfMatrix(Target,7, One); break;
					case 2: PrintUpHalfMatrix(Target,7, Two); break;
					case 3: PrintUpHalfMatrix(Target,7, Three); break;
					case 4: PrintUpHalfMatrix(Target,7, Four); break;
					case 5: PrintUpHalfMatrix(Target,7, Five); break;
					case 6: PrintUpHalfMatrix(Target,7, Six); break;
					case 7: PrintUpHalfMatrix(Target,7, Seven); break;
					case 8: PrintUpHalfMatrix(Target,7, Eight); break;
					case 9: PrintUpHalfMatrix(Target,7, Nine); break;
				}
				switch(Tens)
				{
					case 0: PrintUpHalfMatrix(Target,13, Zero); break;
					case 1: PrintUpHalfMatrix(Target,13, One); break;
					case 2: PrintUpHalfMatrix(Target,13, Two); break;
					case 3: PrintUpHalfMatrix(Target,13, Three); break;
					case 4: PrintUpHalfMatrix(Target,13, Four); break;
					case 5: PrintUpHalfMatrix(Target,13, Five); break;
					case 6: PrintUpHalfMatrix(Target,13, Six); break;
					case 7: PrintUpHalfMatrix(Target,13, Seven); break;
					case 8: PrintUpHalfMatrix(Target,13, Eight); break;
					case 9: PrintUpHalfMatrix(Target,13, Nine); break;
				}
				switch(Ones)
				{
					case 0: PrintUpHalfMatrix(Target,19, Zero); break;
					case 1: PrintUpHalfMatrix(Target,19, One); break;
					case 2: PrintUpHalfMatrix(Target,19, Two); break;
					case 3: PrintUpHalfMatrix(Target,19, Three); break;
					case 4: PrintUpHalfMatrix(Target,19, Four); break;
					case 5: PrintUpHalfMatrix(Target,19, Five); break;
					case 6: PrintUpHalfMatrix(Target,19, Six); break;
					case 7: PrintUpHalfMatrix(Target,19, Seven); break;
					case 8: PrintUpHalfMatrix(Target,19, Eight); break;
					case 9: PrintUpHalfMatrix(Target,19, Nine); break;
				}
				PrintUpHalfMatrix(Target,25, Ruble);
			}
		}
//	}
	//OldMoney = MoneyToDisplay;
}
/**************************************************************************************************************************************************/
/********************************************* Выводит надпись "Выберите режим " ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionSelectMode(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if((*CurrentMode != CashPaymentRecieveMode) && (*CurrentMode != ReadyToWash))
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];
	Source[0]= 0;						// Надпись "Выбери"
	Source[1]= 4061650660;
	Source[2]= 2316570772;
	Source[3]= 2316570772;
	Source[4]= 4086800101;
	Source[5]= 2320781446;
	Source[6]= 2320781444;
	Source[7]= 4086800004;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if((*CurrentMode != CashPaymentRecieveMode) && (*CurrentMode != ReadyToWash))
		{
			return;
		}
		osDelay(100);
	}
	Source[0]= 0;						// Надпись "те реж"
	Source[1]= 1601729481;
	Source[2]= 1145063945;
	Source[3]= 3292547589;
	Source[4]= 1148744643;
	Source[5]= 1145061893;
	Source[6]= 1145061897;
	Source[7]= 1148732361;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if((*CurrentMode != CashPaymentRecieveMode) && (*CurrentMode != ReadyToWash)) 
		{
			return;
		}
		osDelay(100);
	}
	Source[0]= 0;						// Надпись "им"
	Source[1]= 681639936;
	Source[2]= 682819584;
	Source[3]= 1236074496;
	Source[4]= 2325807104;
	Source[5]= 1285619712;
	Source[6]= 681639936;
	Source[7]= 681639936;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if((*CurrentMode != CashPaymentRecieveMode) && (*CurrentMode != ReadyToWash)) 
		{
			return;
		}
		osDelay(100);
	}	
}
/**************************************************************************************************************************************************/
/******************************************************** Выводит надпись "Вода" ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionWater(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != Water) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];
	Source[0]= 0;						// Надпись "Вода"
	Source[1]= 4056122368;
	Source[2]= 2317650432;
	Source[3]= 2317652224;
	Source[4]= 4062482688;
	Source[5]= 2317655808;
	Source[6]= 2318389504;
	Source[7]= 4056436992;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Water) 
		{
			return;
		}
		osDelay(100);
	}
	Source[0]= 0;						// Надпись " "
	Source[1]= 0;
	Source[2]= 0;
	Source[3]= 0;
	Source[4]= 0;
	Source[5]= 0;
	Source[6]= 0;
	Source[7]= 0;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Water) 
		{
			return;
		}
		osDelay(100);
	}
}
/**************************************************************************************************************************************************/
/******************************************************** Выводит надпись "Пена" ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionFoam(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != Foam) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];
	Source[0]= 0;						// Надпись "Пена"
	Source[1]= 4224782336;
	Source[2]= 2316380160;
	Source[3]= 2316387328;
	Source[4]= 2346664960;
	Source[5]= 2316401664;
	Source[6]= 2316387328;
	Source[7]= 2345747456;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Foam) 
		{
			return;
		}
		osDelay(100);
	}
	Source[0]= 0;						// Надпись " "
	Source[1]= 0;
	Source[2]= 0;
	Source[3]= 0;
	Source[4]= 0;
	Source[5]= 0;
	Source[6]= 0;
	Source[7]= 0;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Foam) 
		{
			return;
		}
		osDelay(100);
	}
}
/**************************************************************************************************************************************************/
/******************************************************** Выводит надпись "Воск" ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionWax(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != Wax) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];
	Source[0]= 0;						// Надпись "Воск"
	Source[1]= 4056359936;
	Source[2]= 2317920256;
	Source[3]= 2317889536;
	Source[4]= 4062715904;
	Source[5]= 2317889536;
	Source[6]= 2317920256;
	Source[7]= 4056359936;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Wax) 
		{
			return;
		}
		osDelay(100);
	}
	Source[0]= 0;						// Надпись " "
	Source[1]= 0;
	Source[2]= 0;
	Source[3]= 0;
	Source[4]= 0;
	Source[5]= 0;
	Source[6]= 0;
	Source[7]= 0;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Wax) 
		{
			return;
		}
		osDelay(100);
	}
}
/**************************************************************************************************************************************************/
/******************************************************** Выводит надпись "Осмос" ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionOsmos(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != Osmos) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];					
	Source[0]= 0,							// Надпись "Осмос"
	Source[1]= 1908972656;
	Source[2]=  2318246536;
	Source[3]=  2315952768;
	Source[4]=  2315821696;
	Source[5]=  2315821696;
	Source[6]=  2317918856;
	Source[7]=  1908972656;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Osmos) 
		{
			return;
		}
		osDelay(100);
	}
	Source[0]= 0;						// Надпись " "
	Source[1]= 0;
	Source[2]= 0;
	Source[3]= 0;
	Source[4]= 0;
	Source[5]= 0;
	Source[6]= 0;
	Source[7]= 0;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Osmos) 
		{
			return;
		}
		osDelay(100);
	}
}
/**************************************************************************************************************************************************/
/******************************************************** Выводит надпись "Пылесос" ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionVacuumCliner(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != VacuumCliner) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];	
		// Надпись "Пылес"
	Source[0]= 0;
	Source[1]= 4195606129;
	Source[2]= 2316456074;
	Source[3]= 2316456066;
	Source[4]= 2341625474;
	Source[5]= 2320650370;
	Source[6]= 2320650378;
	Source[7]= 2341756529;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != VacuumCliner) 
		{
			return;
		}
		osDelay(100);
	}
	// Надпись "ос"
	Source[0]= 0;
	Source[1]= 3338665984;
	Source[2]= 679477248;
	Source[3]= 671088640;
	Source[4]= 671088640;
	Source[5]= 671088640;
	Source[6]= 679477248;
	Source[7]= 3338665984;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != VacuumCliner) 
		{
			return;
		}
		osDelay(100);
	}
}
/**************************************************************************************************************************************************/
/******************************************************** Выводит надпись "Воздух" ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionAir(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != Air) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];	
		// Надпись "Воздух"
	Source[0]= 0;
	Source[1]= 3817749652;
	Source[2]= 2488345748;
	Source[3]= 2487297170;
	Source[4]= 3830326385;
	Source[5]= 2487297042;
	Source[6]= 2488368788;
	Source[7]= 3817751140;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Air) 
		{
			return;
		}
		osDelay(100);
	}
	// Надпись "  "
	Source[0]= 0;
	Source[1]= 1073741828;
	Source[2]= 1073741828;
	Source[3]= 2147483650;
	Source[4]= 1;
	Source[5]= 2147483650;
	Source[6]= 1073741828;
	Source[7]= 1073741828;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != Air) 
		{
			return;
		}
		osDelay(100);
	}
}
/**************************************************************************************************************************************************/
/******************************************************** Выводит надпись "Пауза" ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionPause(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != PauseMode) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];	
		// Надпись "Пауза"
	Source[0]= 0;
	Source[1]= 4169740416;
	Source[2]= 2303281472;
	Source[3]= 2317945376;
	Source[4]= 2317816352;
	Source[5]= 2346781664;
	Source[6]= 2317961760;
	Source[7]= 2317759008;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	// Надпись "  "
	Source[0]= 0;
	Source[1]= 0;
	Source[2]= 0;
	Source[3]= 0;
	Source[4]= 0;
	Source[5]= 0;
	Source[6]= 0;
	Source[7]= 0;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
			// Надпись "Для со"
	Source[0]= 0;
	Source[1]= 2029224846;
	Source[2]= 1217692753;
	Source[3]= 1217692689;
	Source[4]= 1217627153;
	Source[5]= 1217496081;
	Source[6]= 4237460561;
	Source[7]= 2232714126;
	//ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	// Надпись "хранен"
	Source[0]= 0;
	Source[1]= 1170350836;
	Source[2]= 1160061572;
	Source[3]= 690528900;
	Source[4]= 298368759;
	Source[5]= 688890500;
	Source[6]= 1158193796;
	Source[7]= 1158193908;
	//ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	// Надпись "ия сд"
	Source[0]= 0;
	Source[1]= 1362639088;
	Source[2]= 1363690641;
	Source[3]= 1397244050;
	Source[4]= 3577233554;
	Source[5]= 1494761619;
	Source[6]= 1361593850;
	Source[7]= 1363687690;
	//ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	// Надпись "ачи при"
	Source[0]= 0;
	Source[1]= 2302951140;
	Source[2]= 1229202068;
	Source[3]= 692855444;
	Source[4]= 794043109;
	Source[5]= 3781436038;
	Source[6]= 558113412;
	Source[7]= 558113412;
	//ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	// Надпись "ложит"
	Source[0]= 0;
	Source[1]= 1329157215;
	Source[2]= 1229280324;
	Source[3]= 3376735428;
	Source[4]= 1229210948;
	Source[5]= 1229252164;
	Source[6]= 1229280324;
	Source[7]= 1362711620;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	// Надпись "е карт"
	Source[0]= 0;
	Source[1]= 2022776058;
	Source[2]= 1084396066;
	Source[3]= 1086607906;
	Source[4]= 2021940257;
	Source[5]= 1086836768;
	Source[6]= 1084510242;
	Source[7]= 2022985761;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}

// Надпись "у клиен"
	Source[0]= 0;
	Source[1]= 556245748;
	Source[2]= 558146180;
	Source[3]= 562341508;
	Source[4]= 3775179511;
	Source[5]= 562344580;
	Source[6]= 558146180;
	Source[7]= 3240665844;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}

// Надпись "та к с"
	Source[0]= 0;
	Source[1]= 1594893340;
	Source[2]= 1143482402;
	Source[3]= 1145319456;
	Source[4]= 3292799008;
	Source[5]= 1148989472;
	Source[6]= 1145317410;
	Source[7]= 1145316380;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}

// Надпись "читыва"
	Source[0]= 0;
	Source[1]= 2489271009;
	Source[2]= 2487501458;
	Source[3]= 2495890068;
	Source[4]= 4114903780;
	Source[5]= 373574295;
	Source[6]= 340019860;
Source[7]= 340030180;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
// Надпись "телю"
	Source[0]= 0;
	Source[1]= 528083328;
	Source[2]= 2218863168;
	Source[3]= 1145121344;
	Source[4]= 1148792384;
	Source[5]= 3292604992;
	Source[6]= 1145121344;
	Source[7]= 1148856704;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	
	
// Надпись "Для з"
	Source[0]= 0;
	Source[1]= 15853318;
	Source[2]= 9513225;
	Source[3]= 9513217;
	Source[4]= 9512710;
	Source[5]= 9511681;
	Source[6]= 33105161;
	Source[7]= 17443078;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	
	
// Надпись "аверш"
	Source[0]= 0;
	Source[1]= 298807883;
	Source[2]= 690506314;
	Source[3]= 1160268362;
	Source[4]= 1171223115;
	Source[5]= 2099790410;
	Source[6]= 1160266314;
	Source[7]= 1171211259;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}		
	
// Надпись "ения бе"
	Source[0]= 0;
	Source[1]= 3510952431;
	Source[2]= 289743112;
	Source[3]= 290267400;
	Source[4]= 3746881999;
	Source[5]= 291791144;
	Source[6]= 289710376;
	Source[7]= 3510968783;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}		

// Надпись "з сдач"
	Source[0]= 0;
	Source[1]= 808575250;
	Source[2]= 1212752530;
	Source[3]= 138486866;
	Source[4]= 809575518;
	Source[5]= 138536898;
	Source[6]= 1212814402;
	Source[7]= 808588354;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}		

// Надпись "и нажм"
	Source[0]= 0;
	Source[1]= 2286175569;
	Source[2]= 2286200155;
	Source[3]= 2554663829;
	Source[4]= 2826768657;
	Source[5]= 3360027537;
	Source[6]= 2286228817;
	Source[7]= 2286228817;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	

// Надпись "иите п"
	Source[0]= 0;
	Source[1]= 1173849468;
	Source[2]= 1145308484;
	Source[3]= 1279524933;
	Source[4]= 1413972037;
	Source[5]= 1682178117;
	Source[6]= 1145307205;
	Source[7]= 1145536581;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	

	// Надпись "аузу"
	Source[0]= 0;
	Source[1]= 1150888448;
	Source[2]= 2762287616;
	Source[3]= 344268800;
	Source[4]= 328785920;
	Source[5]= 4035190784;
	Source[6]= 346365952;
	Source[7]= 320389120;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	
	
	
	// Надпись "  "
	Source[0]= 0;
	Source[1]= 0;
	Source[2]= 0;
	Source[3]= 0;
	Source[4]= 0;
	Source[5]= 0;
	Source[6]= 0;
	Source[7]= 0;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != PauseMode) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
}
/**************************************************************************************************************************************************/
void PauseTimeDisplaying(WorkModeTypeDef* CurrentMode, uint32_t CurentPauseTime, uint32_t* Target)
{
	static uint32_t OldPauseTime = 0;
	if(OldPauseTime != CurentPauseTime)
	{
		uint32_t MinutesTens = 0;
		uint32_t MinutesOnes = 0;
		uint32_t SecondsOnes = 0;
		uint32_t SecondsTens = 0;
		uint32_t Remainder = 0;

		static uint32_t Zero [8] = {1879048192, 2281701376, 2281701376, 2281701376, 2281701376, 2281701376, 2281701376, 1879048192};
		static uint32_t One  [8] = {268435456, 805306368, 1879048192, 2952790016, 805306368, 805306368, 805306368, 805306368};
		static uint32_t Two  [8] = {1879048192, 2281701376, 2281701376, 134217728, 268435456, 536870912, 1073741824, 4160749568};
		static uint32_t Three[8] = {1879048192, 2281701376, 134217728, 805306368, 134217728, 134217728, 2281701376, 1879048192};
		static uint32_t Four [8] = {2281701376, 2281701376, 2281701376, 2281701376, 4160749568, 134217728, 134217728, 134217728};
		static uint32_t Five [8] = {4160749568, 2147483648, 2147483648, 4026531840, 134217728, 134217728, 2281701376, 1879048192};
		static uint32_t Six	 [8] = {1879048192, 2281701376, 2147483648, 4026531840, 2281701376, 2281701376, 2281701376, 1879048192};
		static uint32_t Seven[8] = {4160749568, 2281701376, 134217728, 268435456, 536870912, 1073741824, 1073741824, 1073741824};
		static uint32_t Eight[8] = {1879048192, 2281701376, 2281701376, 1879048192, 2281701376, 2281701376, 2281701376, 1879048192};
		static uint32_t Nine [8] = {1879048192, 2281701376, 2281701376, 2281701376, 2013265920, 134217728, 2281701376, 1879048192};
		static uint32_t Colon[8] = {0,0,2147483648,0,0,2147483648,0,0};
		
		

		MinutesTens = CurentPauseTime / 600;
		Remainder = CurentPauseTime % 600;
		MinutesOnes = Remainder / 60;
		Remainder =	CurentPauseTime % 60;
		SecondsTens = Remainder / 10;
		SecondsOnes = Remainder % 10;
		
		ClearUpHalfMatrix(Target);
		switch(MinutesTens)
		{
			case 0: PrintUpHalfMatrix(Target,3, Zero); break;
			case 1: PrintUpHalfMatrix(Target,3, One); break;
			case 2: PrintUpHalfMatrix(Target,3, Two); break;
			case 3: PrintUpHalfMatrix(Target,3, Three); break;
			case 4: PrintUpHalfMatrix(Target,3, Four); break;
			case 5: PrintUpHalfMatrix(Target,3, Five); break;
			case 6: PrintUpHalfMatrix(Target,3, Six); break;
			case 7: PrintUpHalfMatrix(Target,3, Seven); break;
			case 8: PrintUpHalfMatrix(Target,3, Eight); break;
			case 9: PrintUpHalfMatrix(Target,3, Nine); break;
		}
		switch(MinutesOnes)
		{
			case 0: PrintUpHalfMatrix(Target,9, Zero); break;
			case 1: PrintUpHalfMatrix(Target,9, One); break;
			case 2: PrintUpHalfMatrix(Target,9, Two); break;
			case 3: PrintUpHalfMatrix(Target,9, Three); break;
			case 4: PrintUpHalfMatrix(Target,9, Four); break;
			case 5: PrintUpHalfMatrix(Target,9, Five); break;
			case 6: PrintUpHalfMatrix(Target,9, Six); break;
			case 7: PrintUpHalfMatrix(Target,9, Seven); break;
			case 8: PrintUpHalfMatrix(Target,9, Eight); break;
			case 9: PrintUpHalfMatrix(Target,9, Nine); break;
		}
		
		PrintUpHalfMatrix(Target,15, Colon);
		
		switch(SecondsTens)
		{
			case 0: PrintUpHalfMatrix(Target,17, Zero); break;
			case 1: PrintUpHalfMatrix(Target,17, One); break;
			case 2: PrintUpHalfMatrix(Target,17, Two); break;
			case 3: PrintUpHalfMatrix(Target,17, Three); break;
			case 4: PrintUpHalfMatrix(Target,17, Four); break;
			case 5: PrintUpHalfMatrix(Target,17, Five); break;
			case 6: PrintUpHalfMatrix(Target,17, Six); break;
			case 7: PrintUpHalfMatrix(Target,17, Seven); break;
			case 8: PrintUpHalfMatrix(Target,17, Eight); break;
			case 9: PrintUpHalfMatrix(Target,17, Nine); break;
		}
		
		switch(SecondsOnes)
		{
			case 0: PrintUpHalfMatrix(Target,23, Zero); break;
			case 1: PrintUpHalfMatrix(Target,23, One); break;
			case 2: PrintUpHalfMatrix(Target,23, Two); break;
			case 3: PrintUpHalfMatrix(Target,23, Three); break;
			case 4: PrintUpHalfMatrix(Target,23, Four); break;
			case 5: PrintUpHalfMatrix(Target,23, Five); break;
			case 6: PrintUpHalfMatrix(Target,23, Six); break;
			case 7: PrintUpHalfMatrix(Target,23, Seven); break;
			case 8: PrintUpHalfMatrix(Target,23, Eight); break;
			case 9: PrintUpHalfMatrix(Target,23, Nine); break;
		}
		
		OldPauseTime = CurentPauseTime;
	}
}

/********************************************* Выводит надпись "Выберите сумму и нажмите ОК" ***********************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionSelectTheAmountAndClickOk(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != CashlessPaymentRecieveMode) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];
	Source[0]= 0;						// Надпись "Выбери"
	Source[1]= 4061650660;
	Source[2]= 2316570772;
	Source[3]= 2316570772;
	Source[4]= 4086800101;
	Source[5]= 2320781446;
	Source[6]= 2320781444;
	Source[7]= 4086800004;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != CashlessPaymentRecieveMode) 
		{
			return;
		}
		osDelay(100);
	}
	Source[0]= 0;							// Надпись "те сумм"
	Source[1]= 1601712721;
	Source[2]= 1145064027;
	Source[3]= 3292545621;
	Source[4]= 1148731857;
	Source[5]= 1145061457;
	Source[6]= 1145064017;
Source[7]= 1148727697;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != CashlessPaymentRecieveMode) 
		{
			return;
		}
		osDelay(100);
	}
	Source[0]= 0;							// Надпись "му и на"
	Source[1]= 1159794824;
	Source[2]= 1830883465;
	Source[3]= 1428238474;
	Source[4]= 1155617019;
	Source[5]= 1143050378;
	Source[6]= 1159794826;
	Source[7]= 1153503370;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != CashlessPaymentRecieveMode) 
		{
			return;
		}
		osDelay(100);
	}	
	Source[0]= 0;							// Надпись "жмите"
	Source[1]= 2325908463;
	Source[2]= 1253476488;
	Source[3]= 657102984;
	Source[4]= 3793922191;
	Source[5]= 656590984;
	Source[6]= 715294856;
	Source[7]= 715294863;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != CashlessPaymentRecieveMode) 
		{
			return;
		}
		osDelay(100);
	}	
	Source[0]= 0;						// Надпись "Ok"
	Source[1]= 119799808;
	Source[2]= 145227776;
	Source[3]= 145752064;
	Source[4]= 144703488;
	Source[5]= 145752064;
	Source[6]= 145227776;
	Source[7]= 119799808;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != CashlessPaymentRecieveMode) 
		{
			return;
		}
		osDelay(100);
	}	
}
/**************************************************************************************************************************************************/

/********************************************* Выводит надпись "Выберите сумму и нажмите ОК" ***********************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionAttachABankCard (WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != WaitBankCard) 
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];
	Source[0]= 0;						// Надпись "Подне"
	Source[1]= 4190605689;
	Source[2]= 2317652290;
	Source[3]= 2317652290;
	Source[4]= 2317655930;
	Source[5]= 2317652290;
	Source[6]= 2318389570;
	Source[7]= 2311606649;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != WaitBankCard) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	Source[0]= 0;							// Надпись "сите ба"
	Source[1]= 2440946146;
	Source[2]= 1360068869;
	Source[3]= 319881480;
	Source[4]= 353493448;
	Source[5]= 420544815;
	Source[6]= 1360068904;
	Source[7]= 2433868232;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != WaitBankCard) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	Source[0]= 0;							// Надпись "нковск"
	Source[1]= 580099172;
	Source[2]= 581194389;
	Source[3]= 2730775174;
	Source[4]= 3196345476;
	Source[5]= 2730775174;
	Source[6]= 2728678037;
	Source[7]= 2727582820;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != WaitBankCard) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	
	Source[0]= 0;							// Надпись "ую кар"
	Source[1]= 2771404942;
	Source[2]= 625496393;
	Source[3]= 625500713;
	Source[4]= 499663406;
	Source[5]= 88630248;
	Source[6]= 625496616;
	Source[7]= 2570078760;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != WaitBankCard) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	
	Source[0]= 0;						// Надпись "ту к Pa"
	Source[1]= 2099323330;
	Source[2]= 287392037;
	Source[3]= 287408424;
	Source[4]= 283181519;
	Source[5]= 270631176;
	Source[6]= 287392008;
	Source[7]= 281092360;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != WaitBankCard) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	
	Source[0]= 0;						// Надпись "yPass"
	Source[1]= 607666968;
	Source[2]= 606381220;
	Source[3]= 2753893408;
	Source[4]= 2620986136;
	Source[5]= 2216816772;
	Source[6]= 2753631396;
	Source[7]= 2552304408;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != WaitBankCard) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	
}
/**************************************************************************************************************************************************/

/********************************************* Выводит надпись "Выберите режим или внесите оплату" ************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionSelectModeOrMakePayment(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if(*CurrentMode != ClientCardIsRead)
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];
	Source[0]= 0;						// Надпись "Выбери"
	Source[1]= 4061650660;
	Source[2]= 2316570772;
	Source[3]= 2316570772;
	Source[4]= 4086800101;
	Source[5]= 2320781446;
	Source[6]= 2320781444;
	Source[7]= 4086800004;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != ClientCardIsRead)
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	Source[0]= 0;						// Надпись "те реж"
	Source[1]= 1601729481;
	Source[2]= 1145063945;
	Source[3]= 3292547589;
	Source[4]= 1148744643;
	Source[5]= 1145061893;
	Source[6]= 1145061897;
	Source[7]= 1148732361;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != ClientCardIsRead) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	Source[0]= 0;						// Надпись "им ил"
	Source[1]= 681640487;
	Source[2]= 682820132;
	Source[3]= 1236075108;
	Source[4]= 2325807780;
	Source[5]= 1285620516;
	Source[6]= 681640484;
	Source[7]= 681640488;

	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != ClientCardIsRead) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	
	
	Source[0]= 0;						// Надпись "и внес"
	Source[1]= 2719779790;
	Source[2]= 2719123985;
	Source[3]= 2786232848;
	Source[4]= 2854026192;
	Source[5]= 2987559440;
	Source[6]= 2719123985;
	Source[7]= 2719779790;

	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != ClientCardIsRead) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	Source[0]= 0;						// Надпись "ите оп"
	Source[1]= 1173848991;
	Source[2]= 1145308241;
	Source[3]= 1279525969;
	Source[4]= 1413973073;
	Source[5]= 1682179153;
	Source[6]= 1145308241;
	Source[7]= 1145537425;

	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != ClientCardIsRead) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}
	
	Source[0]= 0;						// Надпись "лату"
	Source[1]= 1011339776;
	Source[2]= 614535680;
	Source[3]= 621875712;
	Source[4]= 636554752;
	Source[5]= 621871616;
	Source[6]= 621875712;
	Source[7]= 1158745088;
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if(*CurrentMode != ClientCardIsRead) 
		{
			return;
		}
		osDelay(RuningStringSpeed);
	}	
}
/**************************************************************************************************************************************************/
/******************************************************** Выводит надпись "Воздух" ******************************************************************/
//uint32_t* Target - указатель на начало массива, из которого отображается изображение на матрице uint32_t* Inscription = (uint32_t *) &MainMatrixArray[8][0];
//WorkModeTypeDef* CurrentMode - режим: ожидание, оплата и т.д.
void InscriptionDop(WorkModeTypeDef* CurrentMode, uint32_t* Target)
{
	if((*CurrentMode != Dop1Mode)&&(*CurrentMode != Dop2Mode)&&(*CurrentMode != Dop3Mode)&&(*CurrentMode != Dop4Mode)&&(*CurrentMode != Dop5Mode)&&(*CurrentMode != Dop6Mode))
	{
		//ClearMatrix((uint32_t *) MainMatrixArray);
		return;
	}
	uint32_t Source[8];	
		// Надпись "Доп"
	Source[0]= 0;
	Source[1]= 954712064;
	Source[2]= 1226063872;
	Source[3]= 1226063872;
	Source[4]= 1226063872;
	Source[5]= 1226063872;
	Source[6]= 4245962752;
	Source[7]= 2229551104;
	ClearUpHalfMatrix(Target);
	for(int8_t j = 31; j >= 0; j--)
	{
		for(uint8_t i = 0; i < 8; i++)
		{
//			*(Target+i) = *(Target+i) << 1;
//			*(Target+i) |= ((Source[i] >> j)& 0x00000001);
			uint32_t TmpVar = htonl(*(Target+i)) << 1;
			TmpVar |= (Source[i] >> j)& 0x00000001;
			*(Target+i) = htonl(TmpVar);
		}
		if((*CurrentMode != Dop1Mode)&&(*CurrentMode != Dop2Mode)&&(*CurrentMode != Dop3Mode)&&(*CurrentMode != Dop4Mode)&&(*CurrentMode != Dop5Mode)&&(*CurrentMode != Dop6Mode))
		{
			return;
		}
		osDelay(100);
	}
}
/**************************************************************************************************************************************************/

//*
