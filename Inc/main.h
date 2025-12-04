/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2021 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define LB11_Pin GPIO_PIN_5
#define LB11_GPIO_Port GPIOE
#define LB10_Pin GPIO_PIN_6
#define LB10_GPIO_Port GPIOE
#define MatrixSCLK_Pin GPIO_PIN_4
#define MatrixSCLK_GPIO_Port GPIOA
#define MatrixA_Pin GPIO_PIN_4
#define MatrixA_GPIO_Port GPIOC
#define MatrixB_Pin GPIO_PIN_5
#define MatrixB_GPIO_Port GPIOC
#define MatrixEn_Pin GPIO_PIN_0
#define MatrixEn_GPIO_Port GPIOB
#define DQR1_Pin GPIO_PIN_1
#define DQR1_GPIO_Port GPIOB
#define DQR2_Pin GPIO_PIN_2
#define DQR2_GPIO_Port GPIOB
#define LB9_Pin GPIO_PIN_7
#define LB9_GPIO_Port GPIOE
#define LB8_Pin GPIO_PIN_8
#define LB8_GPIO_Port GPIOE
#define LB7_Pin GPIO_PIN_9
#define LB7_GPIO_Port GPIOE
#define LB6_Pin GPIO_PIN_10
#define LB6_GPIO_Port GPIOE
#define LB5_Pin GPIO_PIN_11
#define LB5_GPIO_Port GPIOE
#define LB4_Pin GPIO_PIN_12
#define LB4_GPIO_Port GPIOE
#define LB3_Pin GPIO_PIN_13
#define LB3_GPIO_Port GPIOE
#define LB2_Pin GPIO_PIN_14
#define LB2_GPIO_Port GPIOE
#define LB1_Pin GPIO_PIN_15
#define LB1_GPIO_Port GPIOE
#define RF_RST_Pin GPIO_PIN_12
#define RF_RST_GPIO_Port GPIOB
#define RF_CS_Pin GPIO_PIN_8
#define RF_CS_GPIO_Port GPIOD
#define RF_IRQ_Pin GPIO_PIN_9
#define RF_IRQ_GPIO_Port GPIOD
#define ButtonDown_Pin GPIO_PIN_10
#define ButtonDown_GPIO_Port GPIOD
#define ButtonRight_Pin GPIO_PIN_11
#define ButtonRight_GPIO_Port GPIOD
#define ButtonOk_Pin GPIO_PIN_13
#define ButtonOk_GPIO_Port GPIOD
#define ButtonUp_Pin GPIO_PIN_14
#define ButtonUp_GPIO_Port GPIOD
#define ButtonLeft_Pin GPIO_PIN_15
#define ButtonLeft_GPIO_Port GPIOD
#define BI11_Pin GPIO_PIN_5
#define BI11_GPIO_Port GPIOG
#define BI10_Pin GPIO_PIN_6
#define BI10_GPIO_Port GPIOG
#define BI9_Pin GPIO_PIN_7
#define BI9_GPIO_Port GPIOG
#define BI8_Pin GPIO_PIN_8
#define BI8_GPIO_Port GPIOG
#define PulseIn1_Pin GPIO_PIN_6
#define PulseIn1_GPIO_Port GPIOC
#define PulseIn2_Pin GPIO_PIN_8
#define PulseIn2_GPIO_Port GPIOA
#define PulseIn3_Pin GPIO_PIN_15
#define PulseIn3_GPIO_Port GPIOA
#define RS485Tx_PC_Pin GPIO_PIN_10
#define RS485Tx_PC_GPIO_Port GPIOC
#define RS485Rx_PC_Pin GPIO_PIN_11
#define RS485Rx_PC_GPIO_Port GPIOC
#define RS_485ReleTx_Pin GPIO_PIN_12
#define RS_485ReleTx_GPIO_Port GPIOC
#define RS485TxEn_PC_Pin GPIO_PIN_0
#define RS485TxEn_PC_GPIO_Port GPIOD
#define RS_485ReleTxEn_Pin GPIO_PIN_1
#define RS_485ReleTxEn_GPIO_Port GPIOD
#define RS_485ReleRx_Pin GPIO_PIN_2
#define RS_485ReleRx_GPIO_Port GPIOD
#define DQR9_Pin GPIO_PIN_7
#define DQR9_GPIO_Port GPIOD
#define BI7_Pin GPIO_PIN_9
#define BI7_GPIO_Port GPIOG
#define BI6_Pin GPIO_PIN_10
#define BI6_GPIO_Port GPIOG
#define BI5_Pin GPIO_PIN_11
#define BI5_GPIO_Port GPIOG
#define BI4_Pin GPIO_PIN_12
#define BI4_GPIO_Port GPIOG
#define BI3_Pin GPIO_PIN_13
#define BI3_GPIO_Port GPIOG
#define BI2_Pin GPIO_PIN_14
#define BI2_GPIO_Port GPIOG
#define BI1_Pin GPIO_PIN_15
#define BI1_GPIO_Port GPIOG
#define DQR3_Pin GPIO_PIN_3
#define DQR3_GPIO_Port GPIOB
#define DQR4_Pin GPIO_PIN_4
#define DQR4_GPIO_Port GPIOB
#define DQR5_Pin GPIO_PIN_5
#define DQR5_GPIO_Port GPIOB
#define DQR6_Pin GPIO_PIN_6
#define DQR6_GPIO_Port GPIOB
#define DQR7_Pin GPIO_PIN_7
#define DQR7_GPIO_Port GPIOB
#define DQR8_Pin GPIO_PIN_8
#define DQR8_GPIO_Port GPIOB
#define DQL_Pin GPIO_PIN_9
#define DQL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
