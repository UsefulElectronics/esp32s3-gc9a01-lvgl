/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  gpio_config.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jul 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "gpio_config.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	Configures an external interrupt for a specific GPIO pin.
 *
 * 			This function configures an external interrupt for a specific GPIO pin
 * 			on the ESP32 microcontroller.
 *
 * @param 	gpio_pin The GPIO pin number to configure for the external interrupt.
 *
 * @param 	interrupt_type The type of interrupt triggering (rising edge, falling edge, etc.).
 *
 * @param 	gpio_isr_function A pointer to the user-defined ISR (Interrupt Service Routine) function
 *                          that will be called when the interrupt is triggered.
 *
 */
void gpio_config_ext_interrupt(uint8_t gpio_pin, gpio_int_type_t interrupt_type, void* gpio_isr_function)
{
	gpio_config_t gpio_handler;

	gpio_handler.intr_type = interrupt_type;

	gpio_handler.mode = GPIO_MODE_INPUT;

	gpio_handler.pin_bit_mask = 1 << gpio_pin;

	gpio_handler.pull_down_en = GPIO_PULLDOWN_DISABLE;

	gpio_handler.pull_up_en = GPIO_PULLUP_DISABLE;

	gpio_config(&gpio_config);

	gpio_install_isr_service(ESP_INTR_FLAG_LEVEL2);

	gpio_isr_handler_add(gpio_pin, gpio_isr_function, (void*) gpio_pin);
}
/**
 * @brief Configures a GPIO pin as output and sets its initial level to LOW.
 *
 * @param gpio_pin The GPIO pin number to configure as output.
 */
void gpio_config_output(uint8_t gpio_pin)
{
	gpio_pad_select_gpio(gpio_pin);

	gpio_set_direction(gpio_pin, GPIO_MODE_OUTPUT);

	gpio_set_level(gpio_pin, GPIO_RESET);
}
/**
 * @brief Configures a GPIO pin as input.
 *
 * @param gpio_pin The GPIO pin number to configure as input.
 */
void gpio_config_input(uint8_t gpio_pin)
{
	gpio_pad_select_gpio(gpio_pin);

	gpio_set_direction(gpio_pin, GPIO_MODE_INPUT);
}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
