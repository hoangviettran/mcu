/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void AnalogClock(int num);
void clearAllClock();
void clockDisplay(int hour, int min, int sec);
void singleLedDisplay(int num);
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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int hour = 0, min = 0, sec = 0;

  while (1)
  {
	  //EX6

	  /*for(int i = 1; i <= 12; i++){
		  AnalogClock(i);
		  if(i >= 12) i = 0;
		  HAL_Delay (1000);
	  }*/
	  //ex10
	  sec++;

	  if(sec >= 60){
		  sec = 0;
		  min++;
	  }
	  if(min >= 60){
		  hour++;
		  min = 0;
	  }
	  if(hour >= 24) hour = 0;
	  //display
	  clockDisplay(hour, min, sec);
	  HAL_Delay (20);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, P1_Pin|P2_Pin|P3_Pin|P4_Pin
                          |P5_Pin|P6_Pin|P7_Pin|P8_Pin
                          |P9_Pin|P10_Pin|P11_Pin|P12_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : P1_Pin P2_Pin P3_Pin P4_Pin
                           P5_Pin P6_Pin P7_Pin P8_Pin
                           P9_Pin P10_Pin P11_Pin P12_Pin */
  GPIO_InitStruct.Pin = P1_Pin|P2_Pin|P3_Pin|P4_Pin
                          |P5_Pin|P6_Pin|P7_Pin|P8_Pin
                          |P9_Pin|P10_Pin|P11_Pin|P12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void clockDisplay(int hour, int min, int sec){
	  int hourD, minD, secD;
	  if(sec%5 >= 3){
	  	  secD = sec/5+1;
	  }
	  else{
          if(sec/5 == 0) secD = 12;
  	      else secD = sec/5;
	  }
	  if(min%5 >= 3){
		  minD = min/5+1;
	  }
	  else{
  	      if(min/5 == 0) minD = 12;
	 	  else minD = min/5;
	  }
	  if(hour%12 == 0){
	  	  hourD = 12;
	  }
	  else hourD = hour%12;

	  clearAllClock();
	  singleLedDisplay(secD);
	  singleLedDisplay(minD);
	  singleLedDisplay(hourD);
}

void singleLedDisplay(int num){
	switch(num){
	case 1:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_RESET );
		break;
	case 2:
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_RESET );
		break;
	case 3:
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_RESET );
		break;
	case 4:
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_RESET );
		break;
	case 5:
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_RESET );
		break;
	case 6:
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_RESET );
		break;
	case 7:
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_RESET );
		break;
	case 8:
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_RESET );
		break;
	case 9:
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_RESET );
		break;
	case 10:
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_RESET );
		break;
	case 11:
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_RESET );
		break;
	case 12:
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_RESET );
		break;
	default:
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_RESET );
		break;
	}
}

void clearAllClock() {
	HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
	HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
}
void AnalogClock(int num){
	switch(num){
	case 1:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 2:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 3:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 4:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 5:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 6:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 7:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 8:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 9:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 10:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 11:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_RESET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_SET );
		break;
	case 12:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_RESET );
		break;
	default:
		HAL_GPIO_WritePin ( P1_GPIO_Port , P1_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P2_GPIO_Port , P2_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P3_GPIO_Port , P3_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P4_GPIO_Port , P4_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P5_GPIO_Port , P5_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P6_GPIO_Port , P6_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P7_GPIO_Port , P7_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P8_GPIO_Port , P8_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P9_GPIO_Port , P9_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P10_GPIO_Port , P10_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P11_GPIO_Port , P11_Pin ,GPIO_PIN_SET );
		HAL_GPIO_WritePin ( P12_GPIO_Port , P12_Pin ,GPIO_PIN_RESET );
		break;
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
