/**
  ******************************************************************************
  * @file    MyMatrix.h
  * @brief   This file contains headers of my functions.
  ******************************************************************************
*/

 /* Define to prevent recursive inclusion -------------------------------------*/
 
#ifndef __MYMATRIX_H
#define __MYMATRIX_H

#include "stdint.h"
#include "MyDefines.h"

void Welcom (WorkModeTypeDef* CurrentMode);
void ClearMatrix(uint32_t* Target_);
void ClearUpHalfMatrix(uint32_t* Target_);
void ClearDownHalfMatrix(uint32_t* Target_);
void PrintUpHalfMatrix(uint32_t* Target_,uint32_t PrintStartColumnTarget, uint32_t* Source);
void Money(WorkModeTypeDef* CurrentMode, uint32_t MoneyKop, uint32_t* Target);
void InscriptionSelectMode(WorkModeTypeDef* CurrentMode, uint32_t* Target);
void InscriptionWater(WorkModeTypeDef* CurrentMode, uint32_t* Target);
void InscriptionFoam(WorkModeTypeDef* CurrentMode, uint32_t* Target);
void InscriptionWax(WorkModeTypeDef* CurrentMode, uint32_t* Target);
void InscriptionOsmos(WorkModeTypeDef* CurrentMode, uint32_t* Target);
void InscriptionVacuumCliner(WorkModeTypeDef* CurrentMode, uint32_t* Target);
void InscriptionAir(WorkModeTypeDef* CurrentMode, uint32_t* Target);
void InscriptionPause(WorkModeTypeDef* CurrentMode, uint32_t* Target);
void PauseTimeDisplaying(WorkModeTypeDef* CurrentMode, uint32_t CurentPauseTime, uint32_t* Target);
void InscriptionSelectTheAmountAndClickOk(WorkModeTypeDef* CurrentMode, uint32_t* Target);	//Выводит надпись "Выберите сумму и нажмите ОК"
void InscriptionAttachABankCard (WorkModeTypeDef* CurrentMode, uint32_t* Target);
void InscriptionSelectModeOrMakePayment(WorkModeTypeDef* CurrentMode, uint32_t* Target); 		//Выводит надпись "Выберите режим или внесите оплату"
void InscriptionDop(WorkModeTypeDef* CurrentMode, uint32_t* Target);

#endif /* __MYMATRIX_H */
