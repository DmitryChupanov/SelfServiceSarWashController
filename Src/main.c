/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "MyWH1602.h"
#include "MySPI.h"
#include "MyDefines.h"
#include "MyMatrix.h"
#include "MyMainFCs.h"
#include "MyUSART_FCs.h"
#include "rc522.h"
#include "MyVendotek.h"
#include "MyRTC.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
volatile uint8_t MainMatrixArray[MatrixStreeng][MatrixColumn] =  // Массив для матрицы MatrixStreeng = 16  MatrixColumn	= 4
{{255,255,255,255},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{0x80,0,0,1},
{255,255,255,255}};

uint32_t Sum = 0;
uint32_t OldCashSum = 0;
uint32_t CashSum = 0;
//uint32_t CashlessSum = 0;
uint32_t SumFromClientCard = 0;

SettingsTypedef Settings;

//typedef struct {
//	uint32_t PulseTimeMs;				// —уммарное врем¤ импульсов в мс.
//	GPIO_PinState State;				// —осот¤ние импульсного входа 1 или 0
//	uint32_t HighStateCounter;	// —четчик времени нахождени¤ пина в высоком состо¤нии
//}PulseInParametersTupeDef;
//PulseInParametersTupeDef PI3;
//PulseInParametersTupeDef PI2;
//PulseInParametersTupeDef PI1;

ButtonStateTypeDef ButtonUp;
ButtonStateTypeDef ButtonDown;
ButtonStateTypeDef ButtonOk;
ButtonStateTypeDef ButtonLeft;
ButtonStateTypeDef ButtonRight;
uint32_t ButtonUpCounter = 0;
uint32_t ButtonDownCounter = 0;
uint32_t ButtonOkCounter = 0;
uint32_t ButtonLeftCounter = 0;
uint32_t ButtonRightCounter = 0;

ButtonStateTypeDef BI1 = ButtonReset;
ButtonStateTypeDef BI2 = ButtonReset;
ButtonStateTypeDef BI3 = ButtonReset;
ButtonStateTypeDef BI4 = ButtonReset;
ButtonStateTypeDef BI5 = ButtonReset;
ButtonStateTypeDef BI6 = ButtonReset;
ButtonStateTypeDef BI7 = ButtonReset;
ButtonStateTypeDef BI8 = ButtonReset;
ButtonStateTypeDef BI9 = ButtonReset;
ButtonStateTypeDef BI10 = ButtonReset;
ButtonStateTypeDef BI11 = ButtonReset;
ButtonStateTypeDef BI12 = ButtonReset;
ButtonStateTypeDef BI13 = ButtonReset;
ButtonStateTypeDef BI14 = ButtonReset;
ButtonStateTypeDef BI15 = ButtonReset;
ButtonStateTypeDef BI16 = ButtonReset;

MenuLstTypeDef MenuLst = SetingsMenu;
uint32_t SetingsMenuString = 0;
uint32_t OldSetingsMenuString;
uint32_t PIMenuString = 0;

SetsMenyStringsTypeDef SetsMenyStrings={
	"   Настроики    ",
	"Имп.вход.1      ",
	"Имп.вход.2      ",
	"Имп.вход.3      ",
	"Вода            ",
	"Пена            ",
	"Воск            ",
	"Осмос           ",
	"Пылесос         ",
	"Воздух          ",
	"Пауза           ",
	"Доп реж 1       ",
/*	"Доп реж 2       ",
	"Доп реж 3       ",
	"Доп реж 4       ",
	"Доп реж 5       ",
	"Доп реж 6       ",*/
	"Карты           ",
	"Vendotek        ",
	"Время           ",
	"                ",
};

PIMenyStringsTypeDef PIMenyStrings={
	"Цена имп.",
	"Длит.имп.",
	"Выход           ",
	"                ",
};

Cl_ModeMenuTypeDef ClM_MenuStrings={
	"                ",
	"Кнопка N        ",
	"Выход 1         ",
	"Режим 1         ",
	"Процент 1       ",
	"Выход 2         ",
	"Режим 2         ",
	"Процент 2       ",
	"Выход 3         ",
	"Режим 3         ",
	"Процент 3       ",
	"Выход 4         ",
	"Режим 4         ",
	"Процент 4       ",
	"Цена сек        ",
	"Выход           ",
	"                ",
};

WorkModeTypeDef WashMode = IdlMode;

volatile uint8_t ReleModuleTxBuf[ReleModuleTxBufSize];
volatile uint32_t ReleModuleTxBuf1p = 0;
volatile uint32_t ReleModuleTxBuf2p = 0;

volatile ReleOutputStateTypedef RO;
TransmissionStateTypedef TransmissionToReleModuleState = NoTransmission;

PauseMenuTypeDef PauseMenuStrings={
	"                ",
	"Беспл мин       ",
	"Цена сек        ",
	"Выход           ",
	"                ",
};

uint32_t FreePauseSeconds = 0;
uint32_t PauseAuxTimer = 0;
uint32_t SendDataToReleModuleCounter = 0;
//uint32_t SendDataToReleModuleCounter2 = 0;
uint8_t RS485PC_TransferCompleted = 1; // Установка бита завершения передачи
uint8_t PC_TxBuf[PC_TxBufSize];
volatile uint32_t PC_TxBuf1p = 0;
volatile uint32_t PC_TxBuf2p = 0;
uint8_t PC_RxBuf[PC_RxBufSize];
volatile uint32_t PC_RxBuf1p = 0;
volatile uint32_t PC_RxBuf2p = 0;

CardsMenuTypeDef CardsMenuStrings={
	"                ",
	"Ключ 1       	 ",
	"Ключ 2       	 ",
	"Ключ 3       	 ",
	"Ключ 4       	 ",
	"Ключ 5       	 ",
	"Ключ 6       	 ",
	"Скидка       	 ",
	"Бонус        	 ",
	"Кардридер    	 ",
	"Выход           ",
	"                ",
};


uint8_t blockAddr;
uint8_t sectorKeyA[16][16] = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                             {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                             {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
                             {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},};
//uint8_t FactoryCardKey[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};	// Заводской ключ карты
//uint8_t ReadCardKey[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};			// Прочтенный
uint8_t RfBlockAddr;
														 
														 
//uint8_t RC_size;
//uint8_t status;
//uint8_t	str[MFRC522_MAX_LEN];
//uint8_t sn[/*4*/MFRC522_MAX_LEN];
//char	buff[66];	
//uint8_t FactoryKeyAuthSuccessful = 0;
//uint8_t	RfStrToWrite[MFRC522_MAX_LEN] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,
//																				 0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,};	
uint8_t DiscountReadFromCard = 0;
uint32_t CardDelay = 0;

uint8_t VendotekRxBuf[VendotekRxBufSize] = {0};
uint32_t VendotekRxBuf1p = 0;
uint32_t VendotekRxBuf2p = 0;
														 
uint8_t TestVar = 0x00;			
uint32_t RFID_TimeCounter = 0;

uint8_t VendotekTxBuf[VendotekTxBufSize] = {0};
uint32_t VendotekTxBuf1p = 0;
uint32_t VendotekTxBuf2p = 0;

uint32_t IdlPacketTimeCounter = 0;
uint8_t FirstTransfer = 0;

uint8_t VendotekTxBufAdd[VendotekTxBufSize];
//uint32_t VendotekTxBufAdd1p = 0;
//uint32_t VendotekTxBufAdd2p = 0;

uint32_t MoneyForCashlessPaymentRequest = 0;	// Деньги, которые клиент хочет оплатить через вендотек. Выбираетс кнопками.

OutputPercentTypeDef OutputPercent;

uint32_t ShowMoneyCounter = 0;

VendotekMenuTypeDef VendotekMenuStrings={
	"                ",
	"Шаг           	 ",
	"Выход           ",
	"                ",
};

uint32_t DosingCounter1 = 0;
uint32_t DosingCounter2 = 0;
uint32_t DosingCounter3 = 0;
uint32_t DosingCounter4 = 0;
uint32_t DosingCounter5 = 0;
uint32_t DosingCounter6 = 0;
uint32_t DosingCounter7 = 0;
uint32_t DosingCounter8 = 0;
uint32_t DosingCounter9 = 0;
uint32_t DosingCounter10 = 0;

uint8_t VFD_TxBuf[VFD_TxBufSize];
volatile uint32_t VFD_TxBuf1p = 0;
volatile uint32_t VFD_TxBuf2p = 0;
uint8_t VFD_RxBuf[VFD_RxBufSize];
volatile uint32_t VFD_RxBuf1p = 0;
volatile uint32_t VFD_RxBuf2p = 0;

RTCMenuTypeDef RTCMenuStrings={
	"                ",
	"Число           ",
	"Месяц           ",
	"Год             ",
	"Часы            ",
	"Минуты          ",
	"Секунды         ",
	"Выход           ",
	"                ",
};

TempRTCDataTypeDef TempRTCData;

//RTC_TimeTypeDef CurrentTime;
//RTC_DateTypeDef CurrentDate;
uint32_t RTCReadCounter = 0;

DateAndTimeTypeDef CurrentDateAndTime;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART5_Init(void);
static void MX_UART4_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_RTC_Init(void);
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void StartTask04(void const * argument);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_UART5_Init();
  MX_UART4_Init();
  MX_SPI2_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_RTC_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityRealtime, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, StartTask04, osPriorityIdle, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
 

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* RTC init function */
static void MX_RTC_Init(void)
{

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* SPI2 init function */
static void MX_SPI2_Init(void)
{

  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* UART4 init function */
static void MX_UART4_Init(void)
{

  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* UART5 init function */
static void MX_UART5_Init(void)
{

  huart5.Instance = UART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LB11_Pin|LB10_Pin|LB9_Pin|LB8_Pin 
                          |LB7_Pin|LB6_Pin|LB5_Pin|LB4_Pin 
                          |LB3_Pin|LB2_Pin|LB1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MatrixSCLK_GPIO_Port, MatrixSCLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MatrixA_Pin|MatrixB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MatrixEn_Pin|DQR1_Pin|DQR2_Pin|DQR3_Pin 
                          |DQR4_Pin|DQR5_Pin|DQR6_Pin|DQR7_Pin 
                          |DQR8_Pin|DQL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RF_RST_GPIO_Port, RF_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RF_CS_GPIO_Port, RF_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, RS485TxEn_PC_Pin|RS_485ReleTxEn_Pin|DQR9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LB11_Pin LB10_Pin LB9_Pin LB8_Pin 
                           LB7_Pin LB6_Pin LB5_Pin LB4_Pin 
                           LB3_Pin LB2_Pin LB1_Pin */
  GPIO_InitStruct.Pin = LB11_Pin|LB10_Pin|LB9_Pin|LB8_Pin 
                          |LB7_Pin|LB6_Pin|LB5_Pin|LB4_Pin 
                          |LB3_Pin|LB2_Pin|LB1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : MatrixSCLK_Pin */
  GPIO_InitStruct.Pin = MatrixSCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MatrixSCLK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MatrixA_Pin MatrixB_Pin */
  GPIO_InitStruct.Pin = MatrixA_Pin|MatrixB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MatrixEn_Pin DQR1_Pin DQR2_Pin RF_RST_Pin 
                           DQR3_Pin DQR4_Pin DQR5_Pin DQR6_Pin 
                           DQR7_Pin DQR8_Pin DQL_Pin */
  GPIO_InitStruct.Pin = MatrixEn_Pin|DQR1_Pin|DQR2_Pin|RF_RST_Pin 
                          |DQR3_Pin|DQR4_Pin|DQR5_Pin|DQR6_Pin 
                          |DQR7_Pin|DQR8_Pin|DQL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : RF_CS_Pin RS485TxEn_PC_Pin RS_485ReleTxEn_Pin DQR9_Pin */
  GPIO_InitStruct.Pin = RF_CS_Pin|RS485TxEn_PC_Pin|RS_485ReleTxEn_Pin|DQR9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : RF_IRQ_Pin ButtonDown_Pin ButtonRight_Pin ButtonOk_Pin 
                           ButtonUp_Pin ButtonLeft_Pin */
  GPIO_InitStruct.Pin = RF_IRQ_Pin|ButtonDown_Pin|ButtonRight_Pin|ButtonOk_Pin 
                          |ButtonUp_Pin|ButtonLeft_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : BI11_Pin BI10_Pin BI9_Pin BI8_Pin 
                           BI7_Pin BI6_Pin BI5_Pin BI4_Pin 
                           BI3_Pin BI2_Pin BI1_Pin */
  GPIO_InitStruct.Pin = BI11_Pin|BI10_Pin|BI9_Pin|BI8_Pin 
                          |BI7_Pin|BI6_Pin|BI5_Pin|BI4_Pin 
                          |BI3_Pin|BI2_Pin|BI1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PulseIn1_Pin */
  GPIO_InitStruct.Pin = PulseIn1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PulseIn1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PulseIn2_Pin PulseIn3_Pin */
  GPIO_InitStruct.Pin = PulseIn2_Pin|PulseIn3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN 5 */
	uint32_t SettingsSize = sizeof(Settings) / 4;
	if(FLASH_Read(SettingsFlashAddress) != 0xFFFFFFFF)
	{
		for(uint32_t i = 0; i < SettingsSize; i++)
		{
			*(&Settings.ImpulsePricePI3+i) = FLASH_Read(SettingsFlashAddress + (i*4));
		}
	}
	else
	{
		SetDefaults();
	}
  /* Infinite loop */
  for(;;)
  {
		if((WashMode == IdlMode)||(WashMode == CashPaymentRecieveMode)||(WashMode == ClientCardIsRead))			// Разрешение обработки импульсных входов
		{
			PulseInputControl(&CashSum);
		}
		osDelay(1);
  }
  /* USER CODE END 5 */ 
}

/* StartTask02 function */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	WH1602Init((void (*)())osDelay);
	osDelay(1);
	WH1602_Print ((char*)&SetsMenyStrings+(16*SetingsMenuString), 1, (void (*)())osDelay, 1);
	WH1602_Print ((char*)&SetsMenyStrings.StrSets+(16*SetingsMenuString)+16, 2, (void (*)())osDelay, 1);
	//WH1602_SetDDRAM_Address (0x0F);
	USART5_Transmit_Init();
	UART4_DMA_Transmit_Init();
	UART4_DMA_Receive_Init (PC_RxBuf, PC_RxBufSize);
	USART1_DMA_Receive_Init (VFD_RxBuf, VFD_RxBufSize);
	USART1_DMA_Transmit_Init();
	
  /* Infinite loop */
  for(;;)
  {
		ButtonsHandler();	// Обработчик нажатия кнопок
		Menu();
		//-------------------------------------- Контроль нажатия кнопок клиентом ------------------------------------------------------------
		ClientButtonsControl(&WashMode, &IdlPacketTimeCounter); 				// Контроль нажатия кнопок клиентом
		//------------------------------------------ Контроль подсветки кнопок ---------------------------------------------------------------
		ButtonLedControl(&WashMode);
		//------------------------------------------------------------------------------------------------------------------------------------
		
		//------------------------------------- Переход в ждущий режим -----------------------------------------------------------------------
		if((Sum == 0)&&  ((WashMode == PauseMode)  ||  ((WashMode >= Water)&&(WashMode <= Dop6Mode))))
		{
			DiscountReadFromCard = 0;
			//DiscountReadFromCardFlag = 0;
			//MoneyReadFromClientCardFlag = 0;
			WashMode = IdlMode;
			RO.Rele16State = 0;
			OldCashSum = 0;
			// Отключение всех реле
			RO.Rele1State = 0;
			RO.Rele2State = 0;
			RO.Rele3State = 0;
			RO.Rele4State = 0;
			RO.Rele5State = 0;
			RO.Rele6State = 0;
			RO.Rele7State = 0;
			RO.Rele8State = 0;
			RO.Rele9State = 0;
			RO.Rele10State = 0;
			RO.Rele11State = 0;
			RO.Rele12State = 0;
			RO.Rele13State = 0;
			RO.Rele14State = 0;
			RO.Rele15State = 0;
			RO.Rele16State = 0;
			// Отключение подсветки всех кнопок
			GPIOE->ODR &= 0x001F;
			//HAL_GPIO_WritePin(LB9_GPIO_Port, LB9_Pin, GPIO_PIN_RESET);
		}
		
		
		if((((OldCashSum == 0)&&(CashSum != 0)))&&((WashMode == IdlMode)||(WashMode == ClientCardIsRead))) //  Переход в режим приема наличных денег денег
		{
			WashMode = CashPaymentRecieveMode;
			OldCashSum = CashSum;
			HAL_GPIO_WritePin(LB1_GPIO_Port, LB1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LB2_GPIO_Port, LB2_Pin, GPIO_PIN_RESET);
		}
		if((WashMode == PauseMode)||((WashMode >= Water)&&(WashMode <= Dop6Mode)))
		{
			OldCashSum = 0;
		}
		if(((WashMode == IdlMode)||(WashMode == ClientCardIsRead))&&(MoneyForCashlessPaymentRequest > 0)) // Переход в режим приема безналичного платежа
		{
			WashMode = CashlessPaymentRecieveMode;
			HAL_GPIO_WritePin(LB1_GPIO_Port, LB1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LB2_GPIO_Port, LB2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LB3_GPIO_Port, LB3_Pin, GPIO_PIN_RESET);
		}
		//----------------------------------- Управление светом -----------------------------------------------------------------------------
		if(WashMode != IdlMode)						// Управление светом
			RO.Rele10State = 1;
		else
			RO.Rele10State = 0;
		
		//---------------------------------- Создание тега для передачи команд в релейныймодуль ---------------------------------------------
//		SendDataToReleModuleCounter++;
//		if(SendDataToReleModuleCounter >= 1000)
//		{
//			SendDataToReleModuleCounter=0;
//			AddTag(1, sizeof(RO), (uint8_t*)&RO, (uint8_t*)ReleModuleTxBuf, (uint32_t*)&ReleModuleTxBuf1p, ReleModuleTxBufSize);
//			AddTag(2, sizeof(OutputPercent), (uint8_t*)&OutputPercent, (uint8_t*)ReleModuleTxBuf, (uint32_t*)&ReleModuleTxBuf1p, ReleModuleTxBufSize);
//		}
////		SendDataToReleModuleCounter2++;
////		if(SendDataToReleModuleCounter2 >= 5000)
////		{
////			SendDataToReleModuleCounter2 = 0;
////			AddTag(2, sizeof(OutputPercent), (uint8_t*)&OutputPercent, (uint8_t*)ReleModuleTxBuf, (uint32_t*)&ReleModuleTxBuf1p, ReleModuleTxBufSize);
////		}
		
		//----------------------------------- Передача данных из буфера в релейный модуль ----------------------------------------------------
//		if((ReleModuleTxBuf1p != ReleModuleTxBuf2p)&&(TransmissionToReleModuleState == NoTransmission))
//		{
//			TransmissionToReleModuleState = TransmissionInProcess;
//			HAL_GPIO_WritePin(RS_485ReleTxEn_GPIO_Port, RS_485ReleTxEn_Pin, GPIO_PIN_SET);
//			UART5->DR = ReleModuleTxBuf[ReleModuleTxBuf2p++];
//			ReleModuleTxBuf2p %= ReleModuleTxBufSize;
//			UART5->CR1 |= USART_CR1_TXEIE; // Разрешение прерывания
//		}

		/*--------------------------------------------------------- Управление реле -------------------------------------------------------------------------*/
		DOControlFc(RO.Rele1Mode, RO.Rele1State, DQR1_GPIO_Port, DQR1_Pin, OutputPercent.Out1Percent, &DosingCounter1);
		DOControlFc(RO.Rele2Mode, RO.Rele2State, DQR2_GPIO_Port, DQR2_Pin, OutputPercent.Out2Percent, &DosingCounter2);
		DOControlFc(RO.Rele3Mode, RO.Rele3State, DQR3_GPIO_Port, DQR3_Pin, OutputPercent.Out3Percent, &DosingCounter3);
		DOControlFc(RO.Rele4Mode, RO.Rele4State, DQR4_GPIO_Port, DQR4_Pin, OutputPercent.Out4Percent, &DosingCounter4);
		DOControlFc(RO.Rele5Mode, RO.Rele5State, DQR5_GPIO_Port, DQR5_Pin, OutputPercent.Out5Percent, &DosingCounter5);
		DOControlFc(RO.Rele6Mode, RO.Rele6State, DQR6_GPIO_Port, DQR6_Pin, OutputPercent.Out6Percent, &DosingCounter6);
		DOControlFc(RO.Rele7Mode, RO.Rele7State, DQR7_GPIO_Port, DQR7_Pin, OutputPercent.Out7Percent, &DosingCounter7);
		DOControlFc(RO.Rele8Mode, RO.Rele8State, DQR8_GPIO_Port, DQR8_Pin, OutputPercent.Out8Percent, &DosingCounter8);
		DOControlFc(RO.Rele9Mode, RO.Rele9State, DQR9_GPIO_Port, DQR9_Pin, OutputPercent.Out9Percent, &DosingCounter9);
		DOControlFc(RO.Rele10Mode, RO.Rele10State, DQL_GPIO_Port, DQL_Pin, OutputPercent.Out10Percent, &DosingCounter10);
		/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
		
		//--------------------------------------- Отображение денег на табло ----------------------------------------------------------------------------------
		ShowMoneyCounter++;
		if(ShowMoneyCounter > 500)
		{
			if(((WashMode >= Water)&&(WashMode <= Dop6Mode)) || ((WashMode == PauseMode)&&(FreePauseSeconds == 0)) || (WashMode == ReadyToWash))	// Отображение остатка денег
			{
				Money(&WashMode, Sum, (uint32_t *) &MainMatrixArray[0][0]);
			}
			
			if(WashMode == CashPaymentRecieveMode)
			{
				Money(&WashMode, CashSum, (uint32_t *) &MainMatrixArray[0][0]);
			}
			
			if((WashMode == CashlessPaymentRecieveMode)||(WashMode == WaitBankCard))											// Отображение суммы, которую собирается оплатить клиент по безналичному рассчету
			{
				Money(&WashMode, MoneyForCashlessPaymentRequest, (uint32_t *) &MainMatrixArray[0][0]);
			}
			
			if(WashMode == ClientCardIsRead)
			{
				Money(&WashMode, SumFromClientCard, (uint32_t *) &MainMatrixArray[0][0]);
			}
			ShowMoneyCounter = 0;
		}
		
		
		//------------------------------------------------------------------------------------------------------------------------------------------------------
		
		if((WashMode == PauseMode)&&(FreePauseSeconds != 0))																					// Отображение оставшегося времени бесплатной паузы
		{
			PauseTimeDisplaying(&WashMode, FreePauseSeconds, (uint32_t *) &MainMatrixArray[0][0]);
		}
		
		
		MoneySubtraction(&WashMode, &Sum);														// Уменьшение остатка денег

		/*-------------------------------------------------- Передача данных в комп через RS-485 ------------------------------------------------------------*/
		PC_RS485Send();
		/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
		
		VendotekRxBuf1p = VendotekRxBufSize - DMA1_Channel6 -> CNDTR;
		
		
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* StartTask03 function */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
	MatrixSPI_Init();
	MatrixSPI_Init();
	MFRC522_Init();
	//CharCounter = 0;
	RfBlockAddr = 1;
  /* Infinite loop */
  for(;;)
  {
//		WH1602_SetDDRAM_Address (0x40);
//		osDelay(1);
//		WH1602SendByte(CharCounter, RS_Data, RW_Write);
//		osDelay(1);
//		CharCounter++;
//    osDelay(1000);

		Welcom(&WashMode);
//		Money(&WashMode, Sum, (uint32_t *) &MainMatrixArray[0][0]);
		InscriptionSelectMode(&WashMode, (uint32_t *) &MainMatrixArray[8][0]);	// Выводит надпись "Выберите режим" во время приема наличных денег
		InscriptionWater(&WashMode,(uint32_t *) &MainMatrixArray[8][0]);
		InscriptionFoam(&WashMode,(uint32_t *) &MainMatrixArray[8][0]);
		InscriptionWax(&WashMode,(uint32_t *) &MainMatrixArray[8][0]);
		InscriptionOsmos(&WashMode,(uint32_t *) &MainMatrixArray[8][0]);
		InscriptionVacuumCliner(&WashMode,(uint32_t *) &MainMatrixArray[8][0]);
		InscriptionAir(&WashMode,(uint32_t *) &MainMatrixArray[8][0]);
		InscriptionPause(&WashMode,(uint32_t *) &MainMatrixArray[8][0]);
		InscriptionSelectTheAmountAndClickOk(&WashMode, (uint32_t *) &MainMatrixArray[8][0]); //	Выводит надпись "Выберите сумму и нажмите ОК"
		InscriptionAttachABankCard (&WashMode, (uint32_t *) &MainMatrixArray[8][0]);
		InscriptionSelectModeOrMakePayment(&WashMode, (uint32_t *) &MainMatrixArray[8][0]);
		InscriptionDop(&WashMode, (uint32_t *) &MainMatrixArray[8][0]);
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* StartTask04 function */
void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
	USART2_DMA_Transmit_Init();
	USART2_DMA_Receive_Init (VendotekRxBuf, VendotekRxBufSize);
	
  /* Infinite loop */
  for(;;)
  {
		if(Settings.RFID_OnOff == 1)	// Если считыватель RFID включен в настройках
		{
			RFID_TimeCounter++;
			if(RFID_TimeCounter >= 2000)
			{
				#ifndef CardsFactoryReset
				if(CardDelay > 0)
				{
					CardDelay--;
				}
				if((WashMode == IdlMode)&&(CardDelay == 0))
				{
					CardPersonalization((void (*)())osDelay, Settings.CardDiscount, Settings.CardBonus, &Settings.CardKey1);
				}
				if((WashMode == IdlMode)&&(CardDelay == 0))
				{
					GetMoneyFromCard((void (*)())osDelay, &Settings.CardKey1, &DiscountReadFromCard, &SumFromClientCard, &WashMode);
				}
				if((WashMode == PauseMode)&&(Sum != 0)&&(CardDelay == 0))
				{
					SaveMoneyToCard((void (*)())osDelay, &Settings.CardKey1, &Sum, &WashMode, &CardDelay);
				}
				#endif
				#ifdef CardsFactoryReset
				ResetCardToTheFactoryState((void (*)())osDelay, &Settings.CardKey1);
				#endif
				RFID_TimeCounter = 0;
				
			}			
		}
		
		// ------------------------------ Передача IDL пакета в Vendotek ------------------------------------
		IdlPacketTimeCounter++;
		if((IdlPacketTimeCounter >= LastKeepaliveIntervalInSeconds * 1000)&&(IdlMessageBlock == 0))
		{
			IdlPacketTimeCounter = 0;
			SendIdlPacket(lastOperationNumber, VendotekTxBuf, &VendotekTxBuf1p, VendotekTxBufSize);
		}
		
		//-------------------------------- Отправка данных из буфера в Vendotek --------------------------------------------------
		if(FirstTransfer == 0)
		{
			FirstTransfer = 1;
			USART2_DMA_Transmit (&TestVar, 1);
		}
		if ((VendotekTxBuf1p!=VendotekTxBuf2p)&&(USART2->SR & USART_SR_TXE)&&(DMA1->ISR & DMA_ISR_TCIF7))																			// Проверяем, появилось ли что - нибудь для отправки в отладочный порт
		{
				if(VendotekTxBuf1p>VendotekTxBuf2p)																	//Если убегающий указатель больше догоняющего
				{
					uint16_t SendDataLen = VendotekTxBuf1p - VendotekTxBuf2p;					//То вычисляем длину куска, который нужно передать
					USART2_DMA_Transmit (&VendotekTxBuf[VendotekTxBuf2p], SendDataLen);	//Передаем кусок данных через DMA
					VendotekTxBuf2p = VendotekTxBuf2p+SendDataLen;											//Приравниваем догоняющую метку к убегающей
				}
				else if (VendotekTxBuf1p<VendotekTxBuf2p)
				{
					uint16_t SendDataLen1 = VendotekTxBufSize - VendotekTxBuf2p;			// Вычисляем длину куска, который нужно передать до конца буфера
					uint16_t SendDataLen2 = VendotekTxBuf1p;													// Вычисляем длину куска, который нужно передать от начала буфера
					uint16_t SendDataLen = SendDataLen1 + SendDataLen2;								// Суммарная длина данных, которые нужно передать
					for(uint16_t i = 0; i < SendDataLen; i++)
					{
						VendotekTxBufAdd[i] = VendotekTxBuf[VendotekTxBuf2p++];					// Копируем данные в новый буфер
						VendotekTxBuf2p %= VendotekTxBufSize;															// Закольцовка
						if(i > VendotekTxBufSize) break;
					}
					USART2_DMA_Transmit (VendotekTxBufAdd, SendDataLen);										//Передаем кусок данных через DMA
				}
			
		}
		//---------------------------- Парсинг данных, принятых от Vendotek -----------------------------------------------------------
		VendotekParsing();
		//-----------------------------------------------------------------------------------------------------------------------------
		//---------------------------------------------- Чтение часов реального времени -----------------------------------------------
		RTCReadCounter++;
		if(RTCReadCounter >= 1000)
		{
			RTCReadCounter = 0;
			unixtime_to_datetime(GetUnixTime(), &CurrentDateAndTime);
			//HAL_RTC_GetTime(&hrtc, &CurrentTime, RTC_FORMAT_BIN);
			//HAL_RTC_GetDate(&hrtc, &CurrentDate, RTC_FORMAT_BIN);
		}
		//-----------------------------------------------------------------------------------------------------------------------------
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
/* USER CODE BEGIN Callback 0 */

/* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
/* USER CODE BEGIN Callback 1 */

/* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
