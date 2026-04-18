/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_menu_screen(lv_ui *ui)
{
    //Write codes menu_screen
    ui->menu_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->menu_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->menu_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_tileview_1
    ui->menu_screen_tileview_1 = lv_tileview_create(ui->menu_screen);
    ui->menu_screen_tileview_1_tile = lv_tileview_add_tile(ui->menu_screen_tileview_1, 0, 0, LV_DIR_RIGHT);
    ui->menu_screen_tileview_1_tile_1 = lv_tileview_add_tile(ui->menu_screen_tileview_1, 1, 0, LV_DIR_LEFT);
    lv_obj_set_pos(ui->menu_screen_tileview_1, 10, 20);
    lv_obj_set_size(ui->menu_screen_tileview_1, 300, 200);
    lv_obj_set_scrollbar_mode(ui->menu_screen_tileview_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_screen_tileview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_tileview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_tileview_1, lv_color_hex(0xf6f6f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_tileview_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_tileview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_tileview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for menu_screen_tileview_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_tileview_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_tileview_1, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_tileview_1, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_tileview_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



    //Write codes menu_screen_weather_btn
    ui->menu_screen_weather_btn = lv_btn_create(ui->menu_screen_tileview_1_tile);
    ui->menu_screen_weather_btn_label = lv_label_create(ui->menu_screen_weather_btn);
    lv_label_set_text(ui->menu_screen_weather_btn_label, "天气");
    lv_label_set_long_mode(ui->menu_screen_weather_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_weather_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_weather_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_weather_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_weather_btn, 168, 81);
    lv_obj_set_size(ui->menu_screen_weather_btn, 100, 50);

    //Write style for menu_screen_weather_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_weather_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_weather_btn, lv_color_hex(0x008a08), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_weather_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_weather_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_weather_btn, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_weather_btn, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->menu_screen_weather_btn, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->menu_screen_weather_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->menu_screen_weather_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->menu_screen_weather_btn, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->menu_screen_weather_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_weather_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_weather_btn, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_weather_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_weather_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_t_h_btn
    ui->menu_screen_t_h_btn = lv_btn_create(ui->menu_screen_tileview_1_tile);
    ui->menu_screen_t_h_btn_label = lv_label_create(ui->menu_screen_t_h_btn);
    lv_label_set_text(ui->menu_screen_t_h_btn_label, "温湿度");
    lv_label_set_long_mode(ui->menu_screen_t_h_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_t_h_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_t_h_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_t_h_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_t_h_btn, 28, 79);
    lv_obj_set_size(ui->menu_screen_t_h_btn, 100, 50);

    //Write style for menu_screen_t_h_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_t_h_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_t_h_btn, lv_color_hex(0x00138a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_t_h_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_t_h_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_t_h_btn, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_t_h_btn, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->menu_screen_t_h_btn, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->menu_screen_t_h_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->menu_screen_t_h_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->menu_screen_t_h_btn, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->menu_screen_t_h_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_t_h_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_t_h_btn, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_t_h_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_t_h_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes menu_screen_LED_btn
    ui->menu_screen_LED_btn = lv_btn_create(ui->menu_screen_tileview_1_tile_1);
    ui->menu_screen_LED_btn_label = lv_label_create(ui->menu_screen_LED_btn);
    lv_label_set_text(ui->menu_screen_LED_btn_label, "LED");
    lv_label_set_long_mode(ui->menu_screen_LED_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_LED_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_LED_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_LED_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_LED_btn, 33, 91);
    lv_obj_set_size(ui->menu_screen_LED_btn, 100, 50);

    //Write style for menu_screen_LED_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_LED_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_LED_btn, lv_color_hex(0xf30025), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_LED_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_LED_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_LED_btn, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_LED_btn, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->menu_screen_LED_btn, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->menu_screen_LED_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->menu_screen_LED_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->menu_screen_LED_btn, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->menu_screen_LED_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_LED_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_LED_btn, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_LED_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_LED_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_time_btn
    ui->menu_screen_time_btn = lv_btn_create(ui->menu_screen_tileview_1_tile_1);
    ui->menu_screen_time_btn_label = lv_label_create(ui->menu_screen_time_btn);
    lv_label_set_text(ui->menu_screen_time_btn_label, "时间");
    lv_label_set_long_mode(ui->menu_screen_time_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_time_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_time_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_time_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_time_btn, 169, 93);
    lv_obj_set_size(ui->menu_screen_time_btn, 100, 50);

    //Write style for menu_screen_time_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_time_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_time_btn, lv_color_hex(0xd300f3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_time_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_time_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_time_btn, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_time_btn, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->menu_screen_time_btn, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->menu_screen_time_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->menu_screen_time_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->menu_screen_time_btn, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->menu_screen_time_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_time_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_time_btn, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_time_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_time_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of menu_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->menu_screen);

    //Init events for screen.
    events_init_menu_screen(ui);
}
