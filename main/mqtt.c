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
 * @file    		:  mqtt.c
 * @author  		:  Ward Almasarani
 * @version 		:  v.1.0
 * @date    		:  Jan 2, 2023
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "mqtt.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
static const char *TAG = "MQTT";

QueueHandle_t mqttSubscribe_queue;

mqtt_buffer_t mqttSubscribeBuffer;

static esp_mqtt_client_handle_t mqttClient = {0};
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 *
 * @param base Event base for the handler(always MQTT Base in this example).
 *
 * @param event_id The id for the received event.
 *
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGI(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, (int)event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg = 0;
    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        //Topics subscription is done after successful broker connection callback
        mqttSubscribeBuffer.eventType = MQTT_BROKER_CONNECT;

        xQueueSendToBack(mqttSubscribe_queue, (void *)&mqttSubscribeBuffer, portMAX_DELAY);
        esp_mqtt_client_subscribe(client, MQTT_TEMPERATURE_TOPIC, 0);
//
//        esp_mqtt_client_subscribe(client, MQTT_COLOR_TOPIC, 0);
//
//        esp_mqtt_client_subscribe(client, MQTT_MODE_TOPIC, 0);
//
//        esp_mqtt_client_subscribe(client, MQTT_FREQUENCY_TOPIC, 0);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");

        mqttSubscribeBuffer.eventType = MQTT_BROKER_DISCONNECT;

        xQueueSendToBack(mqttSubscribe_queue, (void *)&mqttSubscribeBuffer, portMAX_DELAY);

        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);

        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");

        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);

        printf("DATA=%.*s\r\n", event->data_len, event->data);


        mqttSubscribeBuffer.msgLength = event->data_len;

        strcpy(mqttSubscribeBuffer.topicString ,event->topic);

        memcpy(mqttSubscribeBuffer.data, event->data, event->data_len);

        mqttSubscribeBuffer.eventType = MQTT_TOPIC_DATA_RX;

        xQueueSendToBack(mqttSubscribe_queue, (void *)&mqttSubscribeBuffer, portMAX_DELAY);




        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");

        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    //Clear MQTT buffer
    memset(&mqttSubscribeBuffer, 0, sizeof(mqtt_buffer_t));
}
/**
 * @brief Publish data to a specific topic over MQTT
 *
 * @param topic	:	to publish data to
 *
 * @param data	:	pointer to the data to be sent
 *
 * @param len	:	number of bytes to be sent over publish request
 */
void mqtt_publish(const char *topic, const char *data, int len)
{
	const uint8_t quelityOfServiceLevel = 0;
	const uint8_t retainFeature        	= false;

	esp_mqtt_client_publish(mqttClient, topic, data, len, (int) quelityOfServiceLevel, (int) retainFeature);
}
/**
 * @brief Start MQTT broker connection and register MQTT related events callback
 *
 */
void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg =
    {
        .broker.address.uri = "mqtt://192.168.1.104:1990",
    };

    mqttSubscribe_queue = xQueueCreate(10, sizeof(mqtt_buffer_t));

    memset(&mqttSubscribeBuffer, 0, sizeof(mqtt_buffer_t));

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);

    memcpy(&mqttClient, &client, sizeof(esp_mqtt_client_handle_t));
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);

    esp_mqtt_client_start(client);


}

/**************************  Useful Electronics  ****************END OF FILE***/
