/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include <stdio.h>
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "my_linked_list.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

typedef enum
{
	Default  = 48,
	Option_1 = 49,
	Option_2 = 50,
	Option_3 = 51,
	Option_4 = 52,

}LedOptionsType_t;

typedef enum
{

	LED_ON  = 4095,
	LED_OFF = 0,

}LedStateType_t;

uint8_t tx_buffer[] = "1";
uint8_t rx_buffer = Default;

uint8_t rx_flag = STATE_OFF;
uint8_t led_flag = STATE_ON;
uint8_t check_flag = STATE_OFF;
HAL_StatusTypeDef status_flag;
StateType_t greeting_flag = STATE_OFF;

uint8_t txData = (0x66U);
uint8_t rxData = (0x00U);

uint8_t askVar[] = "\n Enter the number, press Space key after entering.\n\r";
uint8_t askIndex[] = "\n Enter the index, press Space key after entering.\n\r";
uint8_t var[4] = {0};
uint8_t varDec = 0;

uint8_t repeat[] = "\n\n\n\r Please Choose An Operation\n\r Add to Head - 1\n\r Add to Tail - 2\n\r Delete Selected Node - 3\n\r Display List - 4\n\r";
uint8_t greeting_list[] = "\n\n\n\r Welcome to Number List\n\n\r Each element of the list can hold up to number 255 and no more\n\n\r Only use numbers and Space key. Please do not press any other button.\n\n\n\r Choose the Linked List operation to run\n\r Add to Head - 1\n\r Add to Tail - 2\n\r Delete Selected Node - 3\n\r Display List - 4\n\r";
uint8_t greeting_led[] = " Write the numbers on the side to run the corresponding action\n\r Led Toggle - 1\n\r Led Blinker - 2\n\r Led Slow Toggle - 3\n\r";



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint16_t readValue = 0U;

LinkedList list;

void setPWM_Freq(uint32_t freq)
{

	uint32_t tempARR = __HAL_TIM_GET_AUTORELOAD(&htim2);
	uint32_t newPSC = ( ( SystemCoreClock / (freq * (tempARR) ) ) - 1 );

	__HAL_TIM_SET_PRESCALER(&htim2, newPSC);

}

void setPWM_DutyCycle(uint32_t value)
{

	uint32_t cycle = (value / 40.95);

	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, cycle);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if( rx_buffer != Default ) { rx_flag = STATE_ON;}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Transmit(huart, greeting_led, sizeof(greeting_led), 500);
	led_flag = STATE_ON;
}

static void Led_GPIO_OutputInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	led_flag = STATE_OFF;
}

static void Led_TIM_OutputInit(void)
{
	TIM_OC_InitTypeDef sConfigOC = {0};

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
	  Error_Handler();
	}

	HAL_TIM_MspPostInit(&htim2);

	led_flag = STATE_ON;
}

void LedControl(void)
{
	  if( rx_flag )
	  {
		  switch(rx_buffer){

				case Option_1:

					if( led_flag )
					{
						Led_GPIO_OutputInit();
					}

					uint8_t choice1[] = "\nChosen Option 1 - Led Toggle\n\r";
					HAL_UART_Transmit(&huart2, choice1, sizeof(choice1), HAL_MAX_DELAY);
					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);

					if( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) ) {readValue = LED_ON;}
					else {readValue = LED_OFF;}

					rx_flag = STATE_OFF;

					break;

				case Option_2:

					if( led_flag )
					{
						Led_GPIO_OutputInit();
					}

					uint8_t choice2[] = "\nChosen Option 2 - Led Blinker\n\r";
					HAL_UART_Transmit(&huart2, choice2, sizeof(choice2), HAL_MAX_DELAY);

					for( uint8_t count = 0; count < 10; count  ++)
					{
						HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
						HAL_Delay(100);
					}

					if( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) ) {readValue = LED_ON;}
					else {readValue = LED_OFF;}

					rx_flag = STATE_OFF;

					break;

				case Option_3:

					if( !led_flag )
					{
						Led_TIM_OutputInit();
					}

					uint8_t choice3[] = "\nChosen Option 3 - Led Slow Toggle\n\r";
					HAL_UART_Transmit(&huart2, choice3, sizeof(choice3), HAL_MAX_DELAY);

					if( readValue == LED_OFF )
					{
						while( readValue != LED_ON)
						{
							setPWM_DutyCycle(readValue);
							readValue += 100;
							HAL_Delay(20);

							if( readValue > 4000)
							{
								readValue = LED_ON;
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
							}
						}
					}
					else if( readValue == LED_ON)
					{
						while( readValue != LED_OFF)
						{
							setPWM_DutyCycle(readValue);
							readValue -= 100;
							HAL_Delay(20);

							if( readValue < 100)
							{
								readValue = LED_OFF;
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
							}
						}
					}

					rx_flag = STATE_OFF;

					break;

				default:
					uint8_t repeat[] = "\n\rPlease Choose A Number\n\r Led Toggle - 1\n\r Led Blinker - 2\n\r Led Slow Toggle - 3\n\r";
					HAL_UART_Transmit(&huart2, repeat, sizeof(repeat), HAL_MAX_DELAY);

					rx_flag = STATE_OFF;
			}
	  }
	  else
	  {
		  HAL_UART_Receive_IT(&huart2, &rx_buffer, sizeof(rx_buffer));
	  }
}

void LinkedListControl(void)
{

	if( rx_flag )
	{

		switch(rx_buffer){

		case Option_1:

			uint8_t choice1[] = "\n\n\n Chosen Option 1 - Add to Head\n\r";
			HAL_UART_Transmit(&huart2, choice1, sizeof(choice1), 500);

			HAL_UART_Transmit(&huart2, askVar, sizeof(askVar), 500);

			status_flag = HAL_UART_Receive(&huart2, var, sizeof(var), HAL_MAX_DELAY);

			// Control for Receive function
			varDec = GetDecimal(&huart2, var, sizeof(var));

			if( status_flag == HAL_OK && var[0] != 0 && varDec)
			{
				// Add node to the head of list
				AddHead(&list, varDec);

				// Control for if node added
				if( GetNode(&list, 1)->data == GetDecimal(&huart2, var, sizeof(var)) )
				{
					uint8_t result1[] = "\n Data successfully added to the head\n\r";
					HAL_UART_Transmit(&huart2, result1, sizeof(result1), 500);
				}
				else
				{
					uint8_t errorADD[] = "\n ERROR: Node couldn't added to the list \n\r";
					HAL_UART_Transmit(&huart2, errorADD, sizeof(errorADD), 500);
				}
			}
			else
			{
				uint8_t errorReceive[] = "\n ERROR: Data receiving error \n\r";
				HAL_UART_Transmit(&huart2, errorReceive, sizeof(errorReceive), 500);
			}

			HAL_UART_Transmit(&huart2, repeat, sizeof(repeat), 500);

			// Reset variables

			for(uint8_t i = 0; i < sizeof(var); i++)
			{
				var[i] = 0;
			}
			rx_flag = STATE_OFF;
			rx_buffer = Default;
			status_flag = STATE_OFF;

			break;

		case Option_2:


			uint8_t choice2[] = "\n\n\n Chosen Option 2 - Add to Tail\n\r";
			HAL_UART_Transmit(&huart2, choice2, sizeof(choice2), 500);


			HAL_UART_Transmit(&huart2, askVar, sizeof(askVar), 500);

			status_flag = HAL_UART_Receive(&huart2, var, sizeof(var), HAL_MAX_DELAY);


			// Control for Receive function
			varDec = GetDecimal(&huart2, var, sizeof(var));

			if( status_flag == HAL_OK && var[0] != 0 && varDec)
			{
				// Add node to the head of list

				AddTail(&list, varDec);

				// Control if node added

				if( GetNode(&list, list.tail->index)->data == GetDecimal(&huart2, var, sizeof(var)) )
				{
					uint8_t result1[] = "\n Data successfully added to the tail\n\r";
					HAL_UART_Transmit(&huart2, result1, sizeof(result1), 500);
				}
				else
				{
					uint8_t errorADD[] = "\n ERROR: Node couldn't added to the list \n\r";
					HAL_UART_Transmit(&huart2, errorADD, sizeof(errorADD), 500);
				}
			}
			else
			{
				uint8_t errorReceive[] = "\n ERROR: Data receiving error \n\r";
				HAL_UART_Transmit(&huart2, errorReceive, sizeof(errorReceive), 500);
			}

			HAL_UART_Transmit(&huart2, repeat, sizeof(repeat), 500);

			for(uint8_t i = 0; i < sizeof(var); i++)
			{
				var[i] = 0;
			}
			rx_flag = STATE_OFF;
			rx_buffer = Default;
			status_flag = STATE_OFF;

			break;

		case Option_3:


			uint8_t choice3[] = "\n\n\n Chosen Option 3 - Delete Selected Node\n\r";
			HAL_UART_Transmit(&huart2, choice3, sizeof(choice3), 500);

			// check if list is empty
			if( IsEmpty(&list) )
			{
				uint8_t empty[] = "\n ERROR: Cannot use Delete operation. List is Empty.\n\r";
				HAL_UART_Transmit(&huart2, empty, sizeof(empty), 500);

				HAL_UART_Transmit(&huart2, repeat, sizeof(repeat), 500);

				for(uint8_t i = 0; i < sizeof(var); i++)
				{
					var[i] = 0;
				}
				rx_flag = STATE_OFF;
				rx_buffer = Default;
				status_flag = STATE_OFF;

			}
			else
			{

				HAL_UART_Transmit(&huart2, askIndex, sizeof(askVar), 500);

				HAL_UART_Receive(&huart2, var, sizeof(var), HAL_MAX_DELAY);

				//Kontrol noktası
				if( status_flag == HAL_OK && var[0] != 0 )
				{
					Node *node = GetNode(&list, GetDecimal(&huart2, var, sizeof(var)) );

					//Control if node is in the list
					if(node)
					{
						Delete(&list, node);

						//Control if node is deleted
						if( CheckNode(&list, node) == HAL_ERROR )
						{
							uint8_t result3[] = "\n Data successfully deleted from the list\n\r";
							HAL_UART_Transmit(&huart2, result3, sizeof(result3), 500);
						}
					}
					else
					{
						uint8_t errorNotFound[] = "\n ERROR: Node with the data entered does not exist\n\r";
						HAL_UART_Transmit(&huart2, errorNotFound, sizeof(errorNotFound), 500);

				}
			}

			HAL_UART_Transmit(&huart2, repeat, sizeof(repeat), 500);

			for(uint8_t i = 0; i < sizeof(var); i++)
			{
				var[i] = 0;
			}
			rx_flag = STATE_OFF;
			rx_buffer = Default;
			status_flag = STATE_OFF;

			break;

		case Option_4:


			uint8_t choice4[] = "\n\n\n Chosen Option 4 - Display List\n\r";
			HAL_UART_Transmit(&huart2, choice4, sizeof(choice4), 500);

			DisplayLinkedList(&list, &huart2);

			HAL_UART_Transmit(&huart2, repeat, sizeof(repeat), 500);

			for(uint8_t i = 0; i < sizeof(var); i++)
			{
				var[i] = 0;
			}
			rx_flag = STATE_OFF;
			rx_buffer = Default;
			status_flag = STATE_OFF;

			break;

		default:
			HAL_UART_Transmit(&huart2, repeat, sizeof(repeat), 500);

			for(uint8_t i = 0; i < sizeof(var); i++)
			{
				var[i] = 0;
			}
			rx_flag = STATE_OFF;
			rx_buffer = Default;
			status_flag = STATE_OFF;

			break;
			}
		}
	}
	else
	{
		HAL_UART_Receive_IT(&huart2, &rx_buffer, sizeof(rx_buffer));
		HAL_Delay(100);
	}
}

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
  InitializeList(&list);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  setPWM_Freq(100000);


  HAL_ADC_Start(&hadc1);
  HAL_UART_Transmit_IT(&huart2, tx_buffer, sizeof(tx_buffer));

//  HAL_UART_Transmit(&huart2, greeting_list, sizeof(greeting_list), 500);
//
//  HAL_UART_Receive_IT(&huart2, &rx_buffer, sizeof(rx_buffer));

//  HAL_UART_Receive_IT(&huart2, rx_buffer, sizeof(rx_buffer));

//  	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x24, &txData, 1);
//  	HAL_I2C_Master_Receive_IT(&hi2c2, 0x24, &rxData, 1);



//  uint8_t txData = 0x66U;
//  uint8_t rxData = 0x00U;
//
  //HAL_SPI_TransmitReceive(&hspi1, &txData, &rxData, 1, HAL_MAX_DELAY);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  LedControl();

//	  LinkedListControl();



//	  HAL_ADC_PollForConversion(&hadc1, 1000);
//	  readValue = HAL_ADC_GetValue(&hadc1);
//	  setPWM_DutyCycle(readValue);
//
//	  HAL_UART_Transmit(&huart2, tx_buffer, sizeof(tx_buffer), 1000);
//	  HAL_Delay(1000);


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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  htim2.Init.Prescaler = 99;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 99;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : T_NRST_Pin */
  GPIO_InitStruct.Pin = T_NRST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(T_NRST_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */

/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
