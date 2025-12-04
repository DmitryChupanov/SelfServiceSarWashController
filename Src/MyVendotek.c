#include "MyVendotek.h"
#include "stm32f103xe.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "MyDefines.h"

uint32_t LastKeepaliveIntervalInSeconds = 10;
//uint32_t LastOperationNumber = 0;
MessageNames LastMessageName = NoMessage;
uint32_t lastOperationNumber = 0;
uint32_t lastOperationTimeoutInSeconds = 60;
uint32_t lastEventNumber = 0;
uint64_t lastVRP_Ansver = 0xffffffffffffffff;
uint8_t VRP_AnsverFound = 0;									// Флаг горорящий о том что получе ответ на запрос VRP
uint8_t IdlMessageBlock = 0;
VRPStateTypeDef VRP_State = NoVRP;

/****************************Функция возвращает индекс элемента массива со смещением относительно текущего индекса**************************************/
//uint32_t CurrentElementIndex - индекс текущего элемента массива
//uint32_t BufSize - размер буфера
//uint32_t Offset - смещение
uint32_t RingBufferAddress(uint32_t CurrentElementIndex, uint32_t BufSize, uint32_t Offset)
{
		uint32_t OffsetElementIndex = CurrentElementIndex;
		while (Offset != 0)
		{
				OffsetElementIndex++;
				OffsetElementIndex %= BufSize;
				Offset--;
		}
		return OffsetElementIndex;
}
/*******************************************************************************************************************************************************/


uint16_t crc16_ccitt_table [] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108, 0x9129, 0xA14A,
	0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF, 0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294,
	0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE, 0x2462,
	0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485, 0xA56A, 0xB54B, 0x8528, 0x9509,
	0xE5EE, 0xF5CF, 0xC5AC, 0xD58D, 0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695,
	0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC, 0x48C4,
	0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823, 0xC9CC, 0xD9ED, 0xE98E, 0xF9AF,
	0x8948, 0x9969, 0xA90A, 0xB92B, 0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33,
	0x2A12, 0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, 0x6CA6,
	0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC,
	0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49, 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13,
	0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59,
	0x8F78, 0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F, 0x1080, 0x00A1,
	0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067, 0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D,
	0xD31C, 0xE37F, 0xF35E, 0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, 0x34E2, 0x24C3,
	0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F,
	0xF77E, 0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB, 0x5844, 0x4865, 0x7806,
	0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3, 0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9,
	0x9BD8, 0xABBB, 0xBB9A, 0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3,
	0x3A92, 0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26,
	0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1, 0xEF1F, 0xFF3E, 0xCF5D,
	0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93,
	0x3EB2, 0x0ED1, 0x1EF0,
};
/***************************************************************************************************************************************/

/***************************************************************************************************************************************/
uint16_t Get_crc( uint8_t data[], uint16_t size )
{
	uint16_t i, tmp;
	uint16_t crc = 0xffff;
	for (i = 0; i<size; i++ )
	{
			tmp = (uint16_t)((crc >> 8)^(0x00ff &(uint16_t)data[i]));
			crc = (uint16_t)((crc << 8 ) ^ crc16_ccitt_table[tmp]);
	}
	return crc;
}
/***************************************************************************************************************************************/

/***************************************************************************************************************************************/
uint16_t Get_crc_ring_buf(uint8_t data[], uint32_t index, uint32_t bufSize, uint16_t size)
{
	uint16_t i, tmp;
	uint16_t crc = 0xffff;
	for (i = 0; i < size; i++)
	{
			tmp = (uint16_t)((crc >> 8) ^ (0x00ff & (uint16_t)data[index]));
			crc = (uint16_t)((crc << 8) ^ crc16_ccitt_table[tmp]);
			index++;
			index %= bufSize;
	}
	return crc;
}
/***************************************************************************************************************************************/

/************************************* Преобразует цифру в кодировку, соответствующую ей в ASCII ***************************************/
char ConvertDigitToAscii(uint8_t byDefDigit)
{
		if (byDefDigit < 10)
		{
			return (char)(byDefDigit + 0x30);
		}
		else
		{
			return (char)(byDefDigit - 10 + 0x41);
		}
}
/***************************************************************************************************************************************/
				
//*********************************************** Создает Тег 0х01  "Message name" ************************************************
// char* MesName - например "Idl"
// uint8_t* MessageBuf - Указатель на начало буфера, в который нужно складывать сообщения
// uint32_t* MessageBuf1p - указатель на убегающую метку буфера, в который нужно складывать сообщения
// uint32_t MessageBufSize - размер буфера, в который нужно складывать сообщения
#pragma push
#pragma O0
void CreateTag_MessegeName(char* MesName, uint8_t* MessageBuf, uint32_t* MessageBuf1p, uint32_t MessageBufSize)
{
	MessageBuf[*MessageBuf1p] = 0x01;         	// Тег
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	MessageBuf[*MessageBuf1p] = 0x03;          	// Длина
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	for(uint8_t i = 0; i < 3; i++)
	{
		MessageBuf[*MessageBuf1p] = *(MesName+i); // Сообщения
		*MessageBuf1p += 1;
		*MessageBuf1p %= MessageBufSize;
	}
}
#pragma pop
/***************************************************************************************************************************************/

/************************************************ Создает Тег 0х03  "Operation number" *************************************************/
// uint32_t OpNum - порядковый номер операции
// uint8_t* MessageBuf - Указатель на начало буфера, в который нужно складывать сообщения
// uint32_t* MessageBuf1p - указатель на убегающую метку буфера, в который нужно складывать сообщения
// uint32_t MessageBufSize - размер буфера, в который нужно складывать сообщения
void CreateTag_OperatiionNumber(uint32_t OpNum, uint8_t* MessageBuf, uint32_t* MessageBuf1p, uint32_t MessageBufSize)
{
	MessageBuf[*MessageBuf1p] = 0x03;         	// Тег
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	MessageBuf[*MessageBuf1p] = 0x00;          	// Длина
	uint32_t TagLenghtIndex = *MessageBuf1p;
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
			
	uint32_t TmpVar = OpNum;
	uint32_t Devier = 10000000;
	uint8_t FirstNonZeroFound = 0;
	uint8_t TagLenght = 0;
	while (Devier > 1)
	{
		uint8_t quotient = (uint8_t)(TmpVar / Devier);
		if (quotient > 0)
		{
				FirstNonZeroFound = 1;
		}
		if (FirstNonZeroFound)
		{ 
			MessageBuf[*MessageBuf1p] =	ConvertDigitToAscii(quotient);
			*MessageBuf1p += 1;
			*MessageBuf1p %= MessageBufSize;
			TagLenght++;
		}
		TmpVar %= Devier;
		Devier /= 10;
	}
	MessageBuf[*MessageBuf1p] =	ConvertDigitToAscii(TmpVar);
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	TagLenght += 1;
	MessageBuf[TagLenghtIndex] = TagLenght;
}
/***************************************************************************************************************************************/
/********************************************** Создает Тег 0х04  "Amount in minor currency unit" ************************************************/
// uint AmountInPenny - Сумма в копейках
// uint8_t* MessageBuf - Указатель на начало буфера, в который нужно складывать сообщения
// uint32_t* MessageBuf1p - указатель на убегающую метку буфера, в который нужно складывать сообщения
// uint32_t MessageBufSize - размер буфера, в который нужно складывать сообщения
void CreateTag_AmountInMinorCurrency (uint64_t AmountInPenny, uint8_t* MessageBuf, uint32_t* MessageBuf1p, uint32_t MessageBufSize)
{
	if (AmountInPenny > 1000000)
	{
			//MessageBox.Show("Слишком большая сумма");
			AmountInPenny = 0;
			return;
	}

	uint32_t TagLenght = 0;											// Переменная для счета длины тега
	MessageBuf[*MessageBuf1p] = 0x04;         	// Тег
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	MessageBuf[*MessageBuf1p] = 0x00;          	// Длина
	uint32_t TagLenghtIndex = *MessageBuf1p;
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;

	uint64_t Devier = 100000000000;
	uint8_t FirstNonZeroFound = 0;
	while (Devier > 10)
	{
			uint8_t quotient = (uint8_t)(AmountInPenny / Devier);
			if (quotient > 0)
			{
					FirstNonZeroFound = 1;
			}
			if (FirstNonZeroFound)
			{
				MessageBuf[*MessageBuf1p] = ConvertDigitToAscii(quotient);
				*MessageBuf1p += 1;
				*MessageBuf1p %= MessageBufSize;
				TagLenght++;
			}
			AmountInPenny %= Devier;
			Devier /= 10;
	}
	MessageBuf[*MessageBuf1p] = ConvertDigitToAscii(AmountInPenny / 10);
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	TagLenght++;
	MessageBuf[*MessageBuf1p] = ConvertDigitToAscii(AmountInPenny % 10);
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	TagLenght++;
	MessageBuf[TagLenghtIndex] = TagLenght;

}
/*************************************************************************************************************************************************/

/******************************************************** Создает Тег 0х09  "Product id" *********************************************************/
//int ProductID должен быть от 1 до 9
// uint8_t* MessageBuf - Указатель на начало буфера, в который нужно складывать сообщения
// uint32_t* MessageBuf1p - указатель на убегающую метку буфера, в который нужно складывать сообщения
// uint32_t MessageBufSize - размер буфера, в который нужно складывать сообщения
void CreateTag_ProductID(uint8_t ProductID, uint8_t* MessageBuf, uint32_t* MessageBuf1p, uint32_t MessageBufSize)
{
	if(ProductID > 9) return;
	MessageBuf[*MessageBuf1p] = 0x09;         									// Тег
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	MessageBuf[*MessageBuf1p] = 0x01;          									// Длина
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	
	MessageBuf[*MessageBuf1p] = ConvertDigitToAscii(ProductID);  // ProductID
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	return;
}
/*************************************************************************************************************************************************/
/******************************************************** Создает тег Event name *****************************************************************/
//EventName:
//CSAPP - Cash Sale Approved
//CSDEN - Cash Sale Denied
void CreateTag_EventName(char* EventName, uint8_t* MessageBuf, uint32_t* MessageBuf1p, uint32_t MessageBufSize)
{
	MessageBuf[*MessageBuf1p] = 0x07;         									// Тег
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	MessageBuf[*MessageBuf1p] = 0x05;          									// Длина
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
		
	for(uint8_t i = 0; i < 5; i++)
	{
		MessageBuf[*MessageBuf1p] = *(EventName+i); 							// Сообщение
		*MessageBuf1p += 1;
		*MessageBuf1p %= MessageBufSize;
	}
}
/*************************************************************************************************************************************************/

/******************************************************* Создает тег Event number ****************************************************************/
void CreateTag_EventNumber(uint32_t EventNum, uint8_t* MessageBuf, uint32_t* MessageBuf1p, uint32_t MessageBufSize)
{
	MessageBuf[*MessageBuf1p] = 0x08;         	// Тег
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	MessageBuf[*MessageBuf1p] = 0x00;          	// Длина
	uint32_t TagLenghtIndex = *MessageBuf1p;
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	
	uint32_t TmpVar = EventNum;
	uint32_t Devier = 10000000;
	uint8_t FirstNonZeroFound = 0;
	uint8_t TagLenght = 0;
	while (Devier > 1)
	{
		uint8_t quotient = (uint8_t)(TmpVar / Devier);
		if (quotient > 0)
		{
				FirstNonZeroFound = 1;
		}
		if (FirstNonZeroFound)
		{ 
			MessageBuf[*MessageBuf1p] =	ConvertDigitToAscii(quotient);
			*MessageBuf1p += 1;
			*MessageBuf1p %= MessageBufSize;
			TagLenght++;
		}
		TmpVar %= Devier;
		Devier /= 10;
	}
	MessageBuf[*MessageBuf1p] =	ConvertDigitToAscii(TmpVar);
	*MessageBuf1p += 1;
	*MessageBuf1p %= MessageBufSize;
	TagLenght += 1;
	MessageBuf[TagLenghtIndex] = TagLenght;
}
/*************************************************************************************************************************************************/



//*********************************** Обарачивает сообщение в пакет и ложит его в буфер для отправки в вендотек *************************
void CreatePacket(uint8_t* TagertBuf, uint32_t* TagertBuf1p, uint32_t TagertBufSize, uint8_t* Message, uint16_t MessageLenght)
{
	TagertBuf[*TagertBuf1p] = 0x1F; 							// Starting byte 
	uint32_t StartingSyteIndex = *TagertBuf1p;
	*TagertBuf1p += 1;
	*TagertBuf1p %= TagertBufSize;
	TagertBuf[*TagertBuf1p] = (MessageLenght+2) >> 8; // Длина передаваемого сообщения  Length (big-endian)
	*TagertBuf1p += 1;
	*TagertBuf1p %= TagertBufSize;
	TagertBuf[*TagertBuf1p] = (MessageLenght+2);
	*TagertBuf1p += 1;
	*TagertBuf1p %= TagertBufSize;
	TagertBuf[*TagertBuf1p] = 0x96;								// Protocol discriminator (big-endian). 0x96FB - from VMC
	*TagertBuf1p += 1;
	*TagertBuf1p %= TagertBufSize;
	TagertBuf[*TagertBuf1p] = 0xFB;
	*TagertBuf1p += 1;
	*TagertBuf1p %= TagertBufSize;
	for(uint16_t i = 0; i < MessageLenght; i++)		// Копирование сообщения в пакет
	{
		TagertBuf[*TagertBuf1p] = *(Message+i);
		*TagertBuf1p += 1;
		*TagertBuf1p %= TagertBufSize;
	}
	//uint16_t CRC16 = Get_crc(Message, MessageLenght); // Рассчет CRC16
	uint16_t CRC16 = Get_crc_ring_buf(TagertBuf, StartingSyteIndex, TagertBufSize, MessageLenght+5);
	TagertBuf[*TagertBuf1p] = CRC16 >> 8;
	*TagertBuf1p += 1;
	*TagertBuf1p %= TagertBufSize;
	TagertBuf[*TagertBuf1p] = CRC16;
	*TagertBuf1p += 1;
	*TagertBuf1p %= TagertBufSize;
}
/***************************************************************************************************************************************/

/***************************************************************************************************************************************/
void SendIdlPacket(uint32_t LastOpNum, uint8_t* TagertBuf_, uint32_t* TagertBuf1p_, uint32_t TagertBufSize_)
{
	uint8_t TmpArray[10];
	uint32_t TmpArray1p = 0;
	CreateTag_MessegeName("IDL", TmpArray, &TmpArray1p, 10);
	CreateTag_OperatiionNumber(LastOpNum, TmpArray, &TmpArray1p, 10);
	CreatePacket(TagertBuf_, TagertBuf1p_, TagertBufSize_, TmpArray, TmpArray1p);
}
/***************************************************************************************************************************************/

/***************************************************************************************************************************************/
void SendVRP_Packet(uint8_t ProductID_,uint64_t Peny,uint32_t LastOpNum, uint8_t* TagertBuf_, uint32_t* TagertBuf1p_, uint32_t TagertBufSize_)
{
	uint8_t TmpArray[100];
	uint32_t TmpArray1p = 0;
	CreateTag_MessegeName("VRP", TmpArray, &TmpArray1p, 100);											// Тег MessegeName
	CreateTag_OperatiionNumber(LastOpNum, TmpArray, &TmpArray1p, 100);						// Добавление Тега OperationNumber
	CreateTag_AmountInMinorCurrency (Peny, TmpArray, &TmpArray1p, 100);
	CreateTag_ProductID(ProductID_, TmpArray, &TmpArray1p, 100);
	CreatePacket(TagertBuf_, TagertBuf1p_, TagertBufSize_, TmpArray, TmpArray1p);
}
/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
// Отправляет сообщение FIN
void SendFIN_Packet(uint64_t Peny, uint32_t LastOpNum, uint8_t* TagertBuf_, uint32_t* TagertBuf1p_, uint32_t TagertBufSize_)
{       
	uint8_t TmpArray[100];
	uint32_t TmpArray1p = 0;
	CreateTag_MessegeName("FIN", TmpArray, &TmpArray1p, 100);            	// Тег MessegeName
	CreateTag_OperatiionNumber(LastOpNum, TmpArray, &TmpArray1p, 100);		// Добавление Тега OperationNumber            
	CreateTag_AmountInMinorCurrency (Peny, TmpArray, &TmpArray1p, 100);		// Добавление Тега AmountInMinorCurrency
	CreatePacket(TagertBuf_, TagertBuf1p_, TagertBufSize_, TmpArray, TmpArray1p);
	//VRP_Mess.AddRange(CreateTag_ProductID(ProductID_));                   // Добавление Тега Product ID
}
/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
// Отправляет сообщение ABR
void SendABR_Packet(uint32_t LastOpNum, uint8_t* TagertBuf_, uint32_t* TagertBuf1p_, uint32_t TagertBufSize_)
{
	uint8_t TmpArray[100];
	uint32_t TmpArray1p = 0;
	CreateTag_MessegeName("ABR", TmpArray, &TmpArray1p, 100);            	// Тег MessegeName
	CreateTag_OperatiionNumber(LastOpNum, TmpArray, &TmpArray1p, 100);		// Добавление Тега OperationNumber
	CreatePacket(TagertBuf_, TagertBuf1p_, TagertBufSize_, TmpArray, TmpArray1p);
}
/***************************************************************************************************************************************/
// Создает сообщение CashResived
// После этого сообщения нужно сбросить keepaliveTimer методом keepaliveTimerReset()
#pragma push
#pragma O0
void SendCRS_Packet(int ProductID_, uint64_t Peny, uint8_t* TagertBuf_, uint32_t* TagertBuf1p_, uint32_t TagertBufSize_)
{
	uint8_t TmpArray[100];
	uint32_t TmpArray1p = 0;
	CreateTag_MessegeName("IDL", TmpArray, &TmpArray1p, 100);								// Тег MessegeName
	CreateTag_EventName("CSAPP", TmpArray, &TmpArray1p, 100);								// Добавление Тега EventName
	CreateTag_EventNumber(++lastEventNumber, TmpArray, &TmpArray1p, 100);		// Добавление Тега EventNumber
	CreateTag_AmountInMinorCurrency (Peny, TmpArray, &TmpArray1p, 100);			// Добавление Тега AmountInMinorCurrency               
	CreateTag_ProductID(ProductID_, TmpArray, &TmpArray1p, 100);						// Добавление Тега Product ID
	CreatePacket(TagertBuf_, TagertBuf1p_, TagertBufSize_, TmpArray, TmpArray1p);
}
#pragma pop
/***********функция берет число от 0 до F в ASCII кодировке и преобразовывать в обычный hex.********************************************/
static uint8_t HexAsciiToHalfbyteHex(uint8_t _ascii)
{
 if((_ascii >= '0') && (_ascii <= '9')) return(_ascii - '0') ; 
 if((_ascii >= 'a') && (_ascii <= 'f')) return(_ascii - 0x57) ; 
 if((_ascii >= 'A') && (_ascii <= 'F')) return(_ascii - 0x37) ; 
 return(0xFF);
}
/***************************************************************************************************************************************************************/

/***************************************************************************************************************************************/
/****************************  Функция берет данные из массива, где они записаны в АСКИ в десятичном виде и преобразует в 32 разрядный Hex  ********************/
// byte [] DecASCII - массив из которого нужно брать данные
// uint Index - индекс в массиве начиная с которого нужно брать данные
// byte Len - количество байт данных, которые нужно преобразовать
static uint32_t DecAsciiToHex32(uint8_t* DecASCII, uint32_t DecASCIIIndex, uint32_t DecASCIISize, uint8_t Len)
{
	uint32_t Hex32 = 0;															//Переменная для хранения преобразованного шестнадцатеричного числа
	int8_t DatLenCounter =0;												//Счетчик количества символов десятичного числа в ASCII кодировке
	uint8_t Dec[10];																//Массив, куда складываются десятичные числа преобразованные из ASCII в Hex
	for(uint8_t i = 0; i < Len; i++)						//Если текущий символ не равен 0, то конец строки не настал
	{
		Dec[DatLenCounter] = HexAsciiToHalfbyteHex(DecASCII[DecASCIIIndex++]);	//Преобразуем ASCII символ в Hex и сохраняем в массиве Dec
		DecASCIIIndex %= DecASCIISize;
		DatLenCounter++;
		if (DatLenCounter >=10) break;								// Если счетчик DecASCII символов превысил 10, то выскакиваем из цикла (10-Й СИМВОЛ - ЭТО 0 В КОНЦЕ СТРОКИ )
	}
	DatLenCounter--;																//Откатываемся на 1 символ так как 0 в конце строки нам не нужен
	uint32_t multiplier = 1U;												//Множитель, соответствующий текущему разряду десятичного числа 

	while (DatLenCounter >= 0)
	{
		Hex32 += Dec[DatLenCounter] * multiplier;
		DatLenCounter--;
		if (DatLenCounter < 0) break;									//Если счетчик разрядов меньше 0, то выскакиваем из цикла, чтобы не переполнить  multiplier за 32 разряда
		multiplier *=10U;															//увеличиваем множитель в 10, так как у следующего символа вес больше в 10 раз
	}
	return Hex32;
}
/***************************************************************************************************************************************************************/
/****************************  Функция берет данные из массива, где они записаны в АСКИ в десятичном виде и преобразует в 32 разрядный Hex  ********************/
// byte [] DecASCII - массив из которого нужно брать данные
// uint Index - индекс в массиве начиная с которого нужно брать данные
// byte Len - количество байт данных, которые нужно преобразовать
static uint64_t DecAsciiToHex64(uint8_t* DecASCII, uint32_t DecASCIIIndex, uint32_t DecASCIISize, uint8_t Len)
{
	uint32_t Hex32 = 0;															//Переменная для хранения преобразованного шестнадцатеричного числа
	int8_t DatLenCounter =0;												//Счетчик количества символов десятичного числа в ASCII кодировке
	uint8_t Dec[18];																//Массив, куда складываются десятичные числа преобразованные из ASCII в Hex
	for(uint8_t i = 0; i < Len; i++)						//Если текущий символ не равен 0, то конец строки не настал
	{
		Dec[DatLenCounter] = HexAsciiToHalfbyteHex(DecASCII[DecASCIIIndex++]);	//Преобразуем ASCII символ в Hex и сохраняем в массиве Dec
		DecASCIIIndex %= DecASCIISize;
		DatLenCounter++;
		if (DatLenCounter >17) break;								// Если счетчик DecASCII символов превысил 10, то выскакиваем из цикла (10-Й СИМВОЛ - ЭТО 0 В КОНЦЕ СТРОКИ )
	}
	DatLenCounter--;																//Откатываемся на 1 символ так как 0 в конце строки нам не нужен
	uint32_t multiplier = 1U;												//Множитель, соответствующий текущему разряду десятичного числа 

	while (DatLenCounter >= 0)
	{
		Hex32 += Dec[DatLenCounter] * multiplier;
		DatLenCounter--;
		if (DatLenCounter < 0) break;									//Если счетчик разрядов меньше 0, то выскакиваем из цикла, чтобы не переполнить  multiplier за 32 разряда
		multiplier *=10U;															//увеличиваем множитель в 10, так как у следующего символа вес больше в 10 раз
	}
	return Hex32;
}
/***************************************************************************************************************************************************************/

/********************************************************Сравнивает 2 массива***************************************************************************/
// uint8_t* RxBuf - указатель на начало массива в котором нужно искать строку
// uint32_t Buf2p - индекс откуда нужно начинать сравнение
// uint32_t BufSize - размер буфера
// char* StrForSerch - строка с которой нужно сравнивать
uint8_t ArrCmp(uint8_t* Buf, uint32_t Buf2p, uint32_t BufSize, char* StrForSerch)
{
	uint8_t StrLen = 0;																		//Создаем переменную, где будет лежать длина строки
	while ( StrForSerch[StrLen] != 0 )									//Ищем, пока не встретим в строке 0.
	{
		if (StrForSerch[StrLen] == Buf [Buf2p])		//Если символ в буфере совпал с символом в искомой строке
		{
			StrLen++;																//, то инкрементируем StrLen и указатель на эллемент буфера
			Buf2p++;
			Buf2p %= BufSize;												// не забывая закольцеваться
		}																					// и продолжаем сравнивать следующие компоненты
		else
		{
			return 0;																					// А если хотя бы один символ не совпал, то выходим из функции и возвращаеи 0
		}
	}
	return StrLen;																	//И возвращаем длину строки
}
/******************************************************* Функция безналичной оплаты ********************************************************************/
//#pragma push
//#pragma O0
CashlessPaymentStateTypeDef CashlessPayment(uint8_t ProdID, uint32_t DesPayInPeny)
{
	static uint32_t OperationTimeout;
	static uint32_t WaitAnswerTimerCounter = 0;
	CashlessPaymentStateTypeDef CashlessPaymentState_ = CP_NoPayment;
	if(ProdID >9) return CP_Error; 																													// В случае неверного ProductID
	if(VRP_State == VRP_Request)											// Отправка VRP
	{
		IdlMessageBlock = 1;                                      										// Блокировка отправки Idl сообщений
		LastMessageName = NoMessage;                     															// Обнуление последнего пришедшего от Vendotek сообщения
		lastVRP_Ansver = 0xffffffffffffffff;                           								// Обнуление последней суммы, пришедшей с пакетом VRP
		VRP_AnsverFound = 0;     
		SendVRP_Packet(ProdID,DesPayInPeny,++lastOperationNumber, VendotekTxBuf, &VendotekTxBuf1p, VendotekTxBufSize); // Отправка VRP пакета
		OperationTimeout = lastOperationTimeoutInSeconds;
		VRP_State = VRP_WaitAnswer;
		CashlessPaymentState_ = CP_InProcess;
	}
	else if(VRP_State == VRP_WaitAnswer)							// Ожидание ответа на VRP
	{
		WaitAnswerTimerCounter++;																										// Насчитывает 1 секунду
		if(WaitAnswerTimerCounter == 1000)
		{
			WaitAnswerTimerCounter = 0;
			OperationTimeout--;																												// Уменьшает время ожидания ответа на запрос VRP на 1 секунду
		}
		if(OperationTimeout > 1)                                                    // Ожидание ответа на запрос VRP втечении operation timeout.
		{
			if ((LastMessageName == VRP)&&(VRP_AnsverFound == 1))            					// Если ответ на запрос VRP пришел
			{
				VRP_State = VRP_FinishStep;																							// переходим к финишному шагу
			}
		}
		else																																				// Если время ожидания ответа истекло
		{
			VRP_State = VRP_FinishStep;																								// переходим к финишному шагу
		}
		CashlessPaymentState_ = CP_InProcess;
	}
	else if(VRP_State == VRP_FinishStep)							// Создание чека или отмена операции
	{
		if ((LastMessageName != VRP)||(lastVRP_Ansver == 0))
		{
			SendABR_Packet(lastOperationNumber, VendotekTxBuf, &VendotekTxBuf1p, VendotekTxBufSize); // Отправка ABR пакета
//			MessageBox.Show("Превышен интервал ожидания ответа на VRP.");
			IdlMessageBlock = 0;                                            					// Разблокировка отправки Idl сообщений
			VRP_State = NoVRP;
			CashlessPaymentState_ = CP_Error;
		}
		if((LastMessageName == VRP)&&(lastVRP_Ansver != 0)) 																		// В случае успешной оплаты, создаем чек
		{
			SendFIN_Packet(DesPayInPeny, lastOperationNumber, VendotekTxBuf, &VendotekTxBuf1p, VendotekTxBufSize);  // Отправка FIN пакета
			IdlMessageBlock = 0;                                            											// Разблокировка отправки Idl сообщений
			VRP_State = NoVRP;
			CashlessPaymentState_ = CP_Ok;
		}
	}
	return CashlessPaymentState_;
}
//#pragma pop
/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
void GetCheck(uint8_t ProdID, uint32_t DesPayInPeny, uint32_t * KeepaliveTimer)
{
	IdlMessageBlock = 1;
	// После этого сообщения нужно сбросить keepaliveTimer методом keepaliveTimerReset()
	SendCRS_Packet(ProdID, DesPayInPeny, VendotekTxBuf, &VendotekTxBuf1p, VendotekTxBufSize);
	*KeepaliveTimer = 0;
	IdlMessageBlock = 0;
}
/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
#pragma push
#pragma O0
void VendotekParsing(void)
{
	#define StartingByte 0x1F
	static uint8_t DelayParsingTimer = 0;
	if (VendotekRxBuf1p != VendotekRxBuf2p)
	{
		DelayParsingTimer++;
		if(DelayParsingTimer < 40)	// Ожидание пока будут получены все байты пакета
		{
			return;
		}
		DelayParsingTimer = 0;
		/*-------------------------------------------------------Быстрый пропуск мусора------------------------------------------------------------------------------*/
		for (uint8_t i = 0; i < 100; i++)
		{
			if (VendotekRxBuf[VendotekRxBuf2p] == StartingByte)            // Поиск стартового байта
			{
					break;                                             // Если значение в буфере = значению адресса устройства (1), то выход из цикла и начало парсинга
			}
			else                                                   // Иначе
			{
					VendotekRxBuf2p++;                                     // Инкрементируем догоняющий индекс
					VendotekRxBuf2p %= VendotekRxBufSize;                      // Закольцовываемся
			}
			if (VendotekRxBuf2p == VendotekRxBuf1p)  return;             // Если буфер пуст - выходим из цикла
		}
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

		/*---------------------------------------------------------- Получение длины пакета -------------------------------------------------------------------------*/
		uint16_t dataLenght = (uint16_t)(VendotekRxBuf[RingBufferAddress(VendotekRxBuf2p, VendotekRxBufSize, 1)] << 8);
		VendotekRxBuf2p %= VendotekRxBufSize;
		dataLenght |= VendotekRxBuf[RingBufferAddress(VendotekRxBuf2p, VendotekRxBufSize, 2)];
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*----------------------------------------------------------- Проверка CRC ----------------------------------------------------------------------------------*/
		uint16_t crcCalculated = Get_crc_ring_buf(VendotekRxBuf, VendotekRxBuf2p, VendotekRxBufSize, (uint16_t)(dataLenght+3));
		uint16_t crcResived =(uint16_t)((VendotekRxBuf[RingBufferAddress(VendotekRxBuf2p, VendotekRxBufSize, (uint16_t)(dataLenght + 3))])<<8);
		crcResived |= (uint16_t)((VendotekRxBuf[RingBufferAddress(VendotekRxBuf2p, VendotekRxBufSize, (uint16_t)(dataLenght + 4))]));
		if (crcCalculated != crcResived)
		{
				VendotekRxBuf2p++;
				VendotekRxBuf2p %= VendotekRxBufSize;
				return;
		}
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*---------------------------------------------------------- Пропуск заголовка пакета -----------------------------------------------------------------------*/
		for (int i = 0; i < 5; i++)
		{
				VendotekRxBuf2p++;
				VendotekRxBuf2p %= VendotekRxBufSize;
		}
		dataLenght -= 2; // Уменьшение длины оставшихся байтов данных пакета на величину дескриминатора пакета 
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
		 for(int i = 0; i < 100; i++)
		 { 
				/*---------------------------------------------------------- Поиск тега 0х01 Message name -------------------------------------------------------------------*/
				if (ArrCmp(VendotekRxBuf, VendotekRxBuf2p, VendotekRxBufSize, "\x01\x03"))
				{
						VendotekRxBuf2p++;                  // Пропуск номера тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						VendotekRxBuf2p++;                  // Пропуск длины тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						if (ArrCmp(VendotekRxBuf, VendotekRxBuf2p, VendotekRxBufSize, "IDL"))
						{
								LastMessageName = IDL;
						}
						else if (ArrCmp(VendotekRxBuf, VendotekRxBuf2p, VendotekRxBufSize, "VRP"))
						{
								LastMessageName = VRP;
						}
						else if (ArrCmp(VendotekRxBuf, VendotekRxBuf2p, VendotekRxBufSize, "CDP"))
						{
								LastMessageName = CDP;
						}
						else if (ArrCmp(VendotekRxBuf, VendotekRxBuf2p, VendotekRxBufSize, "ABR"))
						{
								LastMessageName = ABR;
						}

						VendotekRxBuf2p++;                  // Пропуск содержимого тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						VendotekRxBuf2p++;
						VendotekRxBuf2p %= VendotekRxBufSize;
						VendotekRxBuf2p++;
						VendotekRxBuf2p %= VendotekRxBufSize;
						dataLenght -= 5;                    //  Уменьшение длины оставшихся байтов данных пакета на размер тега
				}
				/*---------------------------------------------------------- Поиск тега 0х03 Operation number -------------------------------------------------------------------*/
				if (VendotekRxBuf[VendotekRxBuf2p] == 0x03)
				{
						VendotekRxBuf2p++;                              // Пропуск номера тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						uint8_t TagLenght = VendotekRxBuf[VendotekRxBuf2p++];  // Длина данных тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						lastOperationNumber = DecAsciiToHex32(VendotekRxBuf, (int)VendotekRxBuf2p, VendotekRxBufSize, TagLenght);
						dataLenght -= (uint16_t)2;                    // Уменьшение длины пакета на номер тега, байт содержащий его длину
						while (TagLenght != 0)
						{
								VendotekRxBuf2p++;                          // Пропуск байтов номера операции
								VendotekRxBuf2p %= VendotekRxBufSize;
								TagLenght--;
								dataLenght--;
						}
				}
				/*---------------------------------------------------------- Поиск тега 0х06 Operation timeout in seconds -------------------------------------------------------*/
				if ((VendotekRxBuf[VendotekRxBuf2p]) == 0x06)
				{
						VendotekRxBuf2p++;                              // Пропуск номера тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						uint8_t TagLenght = VendotekRxBuf[VendotekRxBuf2p++];  // Длина данных тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						lastOperationTimeoutInSeconds = DecAsciiToHex32(VendotekRxBuf, (int)VendotekRxBuf2p, VendotekRxBufSize, TagLenght);
						dataLenght -= (uint16_t)2;                    // Уменьшение длины пакета на номер тега, байт содержащий его длину
						while (TagLenght != 0)
						{
								VendotekRxBuf2p++;                          // Пропуск байтов данных тега
								VendotekRxBuf2p %= VendotekRxBufSize;
								TagLenght--;
								dataLenght--;
						}
				}
				/*---------------------------------------------------------- Поиск тега 0х08 Event number ------------------------------------------------------------------------*/
				if (VendotekRxBuf[VendotekRxBuf2p] == 0x08)
				{
						VendotekRxBuf2p++;                              // Пропуск номера тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						uint8_t TagLenght = VendotekRxBuf[VendotekRxBuf2p++];  // Длина данных тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						lastEventNumber = DecAsciiToHex32(VendotekRxBuf, VendotekRxBuf2p, VendotekRxBufSize, TagLenght);
						dataLenght -= (uint16_t)2;                    // Уменьшение длины пакета на номер тега, байт содержащий его длину
						while (TagLenght != 0)
						{
								VendotekRxBuf2p++;                          // Пропуск байтов данных тега
								VendotekRxBuf2p %= VendotekRxBufSize;
								TagLenght--;
								dataLenght--;
						}
				}
				/*-------------------------------------------------- Поиск тега 0х04 Amount in minor currency unit ---------------------------------------------------------------*/
				if (VendotekRxBuf[VendotekRxBuf2p] == 0x04)
				{
						VendotekRxBuf2p++;                              // Пропуск номера тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						uint8_t TagLenght = VendotekRxBuf[VendotekRxBuf2p++];  // Длина данных тега
						VendotekRxBuf2p %= VendotekRxBufSize;
						lastVRP_Ansver = DecAsciiToHex64(VendotekRxBuf, VendotekRxBuf2p, VendotekRxBufSize, TagLenght);
						if (lastVRP_Ansver == 0)
						{
								if (LastMessageName == VRP)
								{
										//MessageBox.Show("VRP response is zero, the financial operation is not approved.");
										//MessageBox.Show("Предыдущая финансовая операция отменена/отклонена");
								}
								else if (LastMessageName == CDP)
								{
										//MessageBox.Show("CDP response is zero, VMC must return all money to a client.");
								}
								
						}
						else
						{
								VRP_AnsverFound = 1;
						}

						dataLenght -= 2;                    // Уменьшение длины пакета на номер тега и байт содержащий его длину
						while (TagLenght != 0)
						{
								VendotekRxBuf2p++;                          // Пропуск байтов данных тега
								VendotekRxBuf2p %= VendotekRxBufSize;
								TagLenght--;
								dataLenght--;
						}
				}


				if (dataLenght == 0)                // Выход из парсинга, если пакет закончился
				{
						VendotekRxBuf2p++;                  // Пропуск CRC
						VendotekRxBuf2p %= VendotekRxBufSize;
						VendotekRxBuf2p++;
						VendotekRxBuf2p %= VendotekRxBufSize;
						return;                         // Завершение парсинга
				}

		}
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------------*/
	}

}
#pragma pop
/***************************************************************************************************************************************/
/***************************************************************************************************************************************/















//*
