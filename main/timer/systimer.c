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
#include <stdint.h>
#include <stdio.h>
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

typedef struct 
{
    uint32_t duration;        		// Timer duration in ticks
    uint32_t remaining_ticks;  		// Remaining ticks
    bool 	 is_active;            	// Timer active status
    int32_t  repeat_count;			// Number of times the timer repeats (-1 for continuous)
    systimer_callback callback;   	// Function to call on expiry
} systimer_t;
/* VARIABLES -----------------------------------------------------------------*/
systimer_t systimer[SYSTIMER_MAX_TIMERS_COUNT] = {0};
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
void systimer_tick_handler(void) 
{
    for (int i = 0; i < SYSTIMER_MAX_TIMERS_COUNT; i++) 
    {
        if (systimer[i].is_active) 
        {
            if (systimer[i].remaining_ticks > 0) 
            {
                systimer[i].remaining_ticks--;
                if (systimer[i].remaining_ticks == 0) 
                {
                    //systimer[i].is_active = false;
                    if (NULL != systimer[i].callback) 
                    {
                        systimer[i].callback(); // Call the callback
                    }
                    if (systimer[i].repeat_count == 0) 
                    {
                        systimer[i].is_active = false; // Stop timer if no repeats left
                    }
                    else 
                    {
                        if (systimer[i].repeat_count > 0) 
                        {
                            systimer[i].repeat_count--; // Decrement repeat count
                        }
                        systimer[i].remaining_ticks = systimer[i].duration; // Reset timer 
                    } 
                }
            }
        }
    }
}


void systimer_init(void) 
{
    for (uint8_t i = 0; i < SYSTIMER_MAX_TIMERS_COUNT; i++) 
    {
        systimer[i].is_active 		= false;
        systimer[i].remaining_ticks = 0;
        systimer[i].duration 		= 0;
        systimer[i].repeat_count 	= 0;
        systimer[i].callback 		= NULL;
    }
}

int8_t systimer_start(uint32_t duration, int32_t repeatCount, systimer_callback callback) 
{
	// Check for an existing timer with the same properties
    for (uint8_t i = 0; i < SYSTIMER_MAX_TIMERS_COUNT; i++) {
        if (systimer[i].is_active && 
            systimer[i].duration 		== duration && 
            systimer[i].repeat_count 	== repeatCount && 
            systimer[i].callback 		== callback) 
            {
            
            // Restart the existing timer
            systimer[i].remaining_ticks = duration;
            systimer[i].is_active 		= true;
            return i; // Return the existing timer ID
        }
    }
	// Find an available timer slot
    for (int8_t i = 0; i < SYSTIMER_MAX_TIMERS_COUNT; i++) 
    {
        if (!systimer[i].is_active) 
        {
            systimer[i].duration 		= duration;
            systimer[i].remaining_ticks = duration;
            systimer[i].repeat_count 	= repeatCount;
            systimer[i].callback 		= callback;
            systimer[i].is_active 		= true;
            return i; // Return timer ID
        }
    }
    return -1; // No available timer slots
}

void systimer_stop(int8_t systimer_id)
{
	if (systimer >= 0 && systimer_id < SYSTIMER_MAX_TIMERS_COUNT) 
	{
        systimer[systimer_id].is_active = false;
    }
}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
