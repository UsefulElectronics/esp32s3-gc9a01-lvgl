/**
  ******************************************************************************
  *		(c) Copyright 2012-2023; USEFUL ELECTRONICS
  *
  *	All rights reserved.  Protected by international copyright laws.
  *	Knowledge of the source code may not be used to write a similar
  *	product.  This file may only be used in accordance with a license
  *	and should not be redistributed in any way.
  *
  *****************************************************************************/

/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  wifi_connect.h
 * @author  		:  Ward Almasarani
 * @version 		:  v.1.0
 * @date    		:  Jan 2, 2023
 * @brief   		:
 *
 ******************************************************************************/

#ifndef MAIN_WIFI_CONNECT_H_
#define MAIN_WIFI_CONNECT_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "stdbool.h"
#include <stdio.h>
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/

/**
 * @brief Initialize and connect the ESP32 to a Wi-Fi network.
 *
 * This function initializes the necessary components for Wi-Fi connectivity,
 * including the Non-Volatile Storage (NVS), network interfaces, and event loop.
 * It also establishes a connection to the configured Wi-Fi network using the
 * `example_connect()` helper function provided by ESP-IDF.
 * 
 * @note Ensure that the Wi-Fi credentials are configured in `menuconfig` or
 * provided through the `example_connect()` implementation.
 * 
 * @attention This function uses blocking calls and may halt execution
 * if the configuration or connection process fails.
 */
void wifi_connect(void);
/**
 * @brief Get the IP address of the current Wi-Fi connection as a string.
 *
 * This function retrieves the IP address of the ESP32 when it is connected
 * to a Wi-Fi network. The IP address is returned as a null-terminated string.
 * 
 * The memory for the IP address string is managed internally and must not
 * be modified by the caller. If no IP address is assigned or the ESP32 is not
 * connected to a Wi-Fi network, the function returns `NULL`.
 *
 * @note Ensure that Wi-Fi is initialized and connected before calling this function.
 * 
 * @return 
 *     - A pointer to a statically allocated string containing the IP address on success.
 *     - `NULL` if the IP address cannot be retrieved.
 *
 */
char* wifi_get_connection_ip(void);
/**
 * @brief Get the current Wi-Fi connection's RSSI (signal strength).
 *
 * This function retrieves the RSSI (Received Signal Strength Indicator) value 
 * of the currently connected Wi-Fi access point. RSSI is measured in dBm.
 * 
 * @note Ensure that the ESP32 is connected to a Wi-Fi network before calling this function.
 *
 * @return 
 *     - The RSSI value in dBm if successful.
 *     - Returns undefined behavior if the ESP32 is not connected.
 */
int8_t wifi_get_rssi(void);
#endif /* MAIN_WIFI_CONNECT_H_ */


/**************************  Useful Electronics  ****************END OF FILE***/
