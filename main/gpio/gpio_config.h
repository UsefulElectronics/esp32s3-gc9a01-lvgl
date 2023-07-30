/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  gpio_config.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jul 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_GPIO_CONFIG_H_
#define MAIN_GPIO_CONFIG_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "driver/gpio.h"
#include "rom/gpio.h"
/* MACROS --------------------------------------------------------------------*/
#define GPIO_RESET		0
#define GPIO_SET		1

#define ENABLE			1
#define DISABLE			0
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/

/**
 * @brief Configures a GPIO pin as output and sets its initial level to LOW.
 *
 * @param gpio_pin The GPIO pin number to configure as output.
 */
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
void gpio_config_ext_interrupt(uint8_t gpio_pin, gpio_int_type_t interrupt_type, void* gpio_isr_function);
/**
 * @brief Configures a GPIO pin as output and sets its initial level to LOW.
 *
 * @param gpio_pin The GPIO pin number to configure as output.
 */
void gpio_config_output(uint8_t gpio_pin);
/**
 * @brief Configures a GPIO pin as input.
 *
 * @param gpio_pin The GPIO pin number to configure as input.
 */
void gpio_config_input(uint8_t gpio_pin);

#endif /* MAIN_GPIO_CONFIG_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
