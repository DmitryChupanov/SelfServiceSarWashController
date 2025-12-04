/**
  ******************************************************************************
  * @file    MyCommon_FCs.h
  * @brief   This file contains headers of my functions.
  ******************************************************************************
*/

 /* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __MYCOMMON_FCS_H
#define __MYCOMMON_FCS_H

#include "stdint.h"
	 



uint8_t HalfbyteToHexascii(uint8_t halfbyte);									//Функция преобразует младшую половину байта в число которое обозначает эту цыфру в кодировке ASCII
void Hex32ToDecASCII (uint32_t HexData, uint8_t *DecASCII);		//Функция преобразует число из 32-х разрядного Hex в десятичный ASCII
uint8_t HexAsciiToHalfbyteHex(uint8_t _ascii);								//функция берет число от 0 до F в ASCII кодировке и преобразовывать в обычный hex.
uint32_t DecAsciiToHex32 (uint8_t *DecASCII);									//Функция берет данные из массива, где они записаны в АСКИ в десятичном виде и преобразует в 32 разрядный Hex
void CRC8n (uint8_t in, uint8_t *crc);												//CRC8n Функция от Нафиса
unsigned short Crc16Mod (unsigned char *pcBlock, unsigned short len, unsigned short APolynome ); //CRC16 Функция от Нафиса
uint32_t Crc16Buf (uint8_t *Buf, uint32_t Buf2p, uint32_t BufSize, uint16_t len, uint16_t APolynome, uint16_t *crc); //CRC16 Функция для расчета CRC16 в кольцесом буфере
uint32_t DecAsciiToHex32_ (char *simv, uint8_t *Buf, uint32_t Buf1p, uint32_t *Buf2p, uint32_t SizeOfBuf);
uint8_t DataIntoBufIsExhaused (uint32_t Buf1p, uint32_t *Buf2p); //Функция возвращает 1 если данные в буфере GPRxBuf закончились и 0 если необработанные данные еще есть
void NopDelay (uint32_t NopNumber);														//Задержка через NOP
float Kalman (float Kstab, float *Xopt, float *z);						//Фильтр Калмана
float ABSfloat (float a);																			//Возвращает модуль числа
uint32_t TwoStrCmp (char *Str1, char *Str2);									//Сравнение двух строк
uint32_t StrCmpV3 (char *StrForSerch, uint8_t *Buf, uint32_t *Buf2p, uint32_t Buf1p, uint32_t BufSize); //Функция ищет строку в буфере и возвращает 0 если в буфере такой строки не нашлось или длину строки, если строка нашлась
uint8_t DecAsciiToHex8 (uint8_t ASCII_H, uint8_t ASCII_L);		//Преобразует шестнадцатеричное число, записанное в ASCII в однобайтовый Hex
//void PrnHAL_Status(char *StrP, HAL_StatusTypeDef Status);			//Распечатывает статус выполнения функции HAL в отладочный порт
uint32_t GetFilledBufSpace(uint32_t *Buf1p, uint32_t *Buf2p, uint32_t BufSize); //Выдает величину заполненного объема буфера
void CreateHeader(uint8_t DeviceType, uint16_t DataFildLenght, uint8_t* Buf, uint32_t* Buf1p, uint32_t BufSize); // Функция создает заголовок пакета 5517 и сохраняет его в буфер
uint32_t CreateCAN_Tag(uint8_t* Buf, uint32_t* Buf1p, uint32_t BufSize); // Создает теги с CАN параметрами
uint32_t CreateTimeTag (uint8_t* Buf, uint32_t* Buf1p, uint32_t BufSize); //Функция создает тег времени (Тег 0Fh)
uint32_t htonl(uint32_t n); 	// Меняет порядок байт в 32 разрядномчисле

#endif /* __MYCOMMON_FCS_H */
