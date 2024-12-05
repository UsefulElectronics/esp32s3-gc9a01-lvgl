/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  systimer.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Dec 5, 2024
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "systimer.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/
typedef void (*systimer_callback)(void);

typedef struct {
    uint32_t duration;        		// Timer duration in ticks
    uint32_t remainingTicks;  		// Remaining ticks
    bool 	isActive;            	// Timer active status
    systimer_callback callback;   	// Function to call on expiry
} SoftwareTimer;
/* VARIABLES -----------------------------------------------------------------*/

/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/


/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
