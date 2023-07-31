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
void button_init(uint8_t pin, uint32_t debounce_time_ms, uint32_t long_press_time_ms);

void button_update(uint32_t tick_value);

bool button_debounce(uint32_t tick_value, uint8_t pin);
//button debounce

//Button action click double click long press


#endif /* MAIN_BUTTON_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
