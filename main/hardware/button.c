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
#include "esp_log.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/
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
    bool long_press;         // Flag indicating if the button is being long-pressed
    uint8_t (*input_read)(void);
	void 	(*callback)(void);
} button_t;

// Button handler structure
typedef struct
{
    uint32_t    (*tick)(void);
    uint8_t 	(*input_read)(uint8_t gpio_pin);
} button_handler_t;
/* VARIABLES -----------------------------------------------------------------*/
//Offset state is used to handle undefined button situation
button_t 			hw_buttons[HARDWARE_BUTTON_COUNT + HARDWARE_BUTTON_OFFSET] = {0};

button_handler_t	hButton	= {0};

uint32_t* 			(button_tick)(void);

static uint8_t 		button_index = 0;

static const char* TAG = "button";
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
static uint8_t button_index_find(uint8_t pin);

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	Initialize the button driver handler
 * 
 * @param 	get_tick	: function pointer that reads and returns the system tick
 * 
 * @param 	gpio_read 	: fucntion pointer that reads and returns the state of the passed gpio pin
 */
void button_init(uint32_t* get_tick, uint8_t* gpio_read)
{
	hButton.input_read = gpio_read;

	hButton.tick = get_tick;
}
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
void button_add(uint8_t pin, uint8_t pull_type, uint32_t press_time, void* button_callback)
{	
	hw_buttons[button_index].config.pin 				= pin;

	hw_buttons[button_index].config.pull_type 			= pull_type;

	hw_buttons[button_index].config.long_press_time_ms 	= press_time;

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

	const uint16_t	start_boundary 		= 500;
	const uint16_t	end_boundary	 	= 10000;

	const uint16_t	middle_value	 	= 4000;

	static uint16_t level = middle_value;

	uint8_t button_index = 0;

	button_index = button_index_find(pin);

	while(1)
	{
		if(hw_buttons[button_index].config.pull_type != hButton.input_read(hw_buttons[button_index].config.pin))
		{
			++level;
		}
		else
		{
			--level;

			if(level <= start_boundary)
			{
				level = middle_value;

				break;
			}
		}
		if(level >= end_boundary)
		{
			level = middle_value;

			ret = ENABLE;

			hw_buttons[button_index].state 		= BUTTON_PRESSED;

			hw_buttons[button_index].press_time	= hButton.tick();

			break;
		}
	}

	return ret;
}
/**
 * @brief number of registered buttons is owned by this layer
 * 
 * @return the number of registered buttons 
 */
uint8_t button_get_count(void)
{
	return button_index;
}
/**
 * @brief initialize button handler variables content
 * 
 * @param systick 	:	system tick get function
 */
void button_manager_init(uint32_t* systick)
{
	memset(&hw_buttons ,0 ,sizeof(button_t) * HARDWARE_BUTTON_COUNT);

	button_index = 0;

	hButton.tick = systick;
}
/**
 * @brief 	Obtain the stated of the required button whether it is pressed, long pressed or double clicked.
 * 
 * @param 	pin : physical pin the button is connected to 
 * 
 * @return 	button_state_t the state of the button
 */
button_state_t button_state_get(uint8_t pin)
{
	uint8_t button_index = 0;

	button_index = button_index_find(pin);

	return hw_buttons[button_index].state;
}

/**
 * @brief Handle all button related states and callbacks 
 * 
 */
void button_manager(void)
{
	uint8_t button_count = button_get_count();

	for(uint8_t i = 0; i < button_index; ++i)
	{
		if((hw_buttons[i].state == BUTTON_PRESSED) || (hw_buttons[i].state == BUTTON_LONG_PRESSED))
		{
			if(hButton.input_read(hw_buttons[i].config.pin) == hw_buttons[i].config.pull_type)
			{
				hw_buttons[i].state 		= BUTTON_CLICKED;

				hw_buttons[i].callback();

				hw_buttons[i].state 		= BUTTON_IDLE;
			}
			else if(hButton.tick() - hw_buttons[i].press_time > hw_buttons[i].config.long_press_time_ms )
			{
				hw_buttons[i].state 		= BUTTON_LONG_PRESSED;

				hw_buttons[i].callback();

				hw_buttons[i].state 		= BUTTON_IDLE;

			}
		}

	}
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
