/**
  ******************************************************************************
  * @file    MyVendotek.h
  * @brief   This file contains headers of my functions.
  ******************************************************************************
*/

 /* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __MYVENDOTEK_H
#define __MYVENDOTEK_H

#include "stdint.h"

extern uint32_t lastOperationNumber;
extern uint32_t LastKeepaliveIntervalInSeconds;
extern uint32_t lastOperationTimeoutInSeconds;
extern uint32_t lastEventNumber;
extern uint64_t lastVRP_Ansver;
extern uint8_t VRP_AnsverFound;
extern uint8_t IdlMessageBlock;

typedef enum
{
		IDL,    // IDLE state handshake
		DIS,    // DISABLED state handshake
		STA,    // Start of session, if required from POS
		VRP,    // Vend request positive
		FIN,    // Finalization of operation
		ABR,    // Abort of operation
		CDP,    // Cash deposit
		MFR,    // MIFARE card detected
		CON,    // Connect message
		DAT,    // Data message
		DSC,    // Disconnect message
		NoMessage, // После запуска ни одного сообщения ещ не приходило
}MessageNames;
extern MessageNames LastMessageName;


//void CreateTag_MessegeName(char* MesName, uint8_t* MessageBuf, uint32_t* MessageBuf1p, uint32_t MessageBufSize);
//void CreateTag_OperatiionNumber(uint32_t OpNum, uint8_t* MessageBuf, uint32_t* MessageBuf1p, uint32_t MessageBufSize);
void SendIdlPacket(uint32_t LastOpNum, uint8_t* TagertBuf_, uint32_t* TagertBuf1p_, uint32_t TagertBufSize_);
void SendVRP_Packet(uint8_t ProductID_,uint64_t Peny,uint32_t LastOpNum, uint8_t* TagertBuf_, uint32_t* TagertBuf1p_, uint32_t TagertBufSize_);
void VendotekParsing(void);

typedef enum{
	NoVRP,
	VRP_Request,
	VRP_WaitAnswer,
	VRP_FinishStep,
}VRPStateTypeDef;

extern VRPStateTypeDef VRP_State;

typedef enum{
	CP_NoPayment,
	CP_InProcess,
	CP_Ok,
	CP_Error,
}CashlessPaymentStateTypeDef;


CashlessPaymentStateTypeDef CashlessPayment(uint8_t ProdID, uint32_t DesPayInPeny); // Процедура безналичной оплаты 
void GetCheck(uint8_t ProdID, uint32_t DesPayInPeny, uint32_t * KeepaliveTimer);







#endif /* __MYVENDOTEK_H */
