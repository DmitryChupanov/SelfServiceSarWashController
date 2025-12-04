/**
  ******************************************************************************
  * @file    MyUSART_FCs.h
  * @brief   This file contains headers of my functions.
  ******************************************************************************
*/

 /* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __MYUSART_FCS_H
#define __MYUSART_FCS_H

#include "stdint.h"
//#define MyAFIOBase 0x40010000
//#define MyAFIO ((AFIO_TypeDef *)MyAFIO_BASE)

typedef enum 
{
	USART_OK				= 0x00U,
	USART_Bisy			= 0x01U,
	USART_NotInit		= 0x02U,
}USART_DMA_TransmitStatus;





void USART5_Transmit_Init (void);
void UART4_DMA_Receive_Init (uint8_t* MemRxDataP, uint32_t BufSize); // Здесь комп или модем
void UART4_DMA_Transmit_Init (void);
USART_DMA_TransmitStatus UART4_DMA_Transmit (uint8_t* UART4_TxDataP, uint16_t DatLen);
void PC_RS485Send(void);
void PrnToPc(char* Str);

void USART2_DMA_Transmit_Init (void);		//Здесь Vendotek
USART_DMA_TransmitStatus USART2_DMA_Transmit (uint8_t* USART2_TxDataP, uint16_t DatLen); //Отправка даныых из контроллера через UART2,DMA1 канал 7
void USART2_DMA_Receive_Init (uint8_t* MemRxDataP, uint32_t BufSize);	// Функция начальной инициализации DMA1 для передачи данных из памяти в регистр данных USART2

void USART1_DMA_Receive_Init (uint8_t* MemRxDataP, uint32_t BufSize); // Здесь VFD
void USART1_DMA_Transmit_Init (void);
USART_DMA_TransmitStatus USART1_DMA_Transmit (uint8_t* USART1_TxDataP, uint16_t DatLen);






#endif /* __MYUSART_FCS_H */
