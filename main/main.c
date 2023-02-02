/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  main.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jan 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "main.h"
#include "rotary_encoder.h"

#include "display.h"

#include "gc9a01.h"

#include "lvgl_demo_ui.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
static const char *main = "main";
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
static void main_encoder_cb(uint8_t knobPosition);
/* FUNCTION PROTOTYPES -------------------------------------------------------*/

void app_main(void)
{
	gc9a01_displayInit();

	displayConfig();

	encoder_init(main_encoder_cb);


	xTaskCreatePinnedToCore(encoder_handler_task, "encoder_handler", 10000, NULL, 4, NULL, 1);

    while (1)
    {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        vTaskDelay(pdMS_TO_TICKS(10));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
    }
}

static void main_encoder_cb(uint8_t knobPosition)
{
	static uint8_t prevPosition = 0;

	ESP_LOGI(main, "knob position: %d", knobPosition);

	set_value((int32_t) knobPosition);

	prevPosition = knobPosition;

}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
