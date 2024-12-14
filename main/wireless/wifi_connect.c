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
 * @file    		:  wifi_connect.c
 * @author  		:  Ward Almasarani
 * @version 		:  v.1.0
 * @date    		:  Jan 2, 2023
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "wifi_connect.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
static const char* TAG = "WiFi";

uint8_t wifi_memory[50] = {0};
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
void wifi_connect(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
}

bool wifi_is_connected(void)
{
	wifi_ap_record_t ap_info;
	
	esp_err_t err = esp_wifi_sta_get_ap_info(&ap_info);

	if (err == ESP_OK) 
	{
  		return true;
	} 
	else if (err == ESP_ERR_WIFI_NOT_CONNECT) 
	{
	    return false;
	}
	 return false;
}

int8_t wifi_get_rssi(void)
{
	wifi_ap_record_t ap_info;
	
	esp_wifi_sta_get_ap_info(&ap_info);
	
	return ap_info.rssi;
}
char* wifi_get_connection_ip(void)
{
	// Get the default Wi-Fi station interface
    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    if (!netif) 
    {
        return NULL;
    }
	// Retrieve the IP information
    esp_netif_ip_info_t ip_info;
    if (esp_netif_get_ip_info(netif, &ip_info) == ESP_OK) 
    {
        if (ip_info.ip.addr) 
        {
			// Clear wifi layer related memory
			memset(wifi_memory, 0, sizeof(wifi_memory));
			// Format the IP as a string
			sprintf((char*)wifi_memory,  IPSTR, IP2STR(&ip_info.ip));  
			
			return (char*)wifi_memory;

        } 
        else 
        {
            ESP_LOGI(TAG, "No IP address assigned yet");
        }
    }
    else 
    {
        ESP_LOGI(TAG, "Failed to get IP info");
    }
    return NULL;
}

/**************************  Useful Electronics  ****************END OF FILE***/
