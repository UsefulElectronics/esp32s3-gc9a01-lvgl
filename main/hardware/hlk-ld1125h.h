/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  hlk-ld1125h.h
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jul 25, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/

#ifndef MAIN_HLK_LD1125H_H_
#define MAIN_HLK_LD1125H_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
/* MACROS --------------------------------------------------------------------*/
#define DESTINATION_PACK		"dis="

#define MOVEMENT_OCC			"occ"
#define MOVEMENT_MOV			"mov"

#define MOVEMENT_STRING_SIZE	3
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef enum
{
	occ		= 0,
	mov,
}move_type_e;
/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
/**
 * @brief Extracts the distance value from the provided packet and also identifies the packet type.
 *
 * This function extracts the distance value from the packet and identifies the packet type.
 * The packet should be in the format "packet_type, dis=distance_value", where packet_type is a string
 * representing the type of the packet, and distance_value is a floating-point value representing the distance.
 *
 * @param packet The input packet from which the distance is to be extracted.
 * @param packet_type The character array where the packet type will be stored.
 *
 * @return The extracted distance value as a number in cm, or -1 if the distance value is not found.
 *
 * @note The packet_type array should be large enough to store the packet type (e.g., "mov" or "occ") and null-terminated.
 * @note The packet should have the format "packet_type, dis=distance_value" for successful extraction.
 *
 * @code
 * char packet[] = "occ, dis=5.75";
 * char packet_type[4];
 * float distance = extract_distance(packet, packet_type);
 * printf("Received packet type: %s, Distance: %.2f\n", packet_type, distance);
 * @endcode
 */
int16_t hlk_ld1125h_parse_packet(const uint8_t* packet, uint8_t* packet_type);


#endif /* MAIN_HLK_LD1125H_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
