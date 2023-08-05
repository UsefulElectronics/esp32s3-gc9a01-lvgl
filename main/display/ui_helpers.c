// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.3.4
// PROJECT: SquareLine_Project

#include "ui_helpers.h"


void _ui_bar_set_property(lv_obj_t * target, int id, int val)
{
    if(id == _UI_BAR_PROPERTY_VALUE_WITH_ANIM) lv_bar_set_value(target, val, LV_ANIM_ON);
    if(id == _UI_BAR_PROPERTY_VALUE) lv_bar_set_value(target, val, LV_ANIM_OFF);
}

void _ui_basic_set_property(lv_obj_t * target, int id, int val)
{
    if(id == _UI_BASIC_PROPERTY_POSITION_X) lv_obj_set_x(target, val);
    if(id == _UI_BASIC_PROPERTY_POSITION_Y) lv_obj_set_y(target, val);
    if(id == _UI_BASIC_PROPERTY_WIDTH) lv_obj_set_width(target, val);
    if(id == _UI_BASIC_PROPERTY_HEIGHT) lv_obj_set_height(target, val);
}


void _ui_dropdown_set_property(lv_obj_t * target, int id, int val)
{
    if(id == _UI_DROPDOWN_PROPERTY_SELECTED) lv_dropdown_set_selected(target, val);
}

void _ui_image_set_property(lv_obj_t * target, int id, uint8_t * val)
{
    if(id == _UI_IMAGE_PROPERTY_IMAGE) lv_img_set_src(target, val);
}

void _ui_label_set_property(lv_obj_t * target, int id, char * val)
{
    if(id == _UI_LABEL_PROPERTY_TEXT) lv_label_set_text(target, val);
}


void _ui_roller_set_property(lv_obj_t * target, int id, int val)
{
    if(id == _UI_ROLLER_PROPERTY_SELECTED_WITH_ANIM) lv_roller_set_selected(target, val, LV_ANIM_ON);
    if(id == _UI_ROLLER_PROPERTY_SELECTED) lv_roller_set_selected(target, val, LV_ANIM_OFF);
}

void _ui_slider_set_property(lv_obj_t * target, int id, int val)
{
    if(id == _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM) lv_slider_set_value(target, val, LV_ANIM_ON);
    if(id == _UI_SLIDER_PROPERTY_VALUE) lv_slider_set_value(target, val, LV_ANIM_OFF);
}


void _ui_screen_change(lv_obj_t * target, lv_scr_load_anim_t fademode, int spd, int delay)
{
    lv_scr_load_anim(target, fademode, spd, delay, false);
}

/**
 * @brief handle the data to be viewed in the radar UI page
 *
 */
void _ui_radar(uint8_t movement_type, uint16_t detected_distance)
{
	char distance_string[10] = {0};
	uint8_t meter 	= 0;
	uint8_t cm		= 0;

	char movement_type_string[10] = {0};

	meter 	= detected_distance / 100;

	cm		= detected_distance % 100;

	sprintf(distance_string, "%d.%02d", meter, cm);

	if(movement_type)
	{
		sprintf(movement_type_string, "MOVEMENT");
	}
	else
	{
		sprintf(movement_type_string, "STATIC");
	}

	lv_label_set_text(ui_Distance, distance_string);
	lv_label_set_text(ui_MovementType, movement_type_string);
	lv_arc_set_value(ui_Arc3, _ui_arc_scale_radar(detected_distance));

}
/**
 * @brief 	Scale the value read from the rader and scale it to the screen arc
 *
 * @param 	Value_to_scale	:	read value to scale
 *
 * @return	scaled value
 */
uint16_t _ui_arc_scale_radar(uint16_t Value_to_scale)
{
	const uint16_t max_from = 1000;

	const uint16_t max_to 	= 180;

	return (Value_to_scale * max_to )/ max_from;
}
/**
 * @brief Seconds circle handler function
 *
 */
void _ui_arc_increment()
{
	static uint16_t counter = 0;
	static bool direction = true;
	static char timeString[6] = {0};

	memcpy(timeString, &realTime.sel.hour,2);
	timeString[2] = realTime.sel.semi;
	memcpy(timeString + 3, &realTime.sel.minute,2);

	switch (direction)
	{
		case true:
			++counter;
			break;
		case false:
			--counter;
			break;
	}

	if(0 == counter)
	{
		direction = true;
		_ui_arc_reverse();
		realTime.sel.semi = ':';
		lv_label_set_text(ui_Label2, timeString);
//		lv_label_set_text(ui_Label2, "15:10");
	}
	else if(100 == counter)
	{
		direction = false;
		_ui_arc_reverse();
		realTime.sel.semi = '.';

		lv_label_set_text(ui_Label2, timeString);
	}

//    int old = lv_arc_get_value(ui_Arc2);
    lv_arc_set_value(ui_Arc2, counter);
//    lv_event_send(ui_Arc2, LV_EVENT_VALUE_CHANGED, 0);
}
void _ui_arc_set(int val)
{
    lv_arc_set_value(ui_Arc2, val);
}
void _ui_arc_reverse()
{
	static bool mode = false;

	if(mode)
	{
		lv_arc_set_mode(ui_Arc2, LV_ARC_MODE_NORMAL);
	}
	else
	{
		lv_arc_set_mode(ui_Arc2, LV_ARC_MODE_REVERSE);

	}

	//toggle mode
	mode ^= true;
}

void _ui_temp_set(char* tempString)
{
	lv_label_set_text(ui_Label4, tempString);
}


void _ui_text_wifiIndicate(bool connectionStatus)
{
	switch (connectionStatus)
	{
		case true:
			lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xD20000), LV_PART_MAIN | LV_STATE_DEFAULT);
			break;
		case false:
			lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
		break;
		default:
			break;
	}

}
void _ui_bar_increment(lv_obj_t * target, int val, int anm)
{
    int old = lv_bar_get_value(target);
    lv_bar_set_value(target, old + val, anm);
}

void _ui_slider_increment(lv_obj_t * target, int val, int anm)
{
    int old = lv_slider_get_value(target);
    lv_slider_set_value(target, old + val, anm);
    lv_event_send(target, LV_EVENT_VALUE_CHANGED, 0);
}

void _ui_keyboard_set_target(lv_obj_t * keyboard, lv_obj_t * textarea)
{
    lv_keyboard_set_textarea(keyboard, textarea);
}

void _ui_flag_modify(lv_obj_t * target, int32_t flag, int value)
{
    if(value == _UI_MODIFY_FLAG_TOGGLE) {
        if(lv_obj_has_flag(target, flag)) lv_obj_clear_flag(target, flag);
        else lv_obj_add_flag(target, flag);
    }
    else if(value == _UI_MODIFY_FLAG_ADD) lv_obj_add_flag(target, flag);
    else lv_obj_clear_flag(target, flag);
}
void _ui_state_modify(lv_obj_t * target, int32_t state, int value)
{
    if(value == _UI_MODIFY_STATE_TOGGLE) {
        if(lv_obj_has_state(target, state)) lv_obj_clear_state(target, state);
        else lv_obj_add_state(target, state);
    }
    else if(value == _UI_MODIFY_STATE_ADD) lv_obj_add_state(target, state);
    else lv_obj_clear_state(target, state);
}

void _ui_opacity_set(lv_obj_t * target, int val)
{
    lv_obj_set_style_opa(target, val, 0);
}

void _ui_anim_callback_set_x(lv_anim_t * a, int32_t v)
{
    lv_obj_set_x((lv_obj_t *)a->user_data, v);
}

void _ui_anim_callback_set_y(lv_anim_t * a, int32_t v)
{
    lv_obj_set_y((lv_obj_t *)a->user_data, v);
}

void _ui_anim_callback_set_width(lv_anim_t * a, int32_t v)
{
    lv_obj_set_width((lv_obj_t *)a->user_data, v);
}

void _ui_anim_callback_set_height(lv_anim_t * a, int32_t v)
{
    lv_obj_set_height((lv_obj_t *)a->user_data, v);
}

void _ui_anim_callback_set_opacity(lv_anim_t * a, int32_t v)
{
    lv_obj_set_style_opa((lv_obj_t *)a->user_data, v, 0);
}

void _ui_anim_callback_set_image_zoom(lv_anim_t * a, int32_t v)
{
    lv_img_set_zoom((lv_obj_t *)a->user_data, v);
}

void _ui_anim_callback_set_image_angle(lv_anim_t * a, int32_t v)
{
    lv_img_set_angle((lv_obj_t *)a->user_data, v);
}


int32_t _ui_anim_callback_get_x(lv_anim_t * a)
{
    return lv_obj_get_x_aligned((lv_obj_t *)a->user_data);
}

int32_t _ui_anim_callback_get_y(lv_anim_t * a)
{
    return lv_obj_get_y_aligned((lv_obj_t *)a->user_data);
}

int32_t _ui_anim_callback_get_width(lv_anim_t * a)
{
    return lv_obj_get_width((lv_obj_t *)a->user_data);
}

int32_t _ui_anim_callback_get_height(lv_anim_t * a)
{
    return lv_obj_get_height((lv_obj_t *)a->user_data);
}

int32_t _ui_anim_callback_get_opacity(lv_anim_t * a)
{
    return lv_obj_get_style_opa((lv_obj_t *)a->user_data, 0);
}

int32_t _ui_anim_callback_get_image_zoom(lv_anim_t * a)
{
    return lv_img_get_zoom((lv_obj_t *)a->user_data);
}

int32_t _ui_anim_callback_get_image_angle(lv_anim_t * a)
{
    return lv_img_get_angle((lv_obj_t *)a->user_data);
}

void _ui_arc_set_text_value(lv_obj_t * trg, lv_obj_t * src, char * prefix, char * postfix)
{
    char buf[_UI_TEMPORARY_STRING_BUFFER_SIZE];
    lv_snprintf(buf, sizeof(buf), "%s%d%s", prefix, (int)lv_arc_get_value(src), postfix);
    lv_label_set_text(trg, buf);
}

void _ui_slider_set_text_value(lv_obj_t * trg, lv_obj_t * src, char * prefix, char * postfix)
{
    char buf[_UI_TEMPORARY_STRING_BUFFER_SIZE];
    lv_snprintf(buf, sizeof(buf), "%s%d%s", prefix, (int)lv_slider_get_value(src), postfix);
    lv_label_set_text(trg, buf);
}
void _ui_checked_set_text_value(lv_obj_t * trg, lv_obj_t * src, char * txt_on, char * txt_off)
{
    if(lv_obj_has_state(src, LV_STATE_CHECKED)) lv_label_set_text(trg, txt_on);
    else lv_label_set_text(trg, txt_off);
}


