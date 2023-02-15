/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  sntp.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Feb 15, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_SNTP_H_
#define MAIN_SNTP_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "time.h"
#include "lwip/ip_addr.h"
#include "lwip/sockets.h"
#include "esp_sntp.h"
#include "esp_log.h"
/* MACROS --------------------------------------------------------------------*/

/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void sntp_time_get(struct tm* timeinfo);
void sntp_config(void);


#endif /* MAIN_SNTP_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
