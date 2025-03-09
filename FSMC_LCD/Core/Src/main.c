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
#include "tim.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "ili9341.h"
#include "XPT2046_touch.h"

#include "lvgl.h"                // ��Ϊ����LVGL�ṩ�˸�������ͷ�ļ�����
#include "lv_port_disp_template.h"        // LVGL����ʾ֧��
#include "lv_port_indev_template.h"

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

lv_obj_t *myLabel=NULL;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

static void myBtn_event(lv_event_t *event);

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
  MX_FSMC_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */

//  lcdInit();
//  XPT2046_Init();

  HAL_TIM_Base_Start_IT(&htim7);

  HAL_Delay(100);

  lv_init();                             // LVGL ��ʼ��
  lv_port_disp_init();                   // ע��LVGL����ʾ����
  lv_port_indev_init();                  // ע��LVGL�Ĵ����������

//  lcdTest();

    // ��ť
  lv_obj_t *myBtn = lv_btn_create(lv_scr_act());                               // ������ť; �����󣺵�ǰ���Ļ
  lv_obj_set_pos(myBtn, 10, 10);                                               // ��������
  lv_obj_set_size(myBtn, 100, 50);                                             // ���ô�С
  lv_obj_add_event_cb(myBtn, myBtn_event, LV_EVENT_CLICKED, NULL);
//  lv_obj_center(myBtn);

      // ��ť
//    lv_obj_t *myBtn = lv_btn_create(lv_scr_act());                               // ������ť; �����󣺵�ǰ���Ļ
//    lv_obj_set_pos(myBtn, 50, 50);                                               // ��������
//    lv_obj_set_size(myBtn, 100, 150);                                             // ���ô�С
   
    // ��ť�ϵ��ı�
    lv_obj_t *label_btn = lv_label_create(myBtn);                                // �����ı���ǩ�������������btn��ť
    lv_obj_align(label_btn, LV_ALIGN_LEFT_MID, 0, 0);                              // �����ڣ�������
    lv_label_set_text(label_btn, "Test");                                        // ���ñ�ǩ���ı�
//		lv_obj_set_size(label_btn, 100, 150);
    // �����ı�ǩ
    myLabel = lv_label_create(lv_scr_act());                           // �����ı���ǩ; �����󣺵�ǰ���Ļ
    lv_label_set_text(myLabel, "Hello world!");                                  // ���ñ�ǩ���ı�
//    lv_obj_align(myLabel, LV_ALIGN_CENTER, 0, 0);                                // �����ڣ�������
//    lv_obj_align_to(myBtn, myLabel, LV_ALIGN_OUT_TOP_MID, 0, -20);               // �����ڣ�ĳ����
    lv_obj_set_pos(myLabel, 100, 120);                                               // ��������
    lv_obj_set_size(myLabel, 50, 70);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    lv_timer_handler();
//    HAL_Delay(5);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

// ��ť���¼��ص�����
static void myBtn_event(lv_event_t *event)
{
    lv_obj_t *btn = lv_event_get_target(event);                    // ��õ�������ص������Ķ���
    lv_event_code_t code = lv_event_get_code(event);
    if (code == LV_EVENT_CLICKED)
    {
        static uint8_t cnt = 0;
        cnt++;
        lv_obj_t *label = lv_obj_get_child(btn, NULL);             // ��ȡ��1���Ӷ���(���������ʱ���Ѱ��������ĵ�1���Ӷ�����һ��label����)
        lv_label_set_text_fmt(label, "Button: %d", cnt);           // ���ñ�ǩ���ı���д������printf
        lv_label_set_text_fmt(myLabel, "Hello world A %d! ", cnt);
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
