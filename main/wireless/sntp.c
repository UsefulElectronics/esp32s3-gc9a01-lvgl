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

	// Set timezone to Turkey Standard Time
	setenv("TZ", "UTC-3", 1);
	tzset();
	char buff[INET6_ADDRSTRLEN];

	sntp_setoperatingmode(SNTP_OPMODE_POLL);
	sntp_setservername(0, "pool.ntp.org");
	ip_addr_t const *ip = sntp_getserver(0);
	ipaddr_ntoa_r(ip, buff, INET6_ADDRSTRLEN);

	sntp_init();



}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
