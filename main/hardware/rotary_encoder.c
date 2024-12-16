/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  rotary_encoder.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Jan 30, 2023
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "rotary_encoder.h"
#include "stdbool.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/
typedef struct
{
	uint32_t eventCount;
	QueueHandle_t queue;
	void (*callback)(uint32_t encoderValue);
}encoder_handler_t;
/* VARIABLES -----------------------------------------------------------------*/
static const char *encoder = "encoder";

static pcnt_unit_handle_t pcnt_unit = NULL;

encoder_handler_t hEncoder = {0};

/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
static bool pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx);

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
static bool pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx)
{
    BaseType_t high_task_wakeup;
    QueueHandle_t queue = (QueueHandle_t)user_ctx;
    // send event data to queue, from this interrupt callback
    xQueueSendFromISR(queue, &(edata->watch_point_value), &high_task_wakeup);
    return (high_task_wakeup == pdTRUE);
}
/**
 * @brief This tatsk will read the encoder position value every 250ms
 *
 */
void encoder_handler_task(void *param)
{
	static int pulse_count = 5000;

	int static prev_pulse_count = 0;

	const uint8_t pulse_offest = 50;

	const uint8_t rotary_step = 4;

	bool encoder_direction = 0;

	static bool negative_pulse_falg = false;



    while (1)
    {

        pcnt_unit_get_count(pcnt_unit, &pulse_count);
             

        if(pulse_count < -1  || (negative_pulse_falg == true && pulse_count == 0))
        {
        	negative_pulse_falg = true;
        }
        else
        {
        	negative_pulse_falg = false;
        }

        pulse_count = pulse_count > 0 ? pulse_count : pulse_count * -1;

        if((pulse_count - prev_pulse_count >= rotary_step) || (pulse_count - prev_pulse_count <= rotary_step * -1))
        {

        	if(negative_pulse_falg)
        	{
        		encoder_direction = pulse_count > prev_pulse_count ? false : true;

        		ESP_LOGI(encoder, "negative");
        	}
        	else
        	{
        		encoder_direction = pulse_count > prev_pulse_count ? true : false;
        		ESP_LOGI(encoder, "Positive");
        	}
        	
        	hEncoder.callback(encoder_direction);

           // hEncoder.callback(pulse_count + pulse_offest);

            prev_pulse_count = pulse_count;

            ESP_LOGI(encoder, "pulse count %d , direction %d", pulse_count, encoder_direction);
        }


        vTaskDelay(50/portTICK_PERIOD_MS);
    }
}
/**
 * @brief 	Initialize pulse counter to interface rotary encoder.
 *
 * @param 	callback	: the passed callback will be executed
 */
void encoder_init(void* callback)
{
    ESP_LOGI(encoder, "install pcnt unit");
    pcnt_unit_config_t unit_config = {
        .high_limit = EXAMPLE_PCNT_HIGH_LIMIT,
        .low_limit = EXAMPLE_PCNT_LOW_LIMIT,
    };

//    gpio_config_t knob_button_config = {
//        .mode = GPIO_MODE_INPUT,
//        .pin_bit_mask = 1ULL << KNOB_BUTTON
//    };
//    ESP_ERROR_CHECK(gpio_config(&knob_button_config));


    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

    ESP_LOGI(encoder, "set glitch filter");
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 1000,
    };
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config));

    ESP_LOGI(encoder, "install pcnt channels");
    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = EXAMPLE_EC11_GPIO_A,
        .level_gpio_num = EXAMPLE_EC11_GPIO_B,
    };
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan_a));
    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = EXAMPLE_EC11_GPIO_B,
        .level_gpio_num = EXAMPLE_EC11_GPIO_A,
    };
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_b_config, &pcnt_chan_b));

    ESP_LOGI(encoder, "set edge and level actions for pcnt channels");
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    ESP_LOGI(encoder, "add watch points and register callbacks");


    int watch_points[] = {-50,-40,-30};

//    memcpy(hEncoder.whatchPoints, watch_points, sizeof(watch_points));

    for (size_t i = 0; i < sizeof(watch_points) / sizeof(watch_points[0]); i++) {
        ESP_ERROR_CHECK(pcnt_unit_add_watch_point(pcnt_unit, watch_points[i]));
    }
    pcnt_event_callbacks_t cbs = {
        .on_reach = pcnt_on_reach,
    };
    hEncoder.queue = xQueueCreate(10, sizeof(int));
    ESP_ERROR_CHECK(pcnt_unit_register_event_callbacks(pcnt_unit, &cbs, hEncoder.queue));

    ESP_LOGI(encoder, "enable pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_enable(pcnt_unit));
    ESP_LOGI(encoder, "clear pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_clear_count(pcnt_unit));
    ESP_LOGI(encoder, "start pcnt unit");
    ESP_ERROR_CHECK(pcnt_unit_start(pcnt_unit));

    //External callback register.
    hEncoder.callback = callback;
}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
