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

/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef struct page
{
	char *title;
    void (*page_init)();
    void (*page_exit)();
    void (*page)();
    struct menuItem *sub_menu;
    struct menuItem *next_menu;
    IconDef *icon;
    uint8_t reserved : 8,

}page_t;
/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/



#endif /* UI_PAGE_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
