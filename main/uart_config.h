
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  uart.h
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 5, 2022
 * @brief   		:
 *
 ******************************************************************************/

#ifndef MAIN_UART_CONFIG_H_
#define MAIN_UART_CONFIG_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "driver/gpio.h"
/* MACROS --------------------------------------------------------------------*/
#define TXD_PIN 			(GPIO_NUM_10)
#define RXD_PIN 			(GPIO_NUM_9)

#define UART_AT_PORT 		UART_NUM_1
#define PATTERN_AT_COUNT    2

#define RX_BUF_SIZE			1024
#define TX_BUF_SIZE			1024


/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef struct
{
	uint8_t uart_rxBuffer[RX_BUF_SIZE];
	uint8_t uart_txBuffer[TX_BUF_SIZE];
	uint8_t uart_rxPacketSize;
	uint8_t uart_txPacketSize;
	union
	{
		uint8_t all;
		struct
		{
			uint8_t reserved		:7,
					rxPacket		:1;
		}flags;
	}uart_status;
}uartHandler_t;
/* VARIABLES -----------------------------------------------------------------*/
extern QueueHandle_t 		uartRxStore_queue;
extern SemaphoreHandle_t	UART_RXsem;
extern QueueHandle_t 		uartTx_queue;
extern uartHandler_t	 	hUart;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void 	uartBufferInit			(void);
uint8_t uartGetRxBuffer			(uint8_t* buffer);
uint8_t uartCheckPacketRxFlag	(void);
void 	uartResetPacketRxFlag	(void);
void 	uart_config				(void);
void 	uart_event_task			(void *pvParameters);
void 	uart_transmission_task	(void *pvParameters);


#endif /* MAIN_UART_CONFIG_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
