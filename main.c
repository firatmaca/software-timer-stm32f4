
#include "main.h"


void SystemClock_Config(void);
static void MX_GPIO_Init(void);


#include "timer.h"

#include "stdio.h"


void blink(void);
void print(void);
void ticker(void);

timer_t blinker_timer;
timer_t printer_timer;

//TODO: call this from an ISR, like SysTick_Handler()

volatile int is_system_initialized = 0;
void SysTick_Handler(void){
 //just call the ticker()
    ticker();
	
}
void ticker(void)
{
     //do not tick until system is initialized.
    if(is_system_initialized == 0)
        return;

    timer_inc(&blinker_timer, 1); //assume, tick frequency is 1KHZ
    timer_inc(&printer_timer, 1); //same assumption
}


int main(void)
{

  HAL_Init();
	SysTick_Config(SystemCoreClock / 1000);  
  SystemClock_Config();

  
  MX_GPIO_Init();
  
 
   //TODO: MCU specific initialization


    //timer-1 is used for blinking an led...
    timer_ctor(&blinker_timer);
    timer_set_timeout(&blinker_timer, 1000);


    //timer-2 is used for printing a text
      timer_ctor(&printer_timer);
      timer_set_timeout(&printer_timer,500);

       is_system_initialized = 1;
    while(1)
    {

        //Print periodically...
        if(timer_is_timeout(&printer_timer))
        {
            print();
            timer_reset(&printer_timer);
        }        

		
        //Reset periodically
        if(timer_is_timeout(&blinker_timer))
        {
            blink();    
					timer_reset(&blinker_timer);
	
        }
			
    }

}

void print(void)
{
    printf("Hello!\r\n");
	//HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14);
}

void blink(void)
{
   HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_15);
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
 
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


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}



void Error_Handler(void)
{
 
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{ 
  
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
