/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  button.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jul 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_BUTTON_H_
#define MAIN_BUTTON_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "gpio/gpio_config.h"
#include "stdbool.h"
/* MACROS --------------------------------------------------------------------*/
#define HARDWARE_BUTTON_COUNT		1
#define HARDWARE_BUTTON_OFFSET		1

#define ENABLE			1
#define DISABLE			0
/* ENUMORATIONS --------------------------------------------------------------*/
// Button states
typedef enum
{
    BUTTON_IDLE,
    BUTTON_PRESSED,
    BUTTON_CLICKED,
    BUTTON_DOUBLE_CLICKED,
    BUTTON_LONG_PRESSED
} button_state_t;
/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
/**
 * @brief 	Initialize a button with the given pin, pull type, and long-press duration.
 *
 * 			This function initializes a button by setting up its configuration with the given parameters.
 * 			The button configuration includes the GPIO pin, pull type, and the duration required to detect a long-press.
 *
 * @param 	pin 				The GPIO pin number to be associated with the button.
 *
 * @param 	pull_type 			either pull up = 1 or pull down = 0
 *
 * @param 	long_press_time_ms 	The duration in milliseconds required to detect a long-press event on the button.
 * 
 * @param 	button_callback		The duration in milliseconds required to detect a long-press event on the button.
 */
void button_add(uint8_t pin, uint8_t pull_type, uint32_t press_time, void* button_callback);
/**
 * @brief 	Initialize the button driver handler
 * 
 * @param 	get_tick	: function pointer that reads and returns the system tick
 * 
 * @param 	gpio_read 	: fucntion pointer that reads and returns the state of the passed gpio pin
 */
void button_init(uint32_t* get_tick, uint8_t* gpio_read);
/**
 * @brief 	Perform button debounce to filter out spurious button state changes.
 *
 * 			This function performs debounce logic on the input button pin to filter out
 * 			spurious button state changes that can occur due to mechanical button bouncing.
 *
 * @param 	pin The GPIO pin number of the button to debounce.
 *
 * @return 	bool Returns ENABLE if the button state is stable (debounced) and considered valid.
 *          Returns DISABLE if the button state is still unstable due to bouncing.
 *
 * @note The debounce logic maintains an internal level variable to track the stability
 *       of the button state. The debounce time is determined by the start_boundry and end_boundry
 *       constants defined within the function. Adjust these constants based on the desired debounce duration.
 *       The function uses the provided tick_value to track the time elapsed since the button state change.
 *       To debounce multiple buttons, use a separate instance of this function for each button with its pin number.
 */
bool button_debounce(uint8_t pin);
/**
 * @brief 	Obtain the stated of the required button whether it is pressed, long pressed or double clicked.
 * 
 * @param 	pin : physical pin the button is connected to 
 * 
 * @return 	button_state_t the state of the button
 */
button_state_t button_state_get(uint8_t pin);
/**
 * @brief Handle all button related states and callbacks 
 * 
 */
void button_manager(void);

//Button action click double click long press


#endif /* MAIN_BUTTON_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
