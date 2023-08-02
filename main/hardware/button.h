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
#include <stdbool.h>
#include "gpio/gpio_config.h"
#include "stdbool.h"
/* MACROS --------------------------------------------------------------------*/
#define HARDWARE_BUTTON_COUNT		1
#define HARDWARE_BUTTON_OFFSET		1
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
// Button configuration structure
typedef struct
{
    uint8_t pin;                // GPIO pin number for the button
    uint8_t pull_type;          // pull type either pull up = 1 or pull down = 0
    uint32_t long_press_time_ms; // Long press duration in milliseconds
} button_config_t;

// Button object structure
typedef struct
{
    button_config_t config;     // Button configuration
    button_state_t state;       // Current button state
    uint32_t press_time;        // Timestamp when the button was pressed
    bool is_long_press;         // Flag indicating if the button is being long-pressed
    // Add any additional data members you might need here
} button_t;
/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
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
void button_init(uint8_t pin, uint8_t pull_type, uint32_t long_press_time_ms);
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



//Button action click double click long press


#endif /* MAIN_BUTTON_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
