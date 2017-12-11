/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "retarget.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART6_UART_Init(void);

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
	 MX_USART6_UART_Init();
	 HAL_GPIO_WritePin(STAT1_GPIO_Port, STAT1_Pin, GPIO_PIN_SET);
	 /* USER CODE BEGIN 2 */
	 RetargetInit(&huart6);
//	 HAL_UART_Transmit(&huart6, (uint8_t *) "HolaMundo", 9, HAL_MAX_DELAY);
	 printf("\r\n Hola Mundo %0.2f\r\n", 2.3f);
	 /* USER CODE END 2 */

	 /* Infinite loop */
	 /* USER CODE BEGIN WHILE */
	 while (1)
	 {
		  /* USER CODE END WHILE */
		  HAL_GPIO_TogglePin(STAT1_GPIO_Port, STAT1_Pin);
		  HAL_Delay(1000);
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

	 /**Configure the main internal regulator output voltage
	  */
	 __HAL_RCC_PWR_CLK_ENABLE()
	 ;

	 __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	 /**Initializes the CPU, AHB and APB busses clocks
	  */
	 RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	 RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	 RCC_OscInitStruct.HSICalibrationValue = 16;
	 RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	 if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	 {
		  _Error_Handler(__FILE__, __LINE__);
	 }

	 /**Initializes the CPU, AHB and APB busses clocks
	  */
	 RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
				| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	 RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	 RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	 RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	 RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	 if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	 {
		  _Error_Handler(__FILE__, __LINE__);
	 }

	 /**Configure the Systick interrupt time
	  */
	 HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	 /**Configure the Systick
	  */
	 HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	 /* SysTick_IRQn interrupt configuration */
	 HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART6 init function */
static void MX_USART6_UART_Init(void)
{

	 huart6.Instance = USART6;
	 huart6.Init.BaudRate = 9600;
	 huart6.Init.WordLength = UART_WORDLENGTH_8B;
	 huart6.Init.StopBits = UART_STOPBITS_1;
	 huart6.Init.Parity = UART_PARITY_NONE;
	 huart6.Init.Mode = UART_MODE_TX_RX;
	 huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	 huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	 if (HAL_UART_Init(&huart6) != HAL_OK)
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
	 __HAL_RCC_GPIOF_CLK_ENABLE()
	 ;
	 __HAL_RCC_GPIOC_CLK_ENABLE()
	 ;
	 __HAL_RCC_GPIOA_CLK_ENABLE()
	 ;

	 /*Configure GPIO pin Output Level */
	 HAL_GPIO_WritePin(STAT1_GPIO_Port, STAT1_Pin, GPIO_PIN_RESET);

	 /*Configure GPIO pin : STAT1_Pin */
	 GPIO_InitStruct.Pin = STAT1_Pin;
	 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	 HAL_GPIO_Init(STAT1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char * file, int line)
{
	 /* USER CODE BEGIN Error_Handler_Debug */
	 /* User can add his own implementation to report the HAL error return state */
	 while (1)
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

// ----------------------------------------------------------------------------

