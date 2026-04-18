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



void setup_scr_t_h_screen(lv_ui *ui)
{
    //Write codes t_h_screen
    ui->t_h_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->t_h_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->t_h_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for t_h_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->t_h_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes t_h_screen_back1_btn
    ui->t_h_screen_back1_btn = lv_btn_create(ui->t_h_screen);
    ui->t_h_screen_back1_btn_label = lv_label_create(ui->t_h_screen_back1_btn);
    lv_label_set_text(ui->t_h_screen_back1_btn_label, "back");
    lv_label_set_long_mode(ui->t_h_screen_back1_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->t_h_screen_back1_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->t_h_screen_back1_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->t_h_screen_back1_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->t_h_screen_back1_btn, 241, 194);
    lv_obj_set_size(ui->t_h_screen_back1_btn, 65, 36);

    //Write style for t_h_screen_back1_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->t_h_screen_back1_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->t_h_screen_back1_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->t_h_screen_back1_btn, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->t_h_screen_back1_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->t_h_screen_back1_btn, lv_color_hex(0xe30707), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->t_h_screen_back1_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->t_h_screen_back1_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->t_h_screen_back1_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->t_h_screen_back1_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->t_h_screen_back1_btn, lv_color_hex(0xdf4289), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->t_h_screen_back1_btn, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->t_h_screen_back1_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->t_h_screen_back1_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes t_h_screen_btn_2
    ui->t_h_screen_btn_2 = lv_btn_create(ui->t_h_screen);
    ui->t_h_screen_btn_2_label = lv_label_create(ui->t_h_screen_btn_2);
    lv_label_set_text(ui->t_h_screen_btn_2_label, "温度");
    lv_label_set_long_mode(ui->t_h_screen_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->t_h_screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->t_h_screen_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->t_h_screen_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->t_h_screen_btn_2, 33, 53);
    lv_obj_set_size(ui->t_h_screen_btn_2, 79, 39);

    //Write style for t_h_screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->t_h_screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->t_h_screen_btn_2, lv_color_hex(0x180098), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->t_h_screen_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->t_h_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->t_h_screen_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->t_h_screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->t_h_screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->t_h_screen_btn_2, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->t_h_screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->t_h_screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes t_h_screen_btn_3
    ui->t_h_screen_btn_3 = lv_btn_create(ui->t_h_screen);
    ui->t_h_screen_btn_3_label = lv_label_create(ui->t_h_screen_btn_3);
    lv_label_set_text(ui->t_h_screen_btn_3_label, "湿度");
    lv_label_set_long_mode(ui->t_h_screen_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->t_h_screen_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->t_h_screen_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->t_h_screen_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->t_h_screen_btn_3, 33, 125);
    lv_obj_set_size(ui->t_h_screen_btn_3, 79, 39);

    //Write style for t_h_screen_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->t_h_screen_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->t_h_screen_btn_3, lv_color_hex(0x180098), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->t_h_screen_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->t_h_screen_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->t_h_screen_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->t_h_screen_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->t_h_screen_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->t_h_screen_btn_3, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->t_h_screen_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->t_h_screen_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes t_h_screen_temp_label
    ui->t_h_screen_temp_label = lv_label_create(ui->t_h_screen);
    lv_label_set_text(ui->t_h_screen_temp_label, "00.00℃");
    lv_label_set_long_mode(ui->t_h_screen_temp_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->t_h_screen_temp_label, 135, 53);
    lv_obj_set_size(ui->t_h_screen_temp_label, 100, 32);

    //Write style for t_h_screen_temp_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->t_h_screen_temp_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->t_h_screen_temp_label, &lv_font_SourceHanSerifSC_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->t_h_screen_temp_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->t_h_screen_temp_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->t_h_screen_temp_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes t_h_screen_humidity_label
    ui->t_h_screen_humidity_label = lv_label_create(ui->t_h_screen);
    lv_label_set_text(ui->t_h_screen_humidity_label, "00.00%RH");
    lv_label_set_long_mode(ui->t_h_screen_humidity_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->t_h_screen_humidity_label, 135, 129);
    lv_obj_set_size(ui->t_h_screen_humidity_label, 140, 32);

    //Write style for t_h_screen_humidity_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->t_h_screen_humidity_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->t_h_screen_humidity_label, &lv_font_SourceHanSerifSC_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->t_h_screen_humidity_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->t_h_screen_humidity_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->t_h_screen_humidity_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of t_h_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->t_h_screen);

    //Init events for screen.
    events_init_t_h_screen(ui);
}
