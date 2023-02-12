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

/**************************  Useful Electronics  ****************END OF FILE***/
