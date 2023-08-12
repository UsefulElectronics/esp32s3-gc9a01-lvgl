/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  button.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jul 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "button.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
//Offset state is used to handle undefined button situation
button_t hw_buttons[HARDWARE_BUTTON_COUNT + HARDWARE_BUTTON_OFFSET] = {0};
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
static uint8_t button_index_find(uint8_t pin);
/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	Initialize a button with the given pin, pull type, and long-press duration.
 *
 * 			This function initializes a button by setting up its configuration with the given parameters.
 * 			The button configuration includes the GPIO pin, pull type, and the duration required to detect a long-press.
 *
 * @param 	pin The GPIO pin number to be associated with the button.
 *
 * @param 	pull_type either pull up = 1 or pull down = 0
 *
 * @param 	long_press_time_ms The duration in milliseconds required to detect a long-press event on the button.
 */
void button_init(uint8_t pin, uint8_t pull_type, uint32_t long_press_time_ms, uint8_t* button_read, void* button_callback)
{
	static uint8_t button_index = 0;

	hw_buttons[button_index].config.pin 				= pin;

	hw_buttons[button_index].config.pull_type 			= pull_type;

	hw_buttons[button_index].config.long_press_time_ms 	= long_press_time_ms;

	hw_buttons[button_index].input_read 				= button_read;

	hw_buttons[button_index].callback 					= button_callback;

	++button_index;
}
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
bool button_debounce(uint8_t pin)
{
	bool ret = DISABLE;

	const uint16_t	start_boundry 	= 500;
	const uint16_t	end_boundry	 	= 4000;

	static uint16_t level = start_boundry;

	uint8_t button_index = 0;

	button_index = button_index_find(pin);

	if(hw_buttons[button_index].config.pull_type != gpio_get_level(hw_buttons[button_index].config.pin))
	{
		++level;
	}
	else
	{
		--level;
		if(level <= start_boundry)
		{
			level = start_boundry;
		}
	}
	if(level >= end_boundry)
	{
		level = end_boundry;
		ret = ENABLE;
	}
	return ret;
}
/**
 * @brief 	Find the index of a button configuration in the hardware button array.
 *
 * 			This function searches for the index of a button configuration in the hardware button array
 * 			based on the given GPIO pin number.
 *
 * @param 	pin The GPIO pin number of the button to find the configuration index for.
 *
 * @return 	uint8_t Returns the index of the button configuration in the hardware button array
 *          if found, or HARDWARE_BUTTON_COUNT if the button configuration is not found.
 */
static uint8_t button_index_find(uint8_t pin)
{
	uint8_t index = 0;

	for (; index < HARDWARE_BUTTON_COUNT; ++index)
	{
		if(hw_buttons[index].config.pin == pin)
		{
			break;
		}
	}
	return index;
}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
