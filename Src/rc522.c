// Mifare RC522 RFID Card reader 13.56 MHz

//#include "stm32f1xx_hal.h"
#include "rc522.h"
#include "MyUSART_FCs.h"


extern SPI_HandleTypeDef hspi2;

// RC522
extern uint8_t MFRC522_Check(uint8_t* id);
extern uint8_t MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID);
extern void MFRC522_WriteRegister(uint8_t addr, uint8_t val);
extern uint8_t MFRC522_ReadRegister(uint8_t addr);
extern void MFRC522_SetBitMask(uint8_t reg, uint8_t mask);
extern void MFRC522_ClearBitMask(uint8_t reg, uint8_t mask);
extern uint8_t MFRC522_Request(uint8_t reqMode, uint8_t* TagType);
extern uint8_t MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen);
extern uint8_t MFRC522_Anticoll(uint8_t* serNum);
extern void MFRC522_CalulateCRC(uint8_t* pIndata, uint8_t len, uint8_t* pOutData);
extern uint8_t MFRC522_SelectTag(uint8_t* serNum);
extern uint8_t MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum);
extern uint8_t MFRC522_Read(uint8_t blockAddr, uint8_t* recvData);
extern uint8_t MFRC522_Write(uint8_t blockAddr, uint8_t* writeData);
extern void MFRC522_Init(void);
extern void MFRC522_Reset(void);
extern void MFRC522_AntennaOn(void);
extern void MFRC522_AntennaOff(void);
extern void MFRC522_Halt(void);

uint8_t SPI1SendByte(uint8_t data) {
	unsigned char writeCommand[1];
	unsigned char readValue[1];
	writeCommand[0] = data;
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&writeCommand, (uint8_t*)&readValue, 1, 30);
	return readValue[0];
}

void SPI1_WriteReg(uint8_t address, uint8_t value) {
	cs_reset();
	SPI1SendByte(address);
	SPI1SendByte(value);
	cs_set();
}

uint8_t SPI1_ReadReg(uint8_t address) {
	uint8_t	val;

	cs_reset();
	SPI1SendByte(address);
	val = SPI1SendByte(0x00);
	cs_set();
	return val;
}

void MFRC522_WriteRegister(uint8_t addr, uint8_t val) {
	addr = (addr << 1) & 0x7E;															// Address format: 0XXXXXX0
  SPI1_WriteReg(addr, val);
}

uint8_t MFRC522_ReadRegister(uint8_t addr) {
	uint8_t val;

	addr = ((addr << 1) & 0x7E) | 0x80;
	val = SPI1_ReadReg(addr);
	return val;	
}

uint8_t MFRC522_Check(uint8_t* id) {
	uint8_t status;
	status = MFRC522_Request(PICC_REQIDL, id);							// Find cards, return card type
	if (status == MI_OK) status = MFRC522_Anticoll(id);			// Card detected. Anti-collision, return card serial number 4 bytes
	MFRC522_Halt();																					// Command card into hibernation 
	return status;
}

uint8_t MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID[i] != CompareID[i]) return MI_ERR;
	}
	return MI_OK;
}

void MFRC522_SetBitMask(uint8_t reg, uint8_t mask) {
	MFRC522_WriteRegister(reg, MFRC522_ReadRegister(reg) | mask);
}

void MFRC522_ClearBitMask(uint8_t reg, uint8_t mask){
	MFRC522_WriteRegister(reg, MFRC522_ReadRegister(reg) & (~mask));
}

uint8_t MFRC522_Request(uint8_t reqMode, uint8_t* TagType) {
	uint8_t status;  
	uint16_t backBits;																			// The received data bits

	MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x07);		// TxLastBists = BitFramingReg[2..0]
	TagType[0] = reqMode;
	status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);
	if ((status != MI_OK) || (backBits != 0x10)) status = MI_ERR;
	return status;
}

uint8_t MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen) {
	uint8_t status = MI_ERR;
	uint8_t irqEn = 0x00;
	uint8_t waitIRq = 0x00;
	uint8_t lastBits;
	uint8_t n;
	uint16_t i;

	switch (command) {
		case PCD_AUTHENT: {
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE: {
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
		break;
	}

	MFRC522_WriteRegister(MFRC522_REG_COMM_IE_N, irqEn | 0x80);
	MFRC522_ClearBitMask(MFRC522_REG_COMM_IRQ, 0x80);
	MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);
	MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_IDLE);

	// Writing data to the FIFO
	for (i = 0; i < sendLen; i++) MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, sendData[i]);

	// Execute the command
	MFRC522_WriteRegister(MFRC522_REG_COMMAND, command);
	if (command == PCD_TRANSCEIVE) MFRC522_SetBitMask(MFRC522_REG_BIT_FRAMING, 0x80);		// StartSend=1,transmission of data starts 

	// Waiting to receive data to complete
	i = 2000;	// i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms
	do {
		// CommIrqReg[7..0]
		// Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = MFRC522_ReadRegister(MFRC522_REG_COMM_IRQ);
		i--;
	} while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	MFRC522_ClearBitMask(MFRC522_REG_BIT_FRAMING, 0x80);																// StartSend=0

	if (i != 0)  {
		if (!(MFRC522_ReadRegister(MFRC522_REG_ERROR) & 0x1B)) {
			status = MI_OK;
			if (n & irqEn & 0x01) status = MI_NOTAGERR;
			if (command == PCD_TRANSCEIVE) {
				n = MFRC522_ReadRegister(MFRC522_REG_FIFO_LEVEL);
				lastBits = MFRC522_ReadRegister(MFRC522_REG_CONTROL) & 0x07;
				if (lastBits) *backLen = (n-1)*8+lastBits; else *backLen = n*8;
				if (n == 0) n = 1;
				if (n > MFRC522_MAX_LEN) n = MFRC522_MAX_LEN;
				for (i = 0; i < n; i++) backData[i] = MFRC522_ReadRegister(MFRC522_REG_FIFO_DATA);		// Reading the received data in FIFO
			}
		} else status = MI_ERR;
	}
	return status;
}

uint8_t MFRC522_Anticoll(uint8_t* serNum) {
	uint8_t status;
	uint8_t i;
	uint8_t serNumCheck = 0;
	uint16_t unLen;

	MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x00);												// TxLastBists = BitFramingReg[2..0]
	serNum[0] = PICC_ANTICOLL;
	serNum[1] = 0x20;
	status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);
	if (status == MI_OK) {
		// Check card serial number
		for (i = 0; i < 4; i++) serNumCheck ^= serNum[i];
		if (serNumCheck != serNum[i]) status = MI_ERR;
	}
	return status;
} 

void MFRC522_CalculateCRC(uint8_t*  pIndata, uint8_t len, uint8_t* pOutData) {
	uint8_t i, n;

	MFRC522_ClearBitMask(MFRC522_REG_DIV_IRQ, 0x04);													// CRCIrq = 0
	MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);													// Clear the FIFO pointer
	// Write_MFRC522(CommandReg, PCD_IDLE);

	// Writing data to the FIFO	
	for (i = 0; i < len; i++) MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, *(pIndata+i));
	MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_CALCCRC);

	// Wait CRC calculation is complete
	i = 0xFF;
	do {
		n = MFRC522_ReadRegister(MFRC522_REG_DIV_IRQ);
		i--;
	} while ((i!=0) && !(n&0x04));																						// CRCIrq = 1

	// Read CRC calculation result
	pOutData[0] = MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_L);
	pOutData[1] = MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_M);
}

uint8_t MFRC522_SelectTag(uint8_t* serNum) {
	uint8_t i;
	uint8_t status;
	uint8_t size;
	uint16_t recvBits;
	uint8_t buffer[9]; 

	buffer[0] = PICC_SElECTTAG;
	buffer[1] = 0x70;
	for (i = 0; i < 5; i++) buffer[i+2] = *(serNum+i);
	MFRC522_CalculateCRC(buffer, 7, &buffer[7]);		//??
	status = MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
	if ((status == MI_OK) && (recvBits == 0x18)) size = buffer[0]; else size = 0;
	return size;
}

uint8_t MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum) {
	uint8_t status;
	uint16_t recvBits;
	uint8_t i;
	uint8_t buff[12]; 

	// Verify the command block address + sector + password + card serial number
	buff[0] = authMode;
	buff[1] = BlockAddr;
	for (i = 0; i < 6; i++) buff[i+2] = *(Sectorkey+i);
	for (i=0; i<4; i++) buff[i+8] = *(serNum+i);
	status = MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);
	if ((status != MI_OK) || (!(MFRC522_ReadRegister(MFRC522_REG_STATUS2) & 0x08))) status = MI_ERR;
	return status;
}

uint8_t MFRC522_Read(uint8_t blockAddr, uint8_t* recvData) {
	uint8_t status;
	uint16_t unLen;

	recvData[0] = PICC_READ;
	recvData[1] = blockAddr;
	MFRC522_CalculateCRC(recvData,2, &recvData[2]);
	status = MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);
	if ((status != MI_OK) || (unLen != 0x90)) status = MI_ERR;
	return status;
}

uint8_t MFRC522_Write(uint8_t blockAddr, uint8_t* writeData) {
	uint8_t status;
	uint16_t recvBits;
	uint8_t i;
	uint8_t buff[18]; 

	buff[0] = PICC_WRITE;
	buff[1] = blockAddr;
	MFRC522_CalculateCRC(buff, 2, &buff[2]);
	status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);
	if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) status = MI_ERR;
	if (status == MI_OK) {
		// Data to the FIFO write 16Byte
		for (i = 0; i < 16; i++) buff[i] = *(writeData+i);
		MFRC522_CalculateCRC(buff, 16, &buff[16]);
		status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) status = MI_ERR;
	}
	return status;
}

void MFRC522_Init(void) {
	MFRC522_Reset();
	MFRC522_WriteRegister(MFRC522_REG_T_MODE, 0x8D);
	MFRC522_WriteRegister(MFRC522_REG_T_PRESCALER, 0x3E);
	MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_L, 30);           
	MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_H, 0);
	MFRC522_WriteRegister(MFRC522_REG_RF_CFG, 0x48/*0x70*/);				// 48dB gain	
	MFRC522_WriteRegister(MFRC522_REG_TX_AUTO, 0x40);
	MFRC522_WriteRegister(MFRC522_REG_MODE, 0x3D);
	MFRC522_AntennaOn();																		// Open the antenna
}

void MFRC522_Reset(void) {
	MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_RESETPHASE);
}

void MFRC522_AntennaOn(void) {
	uint8_t temp;

	temp = MFRC522_ReadRegister(MFRC522_REG_TX_CONTROL);
	if (!(temp & 0x03)) MFRC522_SetBitMask(MFRC522_REG_TX_CONTROL, 0x03);
}

void MFRC522_AntennaOff(void) {
	MFRC522_ClearBitMask(MFRC522_REG_TX_CONTROL, 0x03);
}

void MFRC522_Halt(void) {
	uint16_t unLen;
	uint8_t buff[4]; 

	buff[0] = PICC_HALT;
	buff[1] = 0;
	MFRC522_CalculateCRC(buff, 2, &buff[2]);
	MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
}
/****************************************************************************************************************************************/
/*********************************************************** Персонализация карты *******************************************************/
// void (*msDelay)(uint32_t ms) - указатель на функцию милисекундной задержки
// uint8_t TrailerBlockAddr - адрес блока трейлера, в котором нужно поменять ключи шифрования А и В
// uint8_t* KeyPointer - 
// uint8_t Discount - скидка по карте
// 
void CardPersonalization(void (*msDelay)(uint32_t ms), uint8_t Discount, uint32_t Bonus, uint32_t* NewCardKey)
{
		uint8_t FactoryCardKey[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};	// Заводской ключ карты
		uint8_t RC_size_;
		uint8_t status_;
		uint8_t	str_[MFRC522_MAX_LEN];
		uint8_t sn_[MFRC522_MAX_LEN];
		char	buff_[64];	
		uint8_t FactoryKeyAuthSuccessful = 0;
	
		MFRC522_Init();
		msDelay(20);
		status_ = MI_ERR;
		// Look for the card, return type
	  status_ = MFRC522_Request(PICC_REQIDL, str_);							
	  if (status_ == MI_OK) {
			sprintf(buff_, "\r\nSAK: 0x%02X, 0x%02X", str_[1], str_[0]);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nSAK: ----  ----");
			PrnToPc(buff_);
		}
		
	  // Anti-collision, return the card's 4-byte serial number
	  status_ = MFRC522_Anticoll(sn_);
    if (status_ == MI_OK) {
			sprintf(buff_, "\r\nCN: %x%x%x%x", sn_[0],sn_[1],sn_[2],sn_[3]);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nCN: --------");
			PrnToPc(buff_);
		}
			
		// Election card, return capacity
	  RC_size_ = MFRC522_SelectTag(sn_);
	  if (RC_size_ != 0) {
			sprintf(buff_, "\r\nCS: %d", RC_size_);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nCS: -");
			PrnToPc(buff_);
		}
			
		// Card reader
	  status_ = MFRC522_Auth(PICC_AUTHENT1A, 1, FactoryCardKey, sn_);			// Запись скидки на карту при персонификации
	  if (status_ == MI_OK) {
			FactoryKeyAuthSuccessful = 1;
			// Read data
		  status_ = MFRC522_Read(1, str_);
			if (status_== MI_OK) {
				sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[0],str_[1],str_[2],str_[3],str_[4],str_[5],str_[6],str_[7]);
				PrnToPc(buff_);
				sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[8],str_[9],str_[10],str_[11],str_[12],str_[13],str_[14],str_[15]);
				PrnToPc(buff_);
				if(str_[0] != Discount)
				{
					uint8_t TmpStr[16];
					TmpStr[0] = Discount;
					MFRC522_Write(1, TmpStr);
				}
				PrnToPc("\r\n");
		  }	
			uint8_t TmpStr[16] = {0};
			MFRC522_Write(1, TmpStr);
	  }
		else {
			FactoryKeyAuthSuccessful = 0;
			sprintf(buff_, "\r\n-- -- -- -- -- -- -- --");
			PrnToPc(buff_);
		}
		
		if(FactoryKeyAuthSuccessful)
		{
			// Card reader
			status_ = MFRC522_Auth(PICC_AUTHENT1A, 2, FactoryCardKey, sn_);	// Запись приветственных бонусов на карту при персонификации
			if (status_ == MI_OK) {
				// Read data
				status_ = MFRC522_Read(2, str_);
				if (status_ == MI_OK) {
					sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[0],str_[1],str_[2],str_[3],str_[4],str_[5],str_[6],str_[7]);
					PrnToPc(buff_);
					sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[8],str_[9],str_[10],str_[11],str_[12],str_[13],str_[14],str_[15]);
					PrnToPc(buff_);
					volatile uint32_t TmpBonus;
					TmpBonus = 0;
					TmpBonus |= str_[0]<<24;
					TmpBonus |= str_[1]<<16;
					TmpBonus |= str_[2]<<8;
					TmpBonus |= str_[3];
					volatile uint32_t BonusKop = Bonus * 100;
					if(TmpBonus != BonusKop)
					{
						volatile uint8_t TmpStr[16];
						TmpStr[3] = BonusKop;
						TmpStr[2] = (BonusKop>>8);
						TmpStr[1] = (BonusKop>>16);
						TmpStr[0] = (BonusKop>>24);
						MFRC522_Write(2, (uint8_t*)TmpStr);
					}
					PrnToPc("\r\n");
				}	
			}
			else {
				sprintf(buff_, "\r\n-- -- -- -- -- -- -- --");
				PrnToPc(buff_);
			}		
					// Card reader
			status_ = MFRC522_Auth(PICC_AUTHENT1A, 3, FactoryCardKey, sn_);	// Смена ключа шифрования при персонификации
			if (status_ == MI_OK) {
				// Read data
				status_ = MFRC522_Read(3, str_);
				if (status_ == MI_OK) {
					sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[0],str_[1],str_[2],str_[3],str_[4],str_[5],str_[6],str_[7]);
					PrnToPc(buff_);
					sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[8],str_[9],str_[10],str_[11],str_[12],str_[13],str_[14],str_[15]);
					PrnToPc(buff_);
					if((str_[15] == 0xFF)&&(str_[14] == 0xFF)&&(str_[13] == 0xFF)&&(str_[12] == 0xFF)&&(str_[11] == 0xFF)&&(str_[10] == 0xFF))
					{
						if((str_[15] != Settings.CardKey6)||(str_[14] != Settings.CardKey5)||(str_[13] != Settings.CardKey4)||(str_[12] != Settings.CardKey3)||(str_[11] != Settings.CardKey2)||(str_[10] != Settings.CardKey1))
						{
							uint8_t TmpStr[16];
							TmpStr[0] = *NewCardKey;
							TmpStr[1] = *(NewCardKey+1);
							TmpStr[2] = *(NewCardKey+2);
							TmpStr[3] = *(NewCardKey+3);
							TmpStr[4] = *(NewCardKey+4);
							TmpStr[5] = *(NewCardKey+5);
							TmpStr[6] = 0xFF;
							TmpStr[7] = 0x07;
							TmpStr[8] = 0x80;
							TmpStr[9] = 0x69;
							TmpStr[10] = *NewCardKey;
							TmpStr[11] = *(NewCardKey+1);
							TmpStr[12] = *(NewCardKey+2);
							TmpStr[13] = *(NewCardKey+3);
							TmpStr[14] = *(NewCardKey+4);
							TmpStr[15] = *(NewCardKey+5);
							sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", TmpStr[0],TmpStr[1],TmpStr[2],TmpStr[3],TmpStr[4],TmpStr[5],TmpStr[6],TmpStr[7]);
							PrnToPc(buff_);
							sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", TmpStr[8],TmpStr[9],TmpStr[10],TmpStr[11],TmpStr[12],TmpStr[13],TmpStr[14],TmpStr[15]);
							PrnToPc(buff_);
							MFRC522_Write(3, TmpStr);
							PrnToPc("\r\nЗаписан новый ключ");
						}
					}
					PrnToPc("\r\n");
					PrnToPc("\r\n");
				}		
			}
			else {
				sprintf(buff_, "\r\n-- -- -- -- -- -- -- --");
				PrnToPc(buff_);
			}
		}	
		
		PrnToPc("\r\n");
		PrnToPc("\r\n");
		PrnToPc("\r\n");
		
		msDelay(2);
		
		MFRC522_Halt();	
		//MFRC522_AntennaOff();
}
/****************************************************************************************************************************************/
/****************************************************************************************************************************************/
void GetMoneyFromCard(void (*msDelay)(uint32_t ms), uint32_t* CardKeyPointer, uint8_t* DiscountFromCard, uint32_t* CurrentSumKop, WorkModeTypeDef* CurrentWashMode)
{
		uint8_t CardKey[16] = {0};
		CardKey[0] = *CardKeyPointer;
		CardKey[1] = *(CardKeyPointer+1);
		CardKey[2] = *(CardKeyPointer+2);
		CardKey[3] = *(CardKeyPointer+3);
		CardKey[4] = *(CardKeyPointer+4);
		CardKey[5] = *(CardKeyPointer+5);
		uint8_t RC_size_;
		uint8_t status_;
		uint8_t	str_[MFRC522_MAX_LEN];
		uint8_t sn_[MFRC522_MAX_LEN];
		char	buff_[64];	
		//uint8_t FactoryKeyAuthSuccessful = 0;
	
		MFRC522_Init();
		msDelay(20);
		status_ = MI_ERR;
		// Look for the card, return type
	  status_ = MFRC522_Request(PICC_REQIDL, str_);							
	  if (status_ == MI_OK) {
			sprintf(buff_, "\r\nSAK: 0x%02X, 0x%02X", str_[1], str_[0]);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nSAK: ----  ----");
			PrnToPc(buff_);
		}
		
	  // Anti-collision, return the card's 4-byte serial number
	  status_ = MFRC522_Anticoll(sn_);
    if (status_ == MI_OK) {
			sprintf(buff_, "\r\nCN: %x%x%x%x", sn_[0],sn_[1],sn_[2],sn_[3]);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nCN: --------");
			PrnToPc(buff_);
		}
			
		// Election card, return capacity
	  RC_size_ = MFRC522_SelectTag(sn_);
	  if (RC_size_ != 0) {
			sprintf(buff_, "\r\nCS: %d", RC_size_);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nCS: -");
			PrnToPc(buff_);
		}
			
		// Чтение скидки с карты
	  status_ = MFRC522_Auth(PICC_AUTHENT1A, 1, CardKey, sn_);			
	  if (status_ == MI_OK) {
			// Read data
		  status_ = MFRC522_Read(1, str_);
			if (status_== MI_OK) {
				sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[0],str_[1],str_[2],str_[3],str_[4],str_[5],str_[6],str_[7]);
				PrnToPc(buff_);
				sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[8],str_[9],str_[10],str_[11],str_[12],str_[13],str_[14],str_[15]);
				PrnToPc(buff_);
				*DiscountFromCard = str_[0];
				*CurrentWashMode = ClientCardIsRead;
				PrnToPc("\r\nСчитана скидка\r\n");
		  }		
	  }
		else 
		{
			PrnToPc("\r\n-- -- -- -- -- -- -- --");
		}
		
		// Чтение денег с карты
			uint32_t TmpMoney;
			TmpMoney = 0;
			status_ = MFRC522_Auth(PICC_AUTHENT1A, 2, CardKey, sn_);	// Запись приветственных бонусов на карту при персонификации
			if (status_ == MI_OK) {
				// Read data
				status_ = MFRC522_Read(2, str_);
				if (status_ == MI_OK) {
					sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[0],str_[1],str_[2],str_[3],str_[4],str_[5],str_[6],str_[7]);
					PrnToPc(buff_);
					sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[8],str_[9],str_[10],str_[11],str_[12],str_[13],str_[14],str_[15]);
					PrnToPc(buff_);
					
					TmpMoney = 0;
					TmpMoney |= str_[0]<<24;
					TmpMoney |= str_[1]<<16;
					TmpMoney |= str_[2]<<8;
					TmpMoney |= str_[3];
					sprintf(buff_, "\r\nДенег на карте %02X %02X %02X %02X \r\n", (uint8_t)(TmpMoney>>24),(uint8_t)(TmpMoney>>16),(uint8_t)(TmpMoney>>8),(uint8_t)TmpMoney);
					PrnToPc(buff_);
				}
				if(TmpMoney != 0)
				{
					uint8_t TmpStr[16] = {0};
					status_ = MFRC522_Write(2, TmpStr);
					if(status_ == MI_OK)
					{
						*CurrentSumKop = *CurrentSumKop + TmpMoney;
						TmpMoney = 0;
						PrnToPc("Деньги сняты с карты");
					}
				}
			}
			else 
			{
				PrnToPc("\r\n-- -- -- -- -- -- -- --");
			}

		PrnToPc("\r\n");
		PrnToPc("\r\n");
		PrnToPc("\r\n");
		
		msDelay(2);
		
		MFRC522_Halt();	
		//MFRC522_AntennaOff();
}
/****************************************************************************************************************************************/
/****************************************************************************************************************************************/
void SaveMoneyToCard(void (*msDelay)(uint32_t ms), uint32_t* CardKeyPointer, uint32_t* CurrentSumKop, WorkModeTypeDef* CurrentWashMode, uint32_t* NewCardOperationDelay)
{
	uint8_t CardKey[16] = {0};
	CardKey[0] = *CardKeyPointer;
	CardKey[1] = *(CardKeyPointer+1);
	CardKey[2] = *(CardKeyPointer+2);
	CardKey[3] = *(CardKeyPointer+3);
	CardKey[4] = *(CardKeyPointer+4);
	CardKey[5] = *(CardKeyPointer+5);
	uint8_t RC_size_;
	uint8_t status_;
	uint8_t	str_[MFRC522_MAX_LEN];
	uint8_t sn_[MFRC522_MAX_LEN];
	char	buff_[64];	
		
	MFRC522_Init();
	msDelay(20);
	status_ = MI_ERR;
	// Look for the card, return type
	status_ = MFRC522_Request(PICC_REQIDL, str_);							
	if (status_ == MI_OK) {
		sprintf(buff_, "\r\nSAK: 0x%02X, 0x%02X", str_[1], str_[0]);
		PrnToPc(buff_);
	}
	else {
		sprintf(buff_, "\r\nSAK: ----  ----");
		PrnToPc(buff_);
	}
	
	// Anti-collision, return the card's 4-byte serial number
	status_ = MFRC522_Anticoll(sn_);
	if (status_ == MI_OK) {
		sprintf(buff_, "\r\nCN: %x%x%x%x", sn_[0],sn_[1],sn_[2],sn_[3]);
		PrnToPc(buff_);
	}
	else {
		sprintf(buff_, "\r\nCN: --------");
		PrnToPc(buff_);
	}
		
	// Election card, return capacity
	RC_size_ = MFRC522_SelectTag(sn_);
	if (RC_size_ != 0) {
		sprintf(buff_, "\r\nCS: %d", RC_size_);
		PrnToPc(buff_);
	}
	else {
		sprintf(buff_, "\r\nCS: -");
		PrnToPc(buff_);
	}
		
	// Сохранение денег на карту
		uint32_t TmpMoney;
		TmpMoney = 0;
		status_ = MFRC522_Auth(PICC_AUTHENT1A, 2, CardKey, sn_);	// Запись приветственных бонусов на карту при персонификации
		if (status_ == MI_OK) {
			// Read data
			status_ = MFRC522_Read(2, str_);
			if (status_ == MI_OK) {
				sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[0],str_[1],str_[2],str_[3],str_[4],str_[5],str_[6],str_[7]);
				PrnToPc(buff_);
				sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[8],str_[9],str_[10],str_[11],str_[12],str_[13],str_[14],str_[15]);
				PrnToPc(buff_);
				
				TmpMoney = 0;
				TmpMoney |= str_[0]<<24;
				TmpMoney |= str_[1]<<16;
				TmpMoney |= str_[2]<<8;
				TmpMoney |= str_[3];
				sprintf(buff_, "\r\nДенег на карте %02X %02X %02X %02X \r\n", (uint8_t)(TmpMoney>>24),(uint8_t)(TmpMoney>>16),(uint8_t)(TmpMoney>>8),(uint8_t)TmpMoney);
				PrnToPc(buff_);
			}
//			if(*CurrentSumKop != 0)
//			{
				TmpMoney = TmpMoney + *CurrentSumKop;
				uint8_t TmpStr[16] = {0};
				TmpStr[0] = (uint8_t)(TmpMoney >> 24);
				TmpStr[1] = (uint8_t)(TmpMoney >> 16);
				TmpStr[2] = (uint8_t)(TmpMoney >> 8);
				TmpStr[3] = (uint8_t)TmpMoney;
				
				status_ = MFRC522_Write(2, TmpStr);
				if(status_ == MI_OK)
				{
					*CurrentSumKop = *CurrentSumKop + TmpMoney;
					TmpMoney = 0;
					*CurrentSumKop = 0;
					
					*CurrentWashMode = IdlMode;
					
					CashSum = 0;
					SumFromClientCard = 0;
					GPIOE->ODR &= 0xE01F;																				// Очистка подсветки всех кнопок кроме Vendotek
					//HAL_GPIO_WritePin(LB9_GPIO_Port, LB9_Pin, GPIO_PIN_RESET);	// Очистка подсветки всех кнопок
					*NewCardOperationDelay = 5;
					PrnToPc("Деньги сохранены на карту");
				}
//			}
		}
		else 
		{
			PrnToPc("\r\n-- -- -- -- -- -- -- --");
		}

	PrnToPc("\r\n");
	PrnToPc("\r\n");
	PrnToPc("\r\n");
	
	msDelay(2);
	
	MFRC522_Halt();	
	//MFRC522_AntennaOff();
}
/****************************************************************************************************************************************/
/****************************************************************************************************************************************/
void ResetCardToTheFactoryState(void (*msDelay)(uint32_t ms), uint32_t* NewCardKey)
{
		//uint8_t FactoryCardKey[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};	// Заводской ключ карты
		uint8_t ActualCardKey[16] = {0};
		ActualCardKey[0] = *NewCardKey;
		ActualCardKey[1] = *(NewCardKey+1);
		ActualCardKey[2] = *(NewCardKey+2);
		ActualCardKey[3] = *(NewCardKey+3);
		ActualCardKey[4] = *(NewCardKey+4);
		ActualCardKey[5] = *(NewCardKey+5);

		uint8_t RC_size_;
		uint8_t status_;
		uint8_t	str_[MFRC522_MAX_LEN];
		uint8_t sn_[MFRC522_MAX_LEN];
		char	buff_[64];	
		//uint8_t FactoryKeyAuthSuccessful = 0;
	
		MFRC522_Init();
		msDelay(20);
		status_ = MI_ERR;
		// Look for the card, return type
	  status_ = MFRC522_Request(PICC_REQIDL, str_);							
	  if (status_ == MI_OK) {
			sprintf(buff_, "\r\nSAK: 0x%02X, 0x%02X", str_[1], str_[0]);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nSAK: ----  ----");
			PrnToPc(buff_);
		}
		
	  // Anti-collision, return the card's 4-byte serial number
	  status_ = MFRC522_Anticoll(sn_);
    if (status_ == MI_OK) {
			sprintf(buff_, "\r\nCN: %x%x%x%x", sn_[0],sn_[1],sn_[2],sn_[3]);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nCN: --------");
			PrnToPc(buff_);
		}
			
		// Election card, return capacity
	  RC_size_ = MFRC522_SelectTag(sn_);
	  if (RC_size_ != 0) {
			sprintf(buff_, "\r\nCS: %d", RC_size_);
			PrnToPc(buff_);
		}
		else {
			sprintf(buff_, "\r\nCS: -");
			PrnToPc(buff_);
		}
			
		// Card reader
	  status_ = MFRC522_Auth(PICC_AUTHENT1A, 1, ActualCardKey, sn_);			// Запись скидки на карту при персонификации
	  if (status_ == MI_OK) {
			//FactoryKeyAuthSuccessful = 1;
			// Read data
		  status_ = MFRC522_Read(1, str_);
			if (status_== MI_OK) {
				sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[0],str_[1],str_[2],str_[3],str_[4],str_[5],str_[6],str_[7]);
				PrnToPc(buff_);
				sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[8],str_[9],str_[10],str_[11],str_[12],str_[13],str_[14],str_[15]);
				PrnToPc(buff_);
				if(str_[0] != 0)
				{
					uint8_t TmpStr[16] = {0};
					MFRC522_Write(1, TmpStr);
				}
				PrnToPc("\r\n");
		  }	
			uint8_t TmpStr[16] = {0};
			MFRC522_Write(1, TmpStr);
	  }
		else {
			sprintf(buff_, "\r\n-- -- -- -- -- -- -- --");
			PrnToPc(buff_);
		}
		
			// Card reader
			status_ = MFRC522_Auth(PICC_AUTHENT1A, 2, ActualCardKey, sn_);	// Запись приветственных бонусов на карту при персонификации
			if (status_ == MI_OK) {
						uint8_t TmpStr[16] = {0};
						MFRC522_Write(2, TmpStr);
				}	

			// Card reader
			status_ = MFRC522_Auth(PICC_AUTHENT1A, 3, ActualCardKey, sn_);	// Смена ключа шифрования при персонификации
			if (status_ == MI_OK) {
				// Read data
				status_ = MFRC522_Read(3, str_);
				if (status_ == MI_OK) {
					sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[0],str_[1],str_[2],str_[3],str_[4],str_[5],str_[6],str_[7]);
					PrnToPc(buff_);
					sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", str_[8],str_[9],str_[10],str_[11],str_[12],str_[13],str_[14],str_[15]);
					PrnToPc(buff_);
					if((str_[15] != 0xFF)||(str_[14] != 0xFF)||(str_[13] != 0xFF)||(str_[12] != 0xFF)||(str_[11] != 0xFF)||(str_[10] != 0xFF))
					{
							uint8_t TmpStr[16];
							TmpStr[0] = 0xFF;
							TmpStr[1] = 0xFF;
							TmpStr[2] = 0xFF;
							TmpStr[3] = 0xFF;
							TmpStr[4] = 0xFF;
							TmpStr[5] = 0xFF;
							TmpStr[6] = 0xFF;
							TmpStr[7] = 0x07;
							TmpStr[8] = 0x80;
							TmpStr[9] = 0x69;
							TmpStr[10] = 0xFF;
							TmpStr[11] = 0xFF;
							TmpStr[12] = 0xFF;
							TmpStr[13] = 0xFF;
							TmpStr[14] = 0xFF;
							TmpStr[15] = 0xFF;
							sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", TmpStr[0],TmpStr[1],TmpStr[2],TmpStr[3],TmpStr[4],TmpStr[5],TmpStr[6],TmpStr[7]);
							PrnToPc(buff_);
							sprintf(buff_, "\r\n%02X %02X %02X %02X %02X %02X %02X %02X", TmpStr[8],TmpStr[9],TmpStr[10],TmpStr[11],TmpStr[12],TmpStr[13],TmpStr[14],TmpStr[15]);
							PrnToPc(buff_);
							MFRC522_Write(3, TmpStr);
							PrnToPc("\r\nЗаписан заводской ключ");
					}
					PrnToPc("\r\n");
					PrnToPc("\r\n");
				}		
			}
			else {
				sprintf(buff_, "\r\n-- -- -- -- -- -- -- --");
				PrnToPc(buff_);
			}
			
		
		PrnToPc("\r\n");
		PrnToPc("\r\n");
		PrnToPc("\r\n");
		
		msDelay(2);
		
		MFRC522_Halt();	
		//MFRC522_AntennaOff();
}
/****************************************************************************************************************************************/
/****************************************************************************************************************************************/
/****************************************************************************************************************************************/
//*

