/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  display.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Feb 1, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_DISPLAY_H_
#define MAIN_DISPLAY_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "gc9a01.h"

#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
/* MACROS --------------------------------------------------------------------*/
#define EXAMPLE_LVGL_TICK_PERIOD_MS    2
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
extern lv_disp_drv_t disp_drv;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
bool display_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);

void displayConfig(void);
#endif /* MAIN_DISPLAY_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
