/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  ui_page.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Nov 19, 2024
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef UI_PAGE_H_
#define UI_PAGE_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
/* MACROS --------------------------------------------------------------------*/
#define OPTION_BUFFER_SIZE		30
/* ENUMORATIONS --------------------------------------------------------------*/
enum
{
	UI_PAGE_OPTION_WATCH = 0,
	UI_PAGE_OPTION_MEASURE,
	UI_PAGE_OPTION_TEMPERATURE,
	UI_PAGE_OPTION_WEATHER,
	UI_PAGE_OPTION_LAMP1,
	UI_PAGE_OPTION_LAMP2,
};
/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef struct action
{
	void (*forward)();
    void (*back)();
    void (*idle)();
}ui_action_t;

typedef struct option
{
	char *title;
	struct option *sub_option;
    struct option *next_option;
    ui_action_t *actions;
	uint8_t buffer[OPTION_BUFFER_SIZE];
    void *icon;
    uint8_t reserved : 8;

}ui_option_t;
/* VARIABLES -----------------------------------------------------------------*/
ui_option_t option_watch;
ui_option_t option_measure;
ui_option_t option_temperature;
ui_option_t option_weather;
ui_option_t option_lamp1;
ui_option_t option_lamp2;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/



#endif /* UI_PAGE_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
