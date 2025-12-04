/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2021 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"
#include "cmsis_os.h"

/* USER CODE BEGIN 0 */
#include "MyDefines.h"
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

extern TIM_HandleTypeDef htim6;

/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Prefetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  osSystickHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles TIM6 global interrupt.
*/
void TIM6_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_IRQn 0 */

  /* USER CODE END TIM6_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_IRQn 1 */

  /* USER CODE END TIM6_IRQn 1 */
}

/* USER CODE BEGIN 1 */
#pragma push
#pragma O0
void SPI1_IRQHandler (void)
{
//	static uint8_t Streeng = 0;
//	static uint8_t Column = 0;
//	//SPI1->DR = ~MainMatrixArray[Streeng][3-Column];
//	SPI1->DR = ~MainMatrixArray[Streeng][Column];
//	Streeng += 4;
//	if(Streeng >= 16)
//	{
//		Column++;
//		if(Column >= 4)
//		{
//			HAL_GPIO_WritePin(MatrixEn_GPIO_Port, MatrixEn_Pin, GPIO_PIN_RESET);	// Отключение всей матрицы
//			Column = 0;
//			switch (Streeng){
//				case 16 : Streeng = 1; SetB; SetA;     break;
//				case 17 : Streeng = 2; SetB; ResetA;   break;
//				case 18 : Streeng = 3; ResetB; SetA;   break;
//				case 19 : Streeng = 0; ResetB; ResetA; break;
//			};
//			for(uint16_t i = 0; i < 250; i++)
//			{
//				if((SPI1->SR & SPI_SR_BSY) == 0) break;
//			}
//			HAL_GPIO_WritePin(MatrixSCLK_GPIO_Port, MatrixSCLK_Pin, GPIO_PIN_SET);	//Запоминание значения в сдвиговых регистрах
//			for(uint16_t i = 0; i < 5; i++){__NOP();}
//			HAL_GPIO_WritePin(MatrixSCLK_GPIO_Port, MatrixSCLK_Pin, GPIO_PIN_RESET);//
//			for(uint16_t i = 0; i < 5; i++){__NOP();}
//			HAL_GPIO_WritePin(MatrixEn_GPIO_Port, MatrixEn_Pin, GPIO_PIN_SET);		// Включение всей матрицы
//		}
//		else
//		{
//			Streeng -= 16;
//		}
//	}
	static int8_t Streeng = 0;
	static int8_t Column = 0;
	//SPI1->DR = ~MainMatrixArray[Streeng][3-Column];
	//SPI1->DR = ~MainMatrixArray[Streeng][Column];
//	static uint8_t MyMatrixArray[16][4] = 
//	{
//		0x80,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//		0x00,0x00,0x00,0x00,
//	};
	//SPI1->DR = ~MyMatrixArray[15 - Streeng][Column];
	SPI1->DR = ~MainMatrixArray[15 - Streeng][Column];
	Streeng += 4;
	if(Streeng >= 16)
	{
		Column++;
		if(Column >= 4)
		{
			HAL_GPIO_WritePin(MatrixEn_GPIO_Port, MatrixEn_Pin, GPIO_PIN_RESET);	// Отключение всей матрицы
			Column = 0;
			switch (Streeng){
				case 16 : Streeng = 1; SetB; SetA;     break;
				case 17 : Streeng = 2; SetB; ResetA;   break;
				case 18 : Streeng = 3; ResetB; SetA;   break;
				case 19 : Streeng = 0; ResetB; ResetA; break;
			};
			for(uint16_t i = 0; i < 250; i++)
			{
				if((SPI1->SR & SPI_SR_BSY) == 0) break;
			}
			HAL_GPIO_WritePin(MatrixSCLK_GPIO_Port, MatrixSCLK_Pin, GPIO_PIN_SET);	//Запоминание значения в сдвиговых регистрах
			for(uint16_t i = 0; i < 5; i++){__NOP();}
			HAL_GPIO_WritePin(MatrixSCLK_GPIO_Port, MatrixSCLK_Pin, GPIO_PIN_RESET);//
			for(uint16_t i = 0; i < 5; i++){__NOP();}
			HAL_GPIO_WritePin(MatrixEn_GPIO_Port, MatrixEn_Pin, GPIO_PIN_SET);		// Включение всей матрицы
		}
		else
		{
			Streeng -= 16;
		}
	}	
}
#pragma pop

void UART5_IRQHandler (void)
{
	if((UART5->SR & USART_SR_TXE)==USART_SR_TXE)
	{
		if(ReleModuleTxBuf1p != ReleModuleTxBuf2p)
		{
			UART5->DR = ReleModuleTxBuf[ReleModuleTxBuf2p++];
			ReleModuleTxBuf2p %= ReleModuleTxBufSize;
		}
		else
		{
			TransmissionToReleModuleState = NoTransmission;
			UART5->CR1 &= ~USART_CR1_TXEIE;
			//HAL_GPIO_WritePin(RS_485ReleTxEn_GPIO_Port, RS_485ReleTxEn_Pin, GPIO_PIN_RESET);
		}
	}
}

void DMA2_Channel4_5_IRQHandler(void)				//Прерывание по завершению передачи UART4
{
	if ((UART4 ->SR & USART_SR_TC))
	{	
		RS485PC_ReceiveON							// Переключение микросхемы RS485 в режим приема
		DMA2->IFCR |= DMA_IFCR_CGIF5|DMA_IFCR_CTCIF5|DMA_IFCR_CHTIF5|DMA_IFCR_CTEIF5; // Сброс флага глобального прерывания|флага завершения передачи|флага половинной передачи|флага ошибки передачи
		RS485PC_TransferCompleted = 1; // Установка бита завершения передачи
	}
}



/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
