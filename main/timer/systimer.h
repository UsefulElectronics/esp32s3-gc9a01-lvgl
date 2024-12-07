/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  systimer.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Dec 5, 2024
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_TIMER_SYSTIMER_H_
#define MAIN_TIMER_SYSTIMER_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
/* MACROS --------------------------------------------------------------------*/
#define SYSTIMER_MAX_TIMERS_COUNT 	10
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef void (*systimer_callback)(void);
/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
/**
 * @brief System timer tick handler.
 *
 * This function is called periodically by the system tick. It decrements the remaining ticks 
 * for each active timer, executes the callback function if a timer expires, and handles 
 * repeating timers based on their repeat count.

 * Timers with a repeat count of `-1` will continue to reset indefinitely, making them 
 * continuous timers.
 *
 * @note This function must be called in a time-critical context, such as from a tick interrupt 
 * or a high-priority task.
 */
void systimer_tick_handler(void);
/**
 * @brief Initializes the system timer module.
 *
 * This function resets all system timers to their default inactive state. 
 * It ensures that all timers are deactivated, their remaining ticks and durations are set to zero, 
 * repeat counts are cleared, and their callback functions are set to NULL.
 * This function should be called during system initialization before any timers are used.
 */
void systimer_init(void);
/**
 * @brief Starts a system timer with the specified configuration.
 *
 * This function starts a timer with the given `duration`, `repeatCount`, and `callback`. 
 * If a timer with the same configuration (duration, repeat count, and callback) already exists, 
 * it restarts the existing timer instead of creating a new one. 
 * If no available slots exist for a new timer, the function returns an error.
 *
 * @param[in] duration     The duration of the timer in ticks.
 * @param[in] repeatCount  The number of times the timer should repeat:
 *                         - `> 0`: Number of repetitions.
 *                         - `0`: One-shot timer (runs once).
 *                         - `-1`: Continuous timer (repeats indefinitely).
 * @param[in] callback     The function to be called when the timer expires.
 *
 * @return int8_t          The ID of the started or restarted timer:
 *                         - `>= 0`: Timer ID (valid index in the timer array).
 *                         - `-1`: No available timer slots or an error occurred.
 */
int8_t systimer_start(uint32_t duration, int32_t repeatCount, systimer_callback callback);
/**
 * @brief Stops an active system timer.
 *
 * This function deactivates the specified timer by its ID, preventing it from 
 * triggering further callbacks. The timer's configuration remains intact and 
 * can be restarted using its ID.
 *
 * @param[in] systimer_id  The ID of the timer to stop. Must be a valid ID 
 *                         within the range [0, SYSTIMER_MAX_TIMERS_COUNT - 1].
 */
void systimer_stop(int8_t systimer_id);


#endif /* MAIN_TIMER_SYSTIMER_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
