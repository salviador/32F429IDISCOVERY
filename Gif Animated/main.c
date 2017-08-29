#include "main.h"
#include "WM.h"
#include "stm32f4xx_hal.h"


static void BSP_Config(void);
static void SystemClock_Config(void);
void BSP_Background(void);

extern GUI_CONST_STORAGE GUI_BITMAP bmf12;
extern const unsigned char _acanim[482738UL + 1];

volatile __IO uint32_t timeTEMP, timetotTEMP;

int main(void)
{  
  HAL_Init();  
  
  BSP_Config();

  SystemClock_Config();

  GUI_Init();

  WM_SetCreateFlags(WM_CF_MEMDEV);
  
  //Fine Inizializzazione

  GUI_SetBkColor(GUI_RED);
  HAL_Delay(500);
  GUI_Clear();
  GUI_SetBkColor(GUI_GREEN);
  HAL_Delay(500);
  GUI_Clear();
  GUI_SetBkColor(GUI_BLUE);
  HAL_Delay(500);
  GUI_Clear();

  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font16_ASCII);
  GUI_DispStringHCenterAt("STemWin", 45, 41);

  HAL_Delay(500);
  GUI_Clear();
  
  
 // GUI_DrawBitmap(&bmf12, 63, 0);
//GUI_GIF_Draw(&_acanim[0],482738UL,0,0);
  
GUI_GIF_INFO       GifInfo   = {0}; 
GUI_GIF_GetInfo(&_acanim[0], 482738UL, &GifInfo);  //Get GIF info structure
while(1) 
{
      for (int i = 0; i < GifInfo.NumImages; i++) {
        //
        // Draw image with index i
        //
        GUI_GIF_DrawSub(&_acanim[0], 482738UL, 0, 0, i);
        timeTEMP = HAL_GetTick();
        GUI_Delay(20);
        timetotTEMP = HAL_GetTick() - timeTEMP;
      }
}







  while(1) 
  {

  }
}

static void BSP_Config(void)
{
  /* Initialize STM32F429I-DISCO's LEDs */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  
  /* Initializes the SDRAM device */
  BSP_SDRAM_Init();
  
  /* Initialize the Touch screen */
  BSP_TS_Init(240, 320);
  
  /* Enable the CRC Module */
  __HAL_RCC_CRC_CLK_ENABLE();
}

/**
  * @brief  BSP_Background.
  * @param  None
  * @retval None
  */


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Activate the Over-Drive mode */
  HAL_PWREx_EnableOverDrive();
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
  clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

