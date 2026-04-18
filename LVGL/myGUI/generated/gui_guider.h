/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *time_screen;
	bool time_screen_del;
	lv_obj_t *time_screen_time_label;
	lv_obj_t *time_screen_date_label;
	lv_obj_t *time_screen_start_label;
	lv_obj_t *time_screen_start_sw;
	lv_obj_t *time_screen_slogan_label;
	lv_obj_t *menu_screen;
	bool menu_screen_del;
	lv_obj_t *menu_screen_tileview_1;
	lv_obj_t *menu_screen_tileview_1_tile;
	lv_obj_t *menu_screen_tileview_1_tile_1;
	lv_obj_t *menu_screen_weather_btn;
	lv_obj_t *menu_screen_weather_btn_label;
	lv_obj_t *menu_screen_t_h_btn;
	lv_obj_t *menu_screen_t_h_btn_label;
	lv_obj_t *menu_screen_LED_btn;
	lv_obj_t *menu_screen_LED_btn_label;
	lv_obj_t *menu_screen_time_btn;
	lv_obj_t *menu_screen_time_btn_label;
	lv_obj_t *t_h_screen;
	bool t_h_screen_del;
	lv_obj_t *t_h_screen_back1_btn;
	lv_obj_t *t_h_screen_back1_btn_label;
	lv_obj_t *t_h_screen_btn_2;
	lv_obj_t *t_h_screen_btn_2_label;
	lv_obj_t *t_h_screen_btn_3;
	lv_obj_t *t_h_screen_btn_3_label;
	lv_obj_t *t_h_screen_temp_label;
	lv_obj_t *t_h_screen_humidity_label;
	lv_obj_t *weaher_screen;
	bool weaher_screen_del;
	lv_obj_t *weaher_screen_back2_btn;
	lv_obj_t *weaher_screen_back2_btn_label;
	lv_obj_t *weaher_screen_btn_1;
	lv_obj_t *weaher_screen_btn_1_label;
	lv_obj_t *weaher_screen_btn_2;
	lv_obj_t *weaher_screen_btn_2_label;
	lv_obj_t *weaher_screen_location_label;
	lv_obj_t *weaher_screen_weather_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_time_screen(lv_ui *ui);
void setup_scr_menu_screen(lv_ui *ui);
void setup_scr_t_h_screen(lv_ui *ui);
void setup_scr_weaher_screen(lv_ui *ui);

LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_47)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_19)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_24)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_23)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_26)


#ifdef __cplusplus
}
#endif
#endif
