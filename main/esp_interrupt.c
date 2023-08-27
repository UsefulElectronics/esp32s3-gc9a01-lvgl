/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  esp_interrupt.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Aug 1, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "esp_interrupt.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
SemaphoreHandle_t button_sem 	= NULL;
interrupt_e interrupt_id		= IDLE_INT;
static const char* TAG = "interrupt";
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	GPIO interrupt service routine will be executed when the related interrupt is fired. this function will give
 * 			button_sem as semaphore and clear the related interrupt flags
 *
 * @param 	arg	:	pointer to the GPIO pin responsible for the interrupt.
 */
void  gpio_isr_handle(void *arg)
{
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	uint8_t gpio_idx = (uint8_t) arg;

	interrupt_id = EXT_GPIO_INT;
	//Notify callback handling task and pass callbackID
	xTaskNotifyFromISR( hMain_eventTask,		//Task handler to pass the notification to
						interrupt_id,				//CallbackID to be passed to the function
						eSetValueWithOverwrite,		//CallbackID will be cleared once the corresponding task is executed
	                    &xHigherPriorityTaskWoken);	//After noticing callback handle task, it will be executed immediately
													//regardless of its priority in the system.

	//Give priority to callback handling task to handle the callback immediately.
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
