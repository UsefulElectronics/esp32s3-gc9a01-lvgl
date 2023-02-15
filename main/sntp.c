/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  sntp.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Feb 15, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "sntp.h"
//#include "esp_netif_sntp.h
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
static const char *sntp = "sntp";
static time_t now;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
void sntp_time_get(struct tm* timeinfo)
{
	time(&now);

	localtime_r(&now, timeinfo);

//   sntp_set_sync_status(SNTP_SYNC_STATUS_COMPLETED);
}

void sntp_config(void)
{
    int retry = 0;
    const int retry_count = 15;

    time(&now);

	// Set timezone to China Standard Time
	setenv("TZ", "UTC+3", 1);
	tzset();
	char buff[INET6_ADDRSTRLEN];
//	ip_addr_t addr;
	sntp_setoperatingmode(SNTP_OPMODE_POLL);
	sntp_setservername(0, "pool.ntp.org");
	ip_addr_t const *ip = sntp_getserver(0);
	ipaddr_ntoa_r(ip, buff, INET6_ADDRSTRLEN);
//	inet_pton(AF_INET, "pool.ntp.org",&addr);
//	sntp_setserver(0,&addr);
	sntp_init();

//    if (sntp_get_sync_mode() == SNTP_SYNC_MODE_SMOOTH)
//    {
//        struct timeval outdelta;
//        while (sntp_get_sync_status() == SNTP_SYNC_STATUS_IN_PROGRESS)
//        {
//            adjtime(NULL, &outdelta);
//            ESP_LOGI(sntp, "Waiting for adjusting time ... outdelta = %jd sec: %li ms: %li us",
//                        (intmax_t)outdelta.tv_sec,
//                        outdelta.tv_usec/1000,
//                        outdelta.tv_usec%1000);
//            vTaskDelay(2000 / portTICK_PERIOD_MS);
//        }
//    }

//    while (esp_netif_sntp_sync_wait(2000 / portTICK_PERIOD_MS) == ESP_ERR_TIMEOUT && ++retry < retry_count)
//    {
//        ESP_LOGI(sntp, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
//    }


}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
