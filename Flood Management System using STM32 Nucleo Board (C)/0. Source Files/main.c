/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h> // library for bool data type

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define CE_PORT GPIOB // PB6 chip enable (slave select)
#define CE_PIN GPIO_PIN_6
#define DC_PORT GPIOA // PA0 data/control
#define DC_PIN GPIO_PIN_0
#define RESET_PORT GPIOA // PA1 reset
#define RESET_PIN GPIO_PIN_1
#define GLCD_WIDTH 84	//define width of GLCD
#define GLCD_HEIGHT 48	//define height of GLCD
#define NUM_BANKS 6		//define number of banks GLCD

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim16;

/* USER CODE BEGIN PV */

//Define a font table reference array to be used to store the information to write
//specific characters to GLCD screen.
const char font_table[][6] =
{

	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},	//space		0
	{0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00},	//'A'		1
	{0x7F, 0x49, 0x49, 0x49, 0x36, 0x00},	//'B'		2
	{0x3E, 0x41, 0x41, 0x41, 0x22, 0x00},	//'C'		3
	{0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00},	//'D'		4
	{0x7F, 0x49, 0x49, 0x49, 0x41, 0x00}, 	//'E'		5
	{0x7F, 0x09, 0x09, 0x09, 0x01, 0x00}, 	//'F'		6
	{0x3E, 0x41, 0x49, 0x49, 0x7A, 0x00},	//'G'		7
	{0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00},	//'H'		8
	{0x41, 0x41, 0x7F, 0x41, 0x41, 0x00},	//'I'		9
	{0x20, 0x40, 0x40, 0x40, 0x3F, 0x00},	//'J'		10
	{0x7F, 0x08, 0x14, 0x22, 0x41, 0x00},	//'K'		11
	{0x7F, 0x40, 0x40, 0x40, 0x40, 0x00},	//'L'		12
	{0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00}, 	//'M'		13
	{0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00},	//'N'		14
	{0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00},	//'O'		15
	{0x7F, 0x09, 0x09, 0x09, 0x06, 0x00}, 	//'P'		16
	{0x3E, 0x41, 0x51, 0x61, 0x7E, 0x00}, 	//'Q'		17
	{0x7F, 0x09, 0x19, 0x29, 0x46, 0x00},	//'R'		18
	{0x26, 0x49, 0x49, 0x49, 0x32, 0x00},	//'S'		19
	{0x01, 0x01, 0x7F, 0x01, 0x01, 0x00}, 	//'T'		20
	{0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00},	//'U'		21
	{0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00},	//'V'		22
	{0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00}, 	//'W'		23
	{0x63, 0x14, 0x08, 0x14, 0x63, 0x00},	//'X'		24
	{0x03, 0x04, 0x78, 0x04, 0x03, 0x00}, 	//'Y'		25
	{0x61, 0x51, 0x49, 0x45, 0x43, 0x00},	//'Z'		26
	{0x00, 0x00, 0x5F, 0x00, 0x00, 0x00},	//'!'		27
	{0x00, 0x00, 0x00, 0xF8, 0xFC, 0x1C},	//Top Left Pipe		28
	{0x0E, 0x06, 0x06, 0x06, 0x0E, 0x8E}, 	//Top Middle Pipe	29
	{0xFC, 0xF8, 0x80, 0x00, 0x00, 0x00},	//Top Right Pipe	30
	{0x00, 0x00, 0x00, 0x7F, 0x7F, 0x00}, 	//Bottom Left Pipe	31
	{0x55, 0x2A, 0x00, 0x00, 0x00, 0x00},	//Water Animation1	32
	{0x2A, 0x55, 0x00, 0x00, 0x00, 0x00}, 	//Water Animation2	33
	{0x00, 0x80, 0x40, 0x20, 0x10, 0x08},	//Top Left Hazard	34
	{0x04, 0x02, 0x7A, 0x02, 0x04, 0x08},	//Top Mid Hazard	35
	{0x10, 0x20, 0x40, 0x80, 0x00, 0x00},	//Top Right Hazard	36
	{0x03, 0x04, 0x04, 0x04, 0x04, 0x04}, 	//Bot Left Hazard	37
	{0x04, 0x04, 0x05, 0x04, 0x04, 0x04},	//Bot Mid Hazard	38
	{0x04, 0x04, 0x04, 0x04, 0x03, 0x00},	//Bot Right Hazard	39
	{0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00},	//Water solidflow	40
	{0x40, 0x00, 0x00, 0x00, 0x00, 0x00}	//"."

};

bool flashLED = false;	//Boolean used to flash the LED for the alarm.
bool PMP2 = false;		//Boolean used to turn on the waterOut pump (PMP2)
int PWM_PERIOD = 40000;	//Define the PWM period to be used in the while loop.


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM16_Init(void);
static void MX_ADC2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

void SPI_write(unsigned char data);
void GLCD_data_write(unsigned char data);
void GLCD_command_write(unsigned char data);
void GLCD_init(void);
void GLCD_setCursor(unsigned char x, unsigned char y);
void GLCD_clear(void);
void GLCD_putchar(int font_table_row);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM16_Init();
  MX_ADC2_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  //Start the necessary timers.
  HAL_TIM_Base_Start_IT(&htim16); // Start Timer16
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // start PWM on Timer3’s Channel 1
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // start PWM on Timer2’s Channel 2

  //Initialize the screen
  GLCD_init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  //Check if the LED needs to flash.
	  if (flashLED)
	  {
		  //Toggle the alarm LED every 500 milliseconds.
		  HAL_GPIO_TogglePin(ALARM_GPIO_Port, ALARM_Pin);
		  HAL_Delay(500);
	  }

	  else
	  {
		  //Turn off the alarm LED.
		  HAL_GPIO_WritePin(ALARM_GPIO_Port, ALARM_Pin, 0);
	  }

	  //Check if PMP2 should be turned on or not.
	  if (PMP2 == true)
	  {
		  TIM2->CCR2 = (int) (0.45 * PWM_PERIOD); //Turn on waterOut Pump (PMP2)
	  }

	  else
	  {
		  TIM2->CCR2 = (int) (0 * PWM_PERIOD); //Turn off waterOut Pump (PMP2)
	  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 8;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc2.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 39999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 39999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 7999;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 999;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|ALARM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 ALARM_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|ALARM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


//This function is used to write using the SPI protocol to the GLCD screen.
//It takes an unsigned char that holds the data as a parameter.
void SPI_write(unsigned char data)
{
	// Chip Enable (low is asserted)
	HAL_GPIO_WritePin(CE_PORT, CE_PIN, GPIO_PIN_RESET);

	// Send data over SPI1
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &data, 1, HAL_MAX_DELAY);

	// Chip Disable
	HAL_GPIO_WritePin(CE_PORT, CE_PIN, GPIO_PIN_SET);
}

//This function switches the GLCD to data mode and then sends data over the SPI protocol.
//It takes an unsigned char with the data as a parameter.
void GLCD_data_write(unsigned char data)
{
	// Switch to "data" mode (D/C pin high)
	HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);

	// Send data over SPI
	SPI_write(data);
}

//This function switches the GLCD to command mode and then sends data over the SPI protocol.
//It takes an unsigned char with the data as a parameter.
void GLCD_command_write(unsigned char data)
{
	// Switch to "command" mode (D/C pin low)
	HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_RESET);

	// Send data over SPI
	SPI_write(data);
}

//This function initializes the GLCD for how this project intends to use it.
//It follows the procedures recommended in the data sheet for the PCD8544 screen.
void GLCD_init(void)
{
	// Keep CE high when not transmitting
	HAL_GPIO_WritePin(CE_PORT, CE_PIN, GPIO_PIN_SET);

	// Reset the screen (low pulse - down & up)
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RESET_PORT, RESET_PIN, GPIO_PIN_SET);

	// Configure the screen (according to the datasheet)
	GLCD_command_write(0x21); // enter extended command mode
	GLCD_command_write(0xB0); // set LCD Vop for contrast (this may be adjusted)
	GLCD_command_write(0x04); // set temp coefficient
	GLCD_command_write(0x15); // set LCD bias mode (this may be adjusted)
	GLCD_command_write(0x20); // return to normal command mode
	GLCD_command_write(0x0C); // set display mode normal
}

//This function allows the user to move the cursor to a new spot on the GLCD screen.
//It takes an unsigned char column number and unsigned char bank number as parameters.
void GLCD_setCursor(unsigned char x, unsigned char y)
{
	GLCD_command_write(0x80 | x); // column
	GLCD_command_write(0x40 | y); // bank
}

//This function clears the GLCD screen.
void GLCD_clear(void)
{
	int i;
	for(i = 0; i < (GLCD_WIDTH * NUM_BANKS); i++)
	{
		GLCD_data_write(0x00); // write zeros
	}

	GLCD_setCursor(0,0); // return cursor to top left

}

//This function pulls data from the font table to know what to display to each
//bank of the GLCD screen.
//It takes an array of arrays each with 6 elements as an argument.
void GLCD_putchar(int font_table_row)
{
	 int i;
	 for (i=0; i<6; i++)
	 {
		 GLCD_data_write(font_table[font_table_row][i]);
	 }

}

// Callback: this ISR is triggered whenever a timer has expired.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 // Check which timer triggered this callback
 if (htim == &htim16) // If the triggered timer was Timer 16,
 {
	 int PWM_PERIOD = 40000;//Assign a period for PWM.
	 int ADC_RANGE = 4096; // Assign an ADC range (2^12 = 12-bit resolution)

	 // Start ADC Conversion
	 HAL_ADC_Start(&hadc1);
	 HAL_ADC_Start(&hadc2);

	 // Wait for ADC conversion to complete
	 HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	 HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);

	 // Read ADC values
	 uint16_t waterLevel_measurement = HAL_ADC_GetValue(&hadc1);
	 uint16_t waterIn_measurement = HAL_ADC_GetValue(&hadc2);

	 // Convert ADC levels to a fraction of total
	 float waterLevel_value = ((float) waterLevel_measurement) / ADC_RANGE;
	 float waterIn_value = ((float) waterIn_measurement) / ADC_RANGE;

	 // Write the PWM duty cycle for the the waterIn Pump (PMP1).
	  TIM3->CCR1 = (int) (waterIn_value * PWM_PERIOD); //This drives the waterIn Pump.

	 //These are known waterLevel values for reference.
	 //max -- waterLevel_value == 0.1867
	 //min -- waterLevel_value == 0.05
	 //Alarm On -- water_value == 0.17

	  //Pump off situation.
	 if (waterLevel_value < 0.05)
	 {
		 //Stop pumping out the water.
		 PMP2 = false;	//Turn off waterOut Pump (PMP2)

		 //DSIPLAY THE SYSTEM OFF MESSAGE
			GLCD_clear(); // clear the screen

			//"SYSTEM OFF." message
			GLCD_setCursor(0,3);	//New Line
			GLCD_putchar(19);	//S
			GLCD_putchar(25);	//Y
			GLCD_putchar(19);	//S
			GLCD_putchar(20);	//T
			GLCD_putchar(5);	//E
			GLCD_putchar(13);	//M
			GLCD_putchar(0);	//
			GLCD_putchar(15);	//O
			GLCD_putchar(6);	//F
			GLCD_putchar(6);	//F
			GLCD_putchar(41);	//.

	 }

	 //Pump on situation.
	 else if(waterLevel_value > 0.12)

	 {
		//Pump out the water.
		PMP2 = true;	//Turn off waterOut Pump (PMP2)


		 //DISPLAY THE PUMP IS ON MESSAGE
		GLCD_clear(); // clear the screen

		//Initial Pipe Illustration
		GLCD_setCursor(0,0);
		GLCD_putchar(28);
		GLCD_putchar(29);
		GLCD_putchar(30);
		GLCD_setCursor(0,1);
		GLCD_putchar(31);
		GLCD_putchar(0);
		GLCD_putchar(32);

		//"PUMP IS ON" message
		GLCD_setCursor(0,2);	//New Line
		GLCD_putchar(16);	//P
		GLCD_putchar(21);	//U
		GLCD_putchar(13);	//M
		GLCD_putchar(16);	//P
		GLCD_putchar(0);	//
		GLCD_putchar(9);	//I
		GLCD_putchar(19);	//S
		GLCD_putchar(0);	//
		GLCD_putchar(15);	//O
		GLCD_putchar(14);	//N
		GLCD_putchar(41);	//.

		//Check for Alarm situation
		 if(waterLevel_value > 0.17)
		 {
			//Flash the alarm LED.
			flashLED = true;

			//DISPLAY THE ALARM MESSAGE TO THE LCD
			GLCD_clear(); // clear the screen

			//Initial Pipe Illustration
			GLCD_setCursor(0,0);
			GLCD_putchar(28);
			GLCD_putchar(29);
			GLCD_putchar(30);
			GLCD_setCursor(0,1);
			GLCD_putchar(31);
			GLCD_putchar(0);
			GLCD_putchar(40);

			//"ECESSIVE FLOODING." message
			GLCD_setCursor(0,2);	//New Line
			GLCD_putchar(5);	//E
			GLCD_putchar(24);	//X
			GLCD_putchar(3);	//C
			GLCD_putchar(5);	//E
			GLCD_putchar(19);	//S
			GLCD_putchar(19);	//S
			GLCD_putchar(9);	//I
			GLCD_putchar(22);	//V
			GLCD_putchar(5);	//E
			GLCD_setCursor(0,3);	//New Line
			GLCD_putchar(6);	//F
			GLCD_putchar(12);	//L
			GLCD_putchar(15);	//O
			GLCD_putchar(15);	//O
			GLCD_putchar(4);	//D
			GLCD_putchar(9);	//I
			GLCD_putchar(14);	//N
			GLCD_putchar(7);	//G
			GLCD_putchar(27);	//!

		 }

		 else
		 {
			 //Stop flashing the LED.
			 flashLED = false;

		 }

	 }

 }

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
