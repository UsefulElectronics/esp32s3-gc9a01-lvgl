/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  ui_page.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Nov 19, 2024
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "ui_page.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
ui_option_t option_watch = 
{
	.title = "Time",
	.actions = &(ui_action_t){.forward = NULL, .back = NULL, .idle = NULL },
	.next_option = &option_measure,
	.sub_option = NULL,
	.icon = NULL,
};

ui_option_t option_measure = 
{
	.title = "Time",
	.actions = &(ui_action_t){.forward = NULL, .back = NULL, .idle = NULL },
	.next_option = &option_temperature,
	.sub_option = NULL,
	.icon = NULL,
};

ui_option_t option_temperature = 
{
	.title = "Time",
	.actions = &(ui_action_t){.forward = NULL, .back = NULL, .idle = NULL },
	.next_option = &option_weather,
	.sub_option = NULL,
	.icon = NULL,
};

ui_option_t option_weather = 
{
	.title = "Time",
	.actions = &(ui_action_t){.forward = NULL, .back = NULL, .idle = NULL },
	.next_option = &option_lamp1,
	.sub_option = NULL,
	.icon = NULL,
};

ui_option_t option_lamp1 = 
{
	.title = "Time",
	.actions = &(ui_action_t){.forward = NULL, .back = NULL, .idle = NULL },
	.next_option = &option_lamp2,
	.sub_option = NULL,
	.icon = NULL,
};

ui_option_t option_lamp2 = 
{
	.title = "Time",
	.actions = &(ui_action_t){.forward = NULL, .back = NULL, .idle = NULL },
	.next_option = NULL,
	.sub_option = NULL,
	.icon = NULL,
};
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/


/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
