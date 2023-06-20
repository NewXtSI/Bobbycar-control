#include <Arduino.h>

#if !defined LGFX_AUTODETECT
  #define LGFX_AUTODETECT
#endif
#define LGFX_USE_V1     // set to use new version of library
#define LGFX_TTGO_TDISPLAY 

#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>
#include <lvgl.h>
#include "lv_conf.h"

#define screenWidth 240
#define screenHeight 135

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

/*** Function declaration ***/
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

static LGFX lcd; // declare display variable

 LV_IMG_DECLARE(bg1);
 LV_IMG_DECLARE(ebike_gauge_bg);
 LV_IMG_DECLARE(ebike_gauge_lines);
 LV_IMG_DECLARE(ebike_gauge_needle);
 LV_IMG_DECLARE(ebike_gauge_numbers);
 LV_IMG_DECLARE(ebike_gauge_battery_line);
 LV_IMG_DECLARE(ebike_gauge_battery);

void ui_task(void *param) {
    lcd.init();
    lv_init();   // Initialize lvgl
    if (lcd.width() < lcd.height()) lcd.setRotation(lcd.getRotation() ^ 1);
    /* LVGL : Setting up buffer to use for display */
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

    /*** LVGL : Setup & Initialize the display device driver ***/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = display_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    lv_obj_t *mainscreen = lv_obj_create(nullptr);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lv_obj_t *RideInfo1_bg_img = lv_img_create(mainscreen);
	lv_obj_set_pos(RideInfo1_bg_img, 0, 0);
	lv_obj_set_size(RideInfo1_bg_img, 240, 135);

	//Write style state: LV_STATE_DEFAULT for style_rideinfo1_bg_img_main_main_default
	static lv_style_t style_rideinfo1_bg_img_main_main_default;
	if (style_rideinfo1_bg_img_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_rideinfo1_bg_img_main_main_default);
	else
		lv_style_init(&style_rideinfo1_bg_img_main_main_default);
	lv_style_set_img_recolor(&style_rideinfo1_bg_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_rideinfo1_bg_img_main_main_default, 0);
	lv_style_set_img_opa(&style_rideinfo1_bg_img_main_main_default, 255);
	lv_obj_add_style(RideInfo1_bg_img, &style_rideinfo1_bg_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(RideInfo1_bg_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(RideInfo1_bg_img,&bg1);
	lv_img_set_pivot(RideInfo1_bg_img, 0,0);
	lv_img_set_angle(RideInfo1_bg_img, 0);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Write codes Overview_gauge_bg_img
	lv_obj_t *Overview_gauge_bg_img = lv_img_create(mainscreen);
	lv_obj_set_pos(Overview_gauge_bg_img, 2, 12);
	lv_obj_set_size(Overview_gauge_bg_img, 116, 117);

	//Write style state: LV_STATE_DEFAULT for style_overview_gauge_bg_img_main_main_default
	static lv_style_t style_overview_gauge_bg_img_main_main_default;
	if (style_overview_gauge_bg_img_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_overview_gauge_bg_img_main_main_default);
	else
		lv_style_init(&style_overview_gauge_bg_img_main_main_default);
	lv_style_set_img_recolor(&style_overview_gauge_bg_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_overview_gauge_bg_img_main_main_default, 0);
	lv_style_set_img_opa(&style_overview_gauge_bg_img_main_main_default, 255);
	lv_obj_add_style(Overview_gauge_bg_img, &style_overview_gauge_bg_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(Overview_gauge_bg_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(Overview_gauge_bg_img,&ebike_gauge_bg);
	lv_img_set_pivot(Overview_gauge_bg_img, 0,0);
	lv_img_set_angle(Overview_gauge_bg_img, 0);

	//Write codes Overview_gaugeL_img
	lv_obj_t* Overview_gaugeL_img = lv_img_create(mainscreen);
	lv_obj_set_pos(Overview_gaugeL_img, 25 / 2, 45 / 2);
	lv_obj_set_size(Overview_gaugeL_img, 193 / 2, 164 / 2);

	//Write style state: LV_STATE_DEFAULT for style_overview_gaugel_img_main_main_default
	static lv_style_t style_overview_gaugel_img_main_main_default;
	if (style_overview_gaugel_img_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_overview_gaugel_img_main_main_default);
	else
		lv_style_init(&style_overview_gaugel_img_main_main_default);
	lv_style_set_img_recolor(&style_overview_gaugel_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_overview_gaugel_img_main_main_default, 0);
	lv_style_set_img_opa(&style_overview_gaugel_img_main_main_default, 255);
	lv_obj_add_style(Overview_gaugeL_img, &style_overview_gaugel_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(Overview_gaugeL_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(Overview_gaugeL_img,&ebike_gauge_lines);
	lv_img_set_pivot(Overview_gaugeL_img, 0,0);
	lv_img_set_angle(Overview_gaugeL_img, 0);

	//Write codes Overview_gaugeN_img
	lv_obj_t* Overview_gaugeN_img = lv_img_create(mainscreen);
	lv_obj_set_pos(Overview_gaugeN_img, 37 / 2, 55 / 2);
	lv_obj_set_size(Overview_gaugeN_img, 166 / 2, 134 / 2);

	//Write style state: LV_STATE_DEFAULT for style_overview_gaugen_img_main_main_default
	static lv_style_t style_overview_gaugen_img_main_main_default;
	if (style_overview_gaugen_img_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_overview_gaugen_img_main_main_default);
	else
		lv_style_init(&style_overview_gaugen_img_main_main_default);
	lv_style_set_img_recolor(&style_overview_gaugen_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_overview_gaugen_img_main_main_default, 0);
	lv_style_set_img_opa(&style_overview_gaugen_img_main_main_default, 255);
	lv_obj_add_style(Overview_gaugeN_img, &style_overview_gaugen_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(Overview_gaugeN_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(Overview_gaugeN_img,&ebike_gauge_numbers);
	lv_img_set_pivot(Overview_gaugeN_img, 0,0);
	lv_img_set_angle(Overview_gaugeN_img, 0);

	//Write codes Overview_needle_img
	lv_obj_t* Overview_needle_img = lv_img_create(mainscreen);
	lv_obj_set_pos(Overview_needle_img, 11, 21 );
	lv_obj_set_size(Overview_needle_img, 100, 100);

	//Write style state: LV_STATE_DEFAULT for style_overview_needle_img_main_main_default
	static lv_style_t style_overview_needle_img_main_main_default;
	if (style_overview_needle_img_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_overview_needle_img_main_main_default);
	else
		lv_style_init(&style_overview_needle_img_main_main_default);
	lv_style_set_img_recolor(&style_overview_needle_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_overview_needle_img_main_main_default, 0);
	lv_style_set_img_opa(&style_overview_needle_img_main_main_default, 255);
	lv_obj_add_style(Overview_needle_img, &style_overview_needle_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(Overview_needle_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(Overview_needle_img,&ebike_gauge_needle);
	lv_img_set_pivot(Overview_needle_img, 50, 50);
	lv_img_set_angle(Overview_needle_img, 1500);

	//Write codes Overview_battery_line_img
	lv_obj_t* Overview_battery_line_img = lv_img_create(mainscreen);
	lv_obj_set_pos(Overview_battery_line_img, 5 / 2, 139 / 2);
	lv_obj_set_size(Overview_battery_line_img, 237 / 2, 120 / 2);

	//Write style state: LV_STATE_DEFAULT for style_overview_battery_line_img_main_main_default
	static lv_style_t style_overview_battery_line_img_main_main_default;
	if (style_overview_battery_line_img_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_overview_battery_line_img_main_main_default);
	else
		lv_style_init(&style_overview_battery_line_img_main_main_default);
	lv_style_set_img_recolor(&style_overview_battery_line_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_overview_battery_line_img_main_main_default, 0);
	lv_style_set_img_opa(&style_overview_battery_line_img_main_main_default, 255);
	lv_obj_add_style(Overview_battery_line_img, &style_overview_battery_line_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(Overview_battery_line_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(Overview_battery_line_img,&ebike_gauge_battery_line);
	lv_img_set_pivot(Overview_battery_line_img, 0,0);
	lv_img_set_angle(Overview_battery_line_img, 0);

	//Write codes Overview_battery_icon
	lv_obj_t* Overview_battery_icon = lv_img_create(mainscreen);
	lv_obj_set_pos(Overview_battery_icon, 110 / 2, 200 / 2);
	lv_obj_set_size(Overview_battery_icon, 15 / 2, 12 / 2);

	//Write style state: LV_STATE_DEFAULT for style_overview_battery_icon_main_main_default
	static lv_style_t style_overview_battery_icon_main_main_default;
	if (style_overview_battery_icon_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_overview_battery_icon_main_main_default);
	else
		lv_style_init(&style_overview_battery_icon_main_main_default);
	lv_style_set_img_recolor(&style_overview_battery_icon_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_overview_battery_icon_main_main_default, 0);
	lv_style_set_img_opa(&style_overview_battery_icon_main_main_default, 255);
	lv_obj_add_style(Overview_battery_icon, &style_overview_battery_icon_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(Overview_battery_icon, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(Overview_battery_icon,&ebike_gauge_battery);
	lv_img_set_pivot(Overview_battery_icon, 0,0);
	lv_img_set_angle(Overview_battery_icon, 0);




	//Write codes Overview_battery_arc
	lv_obj_t* Overview_battery_arc = lv_arc_create(mainscreen);
	lv_obj_set_pos(Overview_battery_arc, 25 / 2, 38 / 2);
	lv_obj_set_size(Overview_battery_arc, 200 / 2, 200 / 2);

	//Write style state: LV_STATE_DEFAULT for style_overview_battery_arc_main_main_default
	static lv_style_t style_overview_battery_arc_main_main_default;
	if (style_overview_battery_arc_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_overview_battery_arc_main_main_default);
	else
		lv_style_init(&style_overview_battery_arc_main_main_default);
	lv_style_set_bg_color(&style_overview_battery_arc_main_main_default, lv_color_make(0x09, 0x80, 0xff));
	lv_style_set_bg_grad_color(&style_overview_battery_arc_main_main_default, lv_color_make(0x00, 0x80, 0xff));
	lv_style_set_bg_grad_dir(&style_overview_battery_arc_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_overview_battery_arc_main_main_default, 0);
	lv_style_set_border_width(&style_overview_battery_arc_main_main_default, 0);
	lv_style_set_arc_color(&style_overview_battery_arc_main_main_default, lv_color_make(0x00, 0x80, 0xff));
	lv_style_set_arc_width(&style_overview_battery_arc_main_main_default, 5);
	lv_obj_add_style(Overview_battery_arc, &style_overview_battery_arc_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_overview_battery_arc_main_indicator_default
	static lv_style_t style_overview_battery_arc_main_indicator_default;
	if (style_overview_battery_arc_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_overview_battery_arc_main_indicator_default);
	else
		lv_style_init(&style_overview_battery_arc_main_indicator_default);
	lv_style_set_arc_color(&style_overview_battery_arc_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_arc_width(&style_overview_battery_arc_main_indicator_default, 5);
	lv_obj_add_style(Overview_battery_arc, &style_overview_battery_arc_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_overview_battery_arc_main_knob_default
	static lv_style_t style_overview_battery_arc_main_knob_default;
	if (style_overview_battery_arc_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_overview_battery_arc_main_knob_default);
	else
		lv_style_init(&style_overview_battery_arc_main_knob_default);
	lv_style_set_bg_color(&style_overview_battery_arc_main_knob_default, lv_color_make(0x00, 0x80, 0xff));
	lv_style_set_bg_grad_color(&style_overview_battery_arc_main_knob_default, lv_color_make(0x00, 0x80, 0xff));
	lv_style_set_bg_grad_dir(&style_overview_battery_arc_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_overview_battery_arc_main_knob_default, 0);
	lv_style_set_pad_all(&style_overview_battery_arc_main_knob_default, 5);
	lv_obj_add_style(Overview_battery_arc, &style_overview_battery_arc_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_bg_angles(Overview_battery_arc, 85, 130);
	lv_arc_set_angles(Overview_battery_arc, 85, 130);
	lv_arc_set_rotation(Overview_battery_arc, 0);
	lv_obj_set_style_pad_top(Overview_battery_arc, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(Overview_battery_arc, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(Overview_battery_arc, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(Overview_battery_arc, 0, LV_STATE_DEFAULT);

//    lv_obj_set_style_bg_color(mainscreen, lv_color_hex(0x0000FF),0);
//    lv_obj_set_style_bg_color(mainscreen, lv_color_hex(0x303030),0);
    lv_scr_load(mainscreen);
#if 0
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_arc_rounded(&style, 0);
    lv_style_set_arc_width(&style, 40);
    lv_style_set_arc_img_src(&style, &circle);
    lv_obj_t* speed_arc = lv_arc_create(lv_scr_act());
    lv_obj_center(speed_arc);

    lv_obj_set_style_arc_color(speed_arc, lv_color_hex(0xff0000), LV_PART_MAIN);
//    lv_obj_add_style(speed_arc, &style, LV_PART_MAIN);
    lv_obj_add_style(speed_arc, &style, LV_PART_INDICATOR);
    lv_obj_remove_style(speed_arc, NULL, LV_PART_KNOB);
    lv_obj_set_size(speed_arc, 135, 135);
    lv_arc_set_rotation(speed_arc, 150);
    lv_arc_set_bg_angles(speed_arc, 0, 240);
    lv_arc_set_range(speed_arc, 0, 240);
    lv_arc_set_value(speed_arc, 120);
#endif
      lcd.setBrightness(255);
    int16_t uiSpeed = 0;
    bool uiForward = true;
    
    while (1) {

//        lv_arc_set_value(speed_arc, uiSpeed);
//        lv_style_set_transform_angle(&style, uiSpeed);
//        lv_style_set_arc_rounded(&style, &circle);
//        lv_arc_set_rotation(speed_arc, uiSpeed);
	lv_arc_set_bg_angles(Overview_battery_arc, 128, 130);
	lv_arc_set_angles(Overview_battery_arc, 128, 130);
//	lv_arc_set_bg_angles(Overview_battery_arc, 85+(uiSpeed/10), 130);
//	lv_arc_set_angles(Overview_battery_arc, 85+(uiSpeed/10), 130);
//        lv_arc_set_value(Overview_battery_arc, uiSpeed);
    	lv_img_set_angle(Overview_needle_img, (1500)+(uiSpeed*10));
        lv_timer_handler(); /* let the GUI do its work */
        vTaskDelay(1);
//        delay(2);
        if (uiForward) {
            uiSpeed+=4;
            if (uiSpeed > 255) {
                uiSpeed = 255;
                uiForward = !uiForward;
            }
        } else {
            uiSpeed-=4;
            if (uiSpeed <= 0) {
                uiSpeed = 0;
                uiForward = !uiForward;
            }

        }
    }
    vTaskDelete(NULL);
}

/*** Display callback to flush the buffer to screen ***/
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
    lcd.endWrite();

    lv_disp_flush_ready(disp);
}
