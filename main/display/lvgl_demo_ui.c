/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/widgets/extra/meter.html#simple-meter

#include "lvgl_demo_ui.h"


static void ui_radar_screen_init(void);
static void ui_watch_screen_init(void);
static void ui_lamp_screen_init(void)

static lv_obj_t *meter;
static lv_obj_t * btn;
static lv_disp_rot_t rotation = LV_DISP_ROT_NONE;
static lv_disp_t *lv_display;
static lv_meter_indicator_t *indic;
static lv_style_t bgStyle;

watch_t realTime = {0};

//Smart watch screen
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Arc2;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Label4;

//Radar Screen
lv_obj_t * ui_radar;
lv_obj_t * ui_Panel6;
lv_obj_t * ui_Arc3;
lv_obj_t * ui_Panel7;
lv_obj_t * ui_Distance;
lv_obj_t * ui_MovementType;

lv_obj_t *tv1;
lv_obj_t *tv2;

// SCREEN: ui_Lamp
lv_obj_t * ui_lamp;
lv_obj_t * ui_Panel9;
lv_obj_t * ui_Switch1;
lv_obj_t * ui_Switch3;
lv_obj_t * ui_Colorwheel2;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Panel10;
lv_obj_t * ui_Image8;
lv_obj_t * ui_Image9;


void set_value(int32_t v, bool buttonStatus)
{
	 lv_color_t bgColor;
	 static bool toggleColor = 0;

	 lv_obj_t *disObject = lv_disp_get_scr_act(lv_display);

    lv_meter_set_indicator_end_value(meter, indic, v);

    if(!buttonStatus)
    {
    	toggleColor ^= 1;
    	if(toggleColor)
    	{
    		//White
    		bgColor = lv_color_hex(0xFFFFFF);
    	}
    	else
    	{
    		//black
    		bgColor = lv_color_hex(0x000000);
    	}
        lv_obj_add_style(disObject, &bgStyle, 0);
        lv_style_set_bg_color(&bgStyle, bgColor);



//        rotation++;
//        if (rotation > LV_DISP_ROT_270)
//        {
//            rotation = LV_DISP_ROT_NONE;
//        }
//        lv_disp_set_rotation(lv_display, rotation);
    }

}

void example_lvgl_demo_ui(lv_disp_t *disp)
{
	 lv_color_t bgColor;
	lv_display = disp;
	lv_obj_t *dis;
	lv_obj_t *scr = lv_disp_get_scr_act(disp);

	bgColor = lv_color_hex(0x101418);
	lv_style_init(&bgStyle);


	dis = lv_tileview_create(scr);
	lv_obj_align(dis, LV_ALIGN_TOP_RIGHT, 0, 0);

	ui_radar 	= lv_tileview_add_tile(dis, 0, 2, LV_DIR_HOR);
	ui_Screen1 	= lv_tileview_add_tile(dis, 0, 1, LV_DIR_HOR);
	ui_lamp 	= lv_tileview_add_tile(dis, 0, 0, LV_DIR_HOR);

	//tv3 		= lv_tileview_add_tile(dis, 0, 2, LV_DIR_HOR);

//	lv_obj_add_style(ui_Screen1, &bgStyle, 0);
//	lv_style_set_bg_color(&bgStyle, bgColor);

	//lv_obj_add_style(ui_radar, &bgStyle, 0);
	//lv_style_set_bg_color(&bgStyle, bgColor);
	
	lv_obj_add_style(ui_lamp, &bgStyle, 0);
	lv_style_set_bg_color(&bgStyle, bgColor);

	ui_lamp_screen_init();
	//ui_radar_screen_init();
}

static void ui_radar_screen_init(void)
{

//	ui_radar = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_radar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

	ui_Panel6 = lv_obj_create(ui_radar);
	lv_obj_set_width(ui_Panel6, 220);
	lv_obj_set_height(ui_Panel6, 220);
	lv_obj_set_align(ui_Panel6, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_Panel6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(ui_Panel6, 360, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_Panel6, lv_color_hex(0x0E0303), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_Panel6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui_Panel6, &ui_img_1321029331, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_Panel6, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_Panel6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui_Panel6, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Arc3 = lv_arc_create(ui_radar);
    lv_obj_set_width(ui_Arc3, 240);
    lv_obj_set_height(ui_Arc3, 240);
    lv_obj_set_align(ui_Arc3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Arc3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_arc_set_range(ui_Arc3, 0, 360);
    lv_arc_set_bg_angles(ui_Arc3, 0, 360);
    lv_arc_set_rotation(ui_Arc3, 180);
    lv_obj_set_style_arc_color(ui_Arc3, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Arc3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_Arc3, lv_color_hex(0xD20000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Arc3, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Arc3, lv_color_hex(0xD20000), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Arc3, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Arc3, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Arc3, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Arc3, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Arc3, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

	ui_Panel7 = lv_obj_create(ui_radar);
	lv_obj_set_width(ui_Panel7, 150);
	lv_obj_set_height(ui_Panel7, 150);
	lv_obj_set_align(ui_Panel7, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_Panel7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(ui_Panel7, 360, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_Panel7, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_Panel7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_Panel7, lv_color_hex(0x080808), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_Panel7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_Distance = lv_label_create(ui_Panel7);
	lv_obj_set_width(ui_Distance, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_Distance, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_Distance, LV_ALIGN_CENTER);
	lv_label_set_text(ui_Distance, "0.00");
	lv_obj_set_style_text_color(ui_Distance, lv_color_hex(0xC50000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_Distance, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_Distance, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_decor(ui_Distance, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_Distance, &ui_font_wise60, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MovementType = lv_label_create(ui_radar);
	lv_obj_set_width(ui_MovementType, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_MovementType, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_x(ui_MovementType, 0);
	lv_obj_set_y(ui_MovementType, -53);
	lv_obj_set_align(ui_MovementType, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MovementType, "Movemet");
	lv_obj_set_style_text_color(ui_MovementType, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_MovementType, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

}
static void ui_watch_screen_init(void)
{


//    ui_Panel2 = lv_obj_create(ui_Screen1);
//    lv_obj_set_width(ui_Panel2, 220);
//    lv_obj_set_height(ui_Panel2, 220);
//    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_radius(ui_Panel2, 360, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x0E0303), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_img_src(ui_Panel2, &ui_img_patern3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_img_tiled(ui_Panel2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_side(ui_Panel2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel2 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel2, 220);
    lv_obj_set_height(ui_Panel2, 220);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel2, 360, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x0E0303), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Panel2, &ui_img_1321029331, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Panel2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_Arc2 = lv_arc_create(ui_Screen1);
    lv_obj_set_width(ui_Arc2, 240);
    lv_obj_set_height(ui_Arc2, 240);
    lv_obj_set_align(ui_Arc2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Arc2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_arc_set_range(ui_Arc2, 0, 100);
    lv_arc_set_value(ui_Arc2, 100);
    lv_arc_set_bg_angles(ui_Arc2, 0, 360);
    lv_arc_set_mode(ui_Arc2, LV_ARC_MODE_NORMAL);
    lv_arc_set_rotation(ui_Arc2, 270);
    lv_obj_set_style_arc_color(ui_Arc2, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Arc2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_Arc2, lv_color_hex(0xD20000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_Arc2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Arc2, lv_color_hex(0xD20000), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Arc2, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Arc2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Arc2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Arc2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Arc2, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
//
//    ui_Panel2 = lv_obj_create(ui_Screen1);
//    lv_obj_set_width(ui_Panel2, 200);
//    lv_obj_set_height(ui_Panel2, 200);
//    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_radius(ui_Panel2, 360, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x0E0303), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_border_side(ui_Panel2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
//
    ui_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel1, 150);
    lv_obj_set_height(ui_Panel1, 150);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel1, 360, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x080808), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//
    ui_Label2 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "15:10");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xC50000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Label2, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_Label2, LV_TEXT_DECOR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, &ui_font_wise60, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, 0);
    lv_obj_set_y(ui_Label3, -53);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
//    lv_label_set_text(ui_Label3, "W");
    lv_label_set_text_static(ui_Label3, LV_SYMBOL_WIFI);
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label4 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, 0);
    lv_obj_set_y(ui_Label4, 41);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "12 °C");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0xD50000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label4, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void ui_lamp_screen_init(void)
{

    ui_lamp = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_lamp, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Panel9 = lv_obj_create(ui_lamp);
    lv_obj_set_width(ui_Panel9, 240);
    lv_obj_set_height(ui_Panel9, 240);
    lv_obj_set_align(ui_Panel9, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel9, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Panel9, &ui_img_bg3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Switch1 = lv_switch_create(ui_Panel9);
    lv_obj_set_width(ui_Switch1, 29);
    lv_obj_set_height(ui_Switch1, 13);
    lv_obj_set_x(ui_Switch1, -35);
    lv_obj_set_y(ui_Switch1, -70);
    lv_obj_set_align(ui_Switch1, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Switch1, lv_color_hex(0xD30000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Switch1, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_Switch1, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Switch1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_Switch1, lv_color_hex(0xD50000), LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_Switch1, 255, LV_PART_INDICATOR | LV_STATE_PRESSED);

    lv_obj_set_style_bg_color(ui_Switch1, lv_color_hex(0xD50000), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch1, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Switch1, lv_color_hex(0x293031), LV_PART_KNOB | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_Switch1, 255, LV_PART_KNOB | LV_STATE_PRESSED);

    ui_Switch3 = lv_switch_create(ui_Panel9);
    lv_obj_set_width(ui_Switch3, 29);
    lv_obj_set_height(ui_Switch3, 13);
    lv_obj_set_x(ui_Switch3, 35);
    lv_obj_set_y(ui_Switch3, -70);
    lv_obj_set_align(ui_Switch3, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Switch3, lv_color_hex(0xD30000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Switch3, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_Switch3, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Switch3, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_Switch3, lv_color_hex(0xD50000), LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_Switch3, 255, LV_PART_INDICATOR | LV_STATE_PRESSED);

    lv_obj_set_style_bg_color(ui_Switch3, lv_color_hex(0xD50000), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch3, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Switch3, lv_color_hex(0x293031), LV_PART_KNOB | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_Switch3, 255, LV_PART_KNOB | LV_STATE_PRESSED);

    ui_Colorwheel2 = lv_colorwheel_create(ui_Panel9, true);
    lv_obj_set_width(ui_Colorwheel2, 240);
    lv_obj_set_height(ui_Colorwheel2, 240);
    lv_obj_set_align(ui_Colorwheel2, LV_ALIGN_CENTER);

    ui_Label4 = lv_label_create(ui_Panel9);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, 35);
    lv_obj_set_y(ui_Label4, -85);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "W");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0xD50000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label6 = lv_label_create(ui_Panel9);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, -35);
    lv_obj_set_y(ui_Label6, -85);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "MQTT");
    lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0xD50000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel10 = lv_obj_create(ui_lamp);
    lv_obj_set_width(ui_Panel10, 150);
    lv_obj_set_height(ui_Panel10, 150);
    lv_obj_set_align(ui_Panel10, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel10, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel10, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image8 = lv_img_create(ui_Panel10);
    lv_img_set_src(ui_Image8, &ui_img_off_bulb_png);
    lv_obj_set_width(ui_Image8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image8, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image8, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image8, 400);

    ui_Image9 = lv_img_create(ui_Panel10);
    lv_img_set_src(ui_Image9, &ui_img_bulb_png);
    lv_obj_set_width(ui_Image9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Image9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image9, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Image9, 400);
}

