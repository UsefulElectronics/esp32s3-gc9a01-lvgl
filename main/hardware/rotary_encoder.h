/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  rotary_encoder.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jan 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_ROTARY_ENCODER_H_
#define MAIN_ROTARY_ENCODER_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/pulse_cnt.h"
#include "driver/gpio.h"
/* MACROS --------------------------------------------------------------------*/


#define ENCODER_MAX_WHATCHPIONT_COINT 100

#define EXAMPLE_PCNT_HIGH_LIMIT 50
#define EXAMPLE_PCNT_LOW_LIMIT  -50

#define EXAMPLE_EC11_GPIO_A 9
#define EXAMPLE_EC11_GPIO_B 10
#define KNOB_BUTTON 6//13
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void encoder_init(void* callback);

void encoder_handler_task(void *param);


#endif /* MAIN_ROTARY_ENCODER_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
