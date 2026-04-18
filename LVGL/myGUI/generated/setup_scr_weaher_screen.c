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



void setup_scr_weaher_screen(lv_ui *ui)
{
    //Write codes weaher_screen
    ui->weaher_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->weaher_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->weaher_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for weaher_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->weaher_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weaher_screen_back2_btn
    ui->weaher_screen_back2_btn = lv_btn_create(ui->weaher_screen);
    ui->weaher_screen_back2_btn_label = lv_label_create(ui->weaher_screen_back2_btn);
    lv_label_set_text(ui->weaher_screen_back2_btn_label, "back");
    lv_label_set_long_mode(ui->weaher_screen_back2_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->weaher_screen_back2_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->weaher_screen_back2_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->weaher_screen_back2_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->weaher_screen_back2_btn, 241, 194);
    lv_obj_set_size(ui->weaher_screen_back2_btn, 65, 36);

    //Write style for weaher_screen_back2_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->weaher_screen_back2_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->weaher_screen_back2_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weaher_screen_back2_btn, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weaher_screen_back2_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->weaher_screen_back2_btn, lv_color_hex(0xe30707), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->weaher_screen_back2_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->weaher_screen_back2_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->weaher_screen_back2_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->weaher_screen_back2_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weaher_screen_back2_btn, lv_color_hex(0xdf4289), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weaher_screen_back2_btn, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weaher_screen_back2_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weaher_screen_back2_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weaher_screen_btn_1
    ui->weaher_screen_btn_1 = lv_btn_create(ui->weaher_screen);
    ui->weaher_screen_btn_1_label = lv_label_create(ui->weaher_screen_btn_1);
    lv_label_set_text(ui->weaher_screen_btn_1_label, "地区");
    lv_label_set_long_mode(ui->weaher_screen_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->weaher_screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->weaher_screen_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->weaher_screen_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->weaher_screen_btn_1, 33, 53);
    lv_obj_set_size(ui->weaher_screen_btn_1, 79, 39);

    //Write style for weaher_screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->weaher_screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->weaher_screen_btn_1, lv_color_hex(0x0ec52d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->weaher_screen_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->weaher_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weaher_screen_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weaher_screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weaher_screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weaher_screen_btn_1, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weaher_screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weaher_screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weaher_screen_btn_2
    ui->weaher_screen_btn_2 = lv_btn_create(ui->weaher_screen);
    ui->weaher_screen_btn_2_label = lv_label_create(ui->weaher_screen_btn_2);
    lv_label_set_text(ui->weaher_screen_btn_2_label, "天气");
    lv_label_set_long_mode(ui->weaher_screen_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->weaher_screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->weaher_screen_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->weaher_screen_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->weaher_screen_btn_2, 33, 127);
    lv_obj_set_size(ui->weaher_screen_btn_2, 79, 39);

    //Write style for weaher_screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->weaher_screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->weaher_screen_btn_2, lv_color_hex(0x0ec52d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->weaher_screen_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->weaher_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weaher_screen_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weaher_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weaher_screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weaher_screen_btn_2, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weaher_screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weaher_screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weaher_screen_location_label
    ui->weaher_screen_location_label = lv_label_create(ui->weaher_screen);
    lv_label_set_text(ui->weaher_screen_location_label, "上海");
    lv_label_set_long_mode(ui->weaher_screen_location_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weaher_screen_location_label, 134, 58);
    lv_obj_set_size(ui->weaher_screen_location_label, 100, 32);

    //Write style for weaher_screen_location_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weaher_screen_location_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weaher_screen_location_label, &lv_font_SourceHanSerifSC_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weaher_screen_location_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weaher_screen_location_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weaher_screen_location_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes weaher_screen_weather_label
    ui->weaher_screen_weather_label = lv_label_create(ui->weaher_screen);
    lv_label_set_text(ui->weaher_screen_weather_label, "多云");
    lv_label_set_long_mode(ui->weaher_screen_weather_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->weaher_screen_weather_label, 137, 132);
    lv_obj_set_size(ui->weaher_screen_weather_label, 100, 32);

    //Write style for weaher_screen_weather_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->weaher_screen_weather_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->weaher_screen_weather_label, &lv_font_SourceHanSerifSC_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->weaher_screen_weather_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->weaher_screen_weather_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->weaher_screen_weather_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of weaher_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->weaher_screen);

    //Init events for screen.
    events_init_weaher_screen(ui);
}
