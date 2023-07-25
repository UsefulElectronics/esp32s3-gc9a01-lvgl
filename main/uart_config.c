
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  uart.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 5, 2022
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "uart_config.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
QueueHandle_t uartRx_queue;
QueueHandle_t uartRxStore_queue;
QueueHandle_t uartTx_queue;
SemaphoreHandle_t UART_RXsem 	  		= NULL;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
const char *UART_DEBUG = "UART";
uartHandler_t hUart;
/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief initialize UART handler
 *
 */
void uartBufferInit(void)
{
	memset(&hUart, 0,sizeof(uartHandler_t));
}
/**
 * @brief	Get a copy from the received data over UART
 *
 * @param 	buffer :	Pointer to the UART RX buffer
 *
 * @return	The size of the received packet
 */
uint8_t uartGetRxBuffer(uint8_t* buffer)
{
	memcpy(buffer, hUart.uart_rxBuffer, hUart.uart_rxPacketSize);

	return hUart.uart_rxPacketSize;
}
/**
 * @brief check if a new packet has been received
 *
 * @return packet reception status flag
 */
uint8_t uartCheckPacketRxFlag(void)
{
	return hUart.uart_status.flags.rxPacket;
}
/**
 * @brief reset packet reception flag
 *
 */
void uartResetPacketRxFlag(void)
{
	hUart.uart_status.flags.rxPacket = 0;
}
/**
 * @brief Configure UART peripheral of ESP32
 *
 */
void uart_config(void)
{
    const uart_config_t uart_config =
    {
    	//TODO								//Baud rate must be set to 115200 for PingPong Example
        .baud_rate  = 115200,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_AT_PORT, RX_BUF_SIZE * 2, TX_BUF_SIZE * 2, 20, &uartRx_queue, 0);
    uart_param_config(UART_AT_PORT, &uart_config);
    uart_set_pin(UART_AT_PORT, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    //Set uart pattern detect function.
//    uart_enable_pattern_det_baud_intr(UART_AT_PORT, '\n', PATTERN_AT_COUNT, 2, 0, 0);
    //Reset the pattern queue length to record at most 20 pattern positions.
//    uart_pattern_queue_reset(UART_AT_PORT, 100);

    uartBufferInit();

    uartTx_queue 		= xQueueCreate(10, sizeof(uartHandler_t));
    uartRxStore_queue  	= xQueueCreate(10, sizeof(uartHandler_t));
}
/**
 * @brief UART TX function. The transmission starts once the related queue is filled.
 *
 * @param pvParameters
 */
void uart_transmission_task(void *pvParameters)
{
	int dataTransmitted = 0;
	while(1)
	{
		if(xQueueReceive(uartTx_queue, (void *)&hUart, portMAX_DELAY))
		{

			dataTransmitted = uart_write_bytes(UART_AT_PORT, hUart.uart_txBuffer, hUart.uart_txPacketSize);

			vTaskDelay(150/portTICK_PERIOD_MS);
		}
	}
}


/**
 * @brief UART event task. Here UART RX callback takes place. This task should be started in the main
 *
 * @param pvParameters
 */
void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    uint8_t* dtmp = (uint8_t*) malloc(RX_BUF_SIZE);
    UART_RXsem = xSemaphoreCreateCounting( 10, 0 );;
    for(;;)
    {
        //Waiting for UART event.
        if(xQueueReceive(uartRx_queue, (void * )&event, portMAX_DELAY))
        {
            bzero(dtmp, RX_BUF_SIZE);

            switch(event.type)
            {
                //Event of UART receving data
            case UART_DATA:
//                	ESP_LOGI(UART_DEBUG, "%d", event.size);
            		uart_read_bytes(UART_AT_PORT, hUart.uart_rxBuffer, event.size, portMAX_DELAY);

                    hUart.uart_rxPacketSize = event.size;

                    hUart.uart_status.flags.rxPacket = 1;

                    xQueueSendToBack(uartRxStore_queue, &hUart, portMAX_DELAY);

//                    xSemaphoreGive(UART_RXsem);

//                    memset(&hUart, 0, sizeof(uartHandler_t));
                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(UART_DEBUG, "hw fifo overflow");
                    // If fifo overflow happened, you should consider adding flow control for your application.
                    // The ISR has already reset the rx FIFO,
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(UART_AT_PORT);
                    xQueueReset(uartRx_queue);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(UART_DEBUG, "ring buffer full");
                    // If buffer full happened, you should consider encreasing your buffer size
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(UART_AT_PORT);
                    xQueueReset(uartRx_queue);
                    break;

                //UART_PATTERN_DET
                case UART_PATTERN_DET:
                    uart_get_buffered_data_len(UART_AT_PORT, &buffered_size);
                    int pos = uart_pattern_pop_pos(UART_AT_PORT);
                    ESP_LOGI(UART_DEBUG, "[UART PATTERN DETECTED] pos: %d, buffered size: %d", pos, buffered_size);
                    if (pos == -1) {
                        // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
                        // record the position. We should set a larger queue size.
                        // As an example, we directly flush the rx buffer here.
                        uart_flush_input(UART_AT_PORT);
                    } else {
                        uart_read_bytes(UART_AT_PORT, dtmp, pos, 100 / portTICK_PERIOD_MS);
                        uint8_t pat[PATTERN_AT_COUNT + 1];
                        memset(pat, 0, sizeof(pat));
                        uart_read_bytes(UART_AT_PORT, pat, PATTERN_AT_COUNT, 100 / portTICK_PERIOD_MS);
                        ESP_LOGI(UART_DEBUG, "read data: %s", dtmp);
                        ESP_LOGI(UART_DEBUG, "read pat : %s", pat);
                    }
                    break;
                //Others
                default:
                    ESP_LOGI(UART_DEBUG, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

/**************************  Useful Electronics  ****************END OF FILE***/
