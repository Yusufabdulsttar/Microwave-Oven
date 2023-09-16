/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <LCD.h>
#include <keypad.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define PASS_LIMIT       3
#define SET              1
#define CLEAR            0
#define CANCEL           2

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t Door = CLEAR;
uint8_t Food_in = CLEAR;
uint8_t Start = CLEAR;
uint8_t Start_Flag = CLEAR;
uint8_t Stop  = CLEAR;
uint8_t Pause_Flage  = CLEAR;
uint8_t Cancel_Flage = CLEAR;
uint8_t Time_minutes = CLEAR;
uint8_t Time_seconds = 60;
uint8_t keypad_value = CLEAR;
uint8_t Time_check = CLEAR;
uint8_t Run_flag = CLEAR;
uint8_t count_char = CLEAR;
uint8_t char_temp = CLEAR;
uint8_t Enable_ISR = CLEAR;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

void initialization ();
uint8_t Keypad_Read_Value();
void Timer_ISR();
void Button_State();
void Set_Time();
void Start_Microwave();
void Stop_Microwave();

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

lcd_4bit_t lcd;
keypad_t keypad;

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
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim10);

  initialization();

  lcd_4bit_send_string_pos(&lcd, 2, 8, "00:00");
  /* USER CODE END 2 */

  /* Infinite loop */
  while(1){
  /* USER CODE BEGIN WHILE */
	  Button_State();
	  Timer_ISR();
		  /* Check if door is closed */
		  if (Door == HIGH){
			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
		  }
		  if (Door == LOW && Start_Flag == CLEAR){
			  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
		  }
		  /* Check if food is in microwave and door is closed */
		 if(Food_in == HIGH && Door == LOW)
		 {
		 	 /* We want to set time only once */
		 	 Set_Time();

			   /* Check the state of the start button */
			 if(Start_Flag == SET && Pause_Flage == CLEAR)
			 {
				 /* Turn on the microwave, heater, and lamb */
				 Start_Microwave();
				 Cancel_Flage = CLEAR;
			 }
		  }

	          /* Check the state of the Stop button */
	  	 if(Pause_Flage == SET)
	  	 {
	              Start_Flag = CLEAR;
	              Pause_Flage = CLEAR;
	              Stop_Microwave(); // stope the operation
	  	 }
	         /* if the stop button is pressed twice, restart the program  */
	     if (Cancel_Flage == CANCEL){
	              Stop_Microwave();
	              lcd_4bit_send_string_pos(&lcd, 2, 8, "00:00");
	              Pause_Flage = CLEAR;
	              Start_Flag = CLEAR;
	              Time_minutes = CLEAR;
	              Time_seconds = 60;
	              Cancel_Flage = CLEAR;
	              Time_check = CLEAR;
	      }

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
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

/* USER CODE BEGIN 4 */

void Button_State(){
    /* Check if there is food in the microwave */
    Food_in = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
    /* Check the status of the door */
    Door = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
    Start = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
    /* Check the status of the Start */
    if (Start == GPIO_PIN_SET){
        Start_Flag = SET;
    }
    /* Check the status of the Stop */
    Stop = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
    if(Stop == GPIO_PIN_SET){

        Pause_Flage++;
        Cancel_Flage++;
    }
}

/**
 * @brief To Set the time from (0 to 99)
 * @param void
 * @return void
 */
void Set_Time(){
    if(Time_check != 2){
    /* get input key from keypad */
    keypad_value = Keypad_Read_Value();
    /* check if the input is correct */
        if(('0' <= keypad_value) && ('9' >= keypad_value))
        {
            if (keypad_value != 0){
            /* Store the time */
            Time_minutes = (Time_minutes * 10) + (keypad_value - '0');

            /* display time*/
            if (Time_minutes <= 9){
                char_temp = keypad_value;
                lcd_4bit_send_char_data_pos(&lcd, 2, 9, char_temp);
            }
            else if(Time_minutes >= 10){
                lcd_4bit_send_char_data_pos(&lcd, 2, 9, keypad_value);
                lcd_4bit_send_char_data_pos(&lcd, 2, 8, char_temp);
            }
            ++Time_check;
            keypad_value = 0;
            }
        }
    }
}

/**
 * @brief Configure the timer to interrupt every 1 sec
 * @param void
 * @return void
 */
void Timer_ISR(){
/* If the Run_flag is 1, then the user has pressed the start button and there is food in the microwave */
/* The Enable_ISR variable is used by the timer interrupt to signal that an interrupt has occurred every 1 second, This will trigger the function every 1 second */
    if(Run_flag == SET && Enable_ISR == SET){
        /* if (Time_minutes) valid then start count the time and display it*/
        if(Time_minutes){
            Time_seconds--;
            /* display the minutes */
            count_char = '0' + ((Time_minutes-1) / 10);
            lcd_4bit_send_char_data_pos(&lcd, 2, 8, count_char);
            count_char = '0' + ((Time_minutes-1) % 10);
            lcd_4bit_send_char_data_pos(&lcd, 2, 9, count_char);

            /* display the seconds */
            count_char = '0' + (Time_seconds / 10);
            lcd_4bit_send_char_data_pos(&lcd, 2, 11, count_char);
            count_char = '0' + (Time_seconds % 10);
            lcd_4bit_send_char_data_pos(&lcd, 2, 12, count_char);

            /* A minute has passed if the seconds are 0 */
            if (Time_seconds == 0){
                Time_minutes--;
                Time_seconds = 60;
            }
            Enable_ISR = CLEAR;
        }
        /* If the minute is 0, then the time is up */
        else {
            lcd_4bit_send_string_pos(&lcd, 2, 8, "00:00");
            Start_Flag = CLEAR;
            Stop_Microwave();
            Enable_ISR = CLEAR;
        }
    }
}

/**
 * @brief This function starts the microwave, lamp, and heater
 * @param void
 * @return void
 */
void Start_Microwave(){
    /* start the heater */
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);
    /* Turn on the lamb  */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
    /* Start the microwave  */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
    /* Start the timer */
    Run_flag = 1;
}

/**
 * @brief This function stops the microwave, lamp, and heater
 * @param void
 * @return void
 */
void Stop_Microwave(){
    /* Stop the heater */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);
    /* Turn off the lamb  */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
    /* Stop the microwave  */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
    /* Stop the timer */
    Run_flag = 0;
}

/**
 * @brief This function reads the keypad
 * @param void
 * @return Keypad Value
 */
uint8_t Keypad_Read_Value()
{
    uint8_t Value;
    keypad_read(&keypad, &Value);
    return Value;
}

/**
 * @brief This function initializes the modules
 * @param void
 * @return void
 */
void initialization(){
	lcd.lcd_rs.port = GPIOD,
	lcd.lcd_rs.pin = GPIO_PIN_0,
	lcd.lcd_en.port = GPIOD,
	lcd.lcd_en.pin = GPIO_PIN_1,
	
	lcd.lcd_data[0].port = GPIOD,
	lcd.lcd_data[0].pin = GPIO_PIN_2,
	lcd.lcd_data[1].port = GPIOD,
	lcd.lcd_data[1].pin = GPIO_PIN_3,
	lcd.lcd_data[2].port = GPIOD,
	lcd.lcd_data[2].pin = GPIO_PIN_4,
	lcd.lcd_data[3].port = GPIOD,
	lcd.lcd_data[3].pin = GPIO_PIN_5;


	keypad.keypad_row[0].port = GPIOD,
	keypad.keypad_row[0].pin = GPIO_PIN_6,
	keypad.keypad_row[1].port = GPIOD,
	keypad.keypad_row[1].pin = GPIO_PIN_7,
	keypad.keypad_row[2].port = GPIOD,
	keypad.keypad_row[2].pin = GPIO_PIN_9,
	keypad.keypad_row[3].port = GPIOD,
	keypad.keypad_row[3].pin = GPIO_PIN_10,
	
	keypad.keypad_col[0].port = GPIOD,
	keypad.keypad_col[0].pin = GPIO_PIN_11,
	keypad.keypad_col[1].port = GPIOD,
	keypad.keypad_col[1].pin = GPIO_PIN_12,
	keypad.keypad_col[2].port = GPIOD,
	keypad.keypad_col[2].pin = GPIO_PIN_13,
	keypad.keypad_col[3].port = GPIOD,
	keypad.keypad_col[3].pin = GPIO_PIN_14;
	
	lcd_4bit_intialize(&lcd);
	keypad_initialize (&keypad);

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
