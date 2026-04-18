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



void setup_scr_time_screen(lv_ui *ui)
{
    //Write codes time_screen
    ui->time_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->time_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->time_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for time_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->time_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes time_screen_time_label
    ui->time_screen_time_label = lv_label_create(ui->time_screen);
    lv_label_set_text(ui->time_screen_time_label, "00:00:00");
    lv_label_set_long_mode(ui->time_screen_time_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->time_screen_time_label, 56, 73);
    lv_obj_set_size(ui->time_screen_time_label, 204, 80);

    //Write style for time_screen_time_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->time_screen_time_label, lv_color_hex(0xff00e9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->time_screen_time_label, &lv_font_SourceHanSerifSC_Regular_47, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->time_screen_time_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->time_screen_time_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->time_screen_time_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes time_screen_date_label
    ui->time_screen_date_label = lv_label_create(ui->time_screen);
    lv_label_set_text(ui->time_screen_date_label, "2026.04.18");
    lv_label_set_long_mode(ui->time_screen_date_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->time_screen_date_label, 202, 12);
    lv_obj_set_size(ui->time_screen_date_label, 100, 32);

    //Write style for time_screen_date_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->time_screen_date_label, lv_color_hex(0x0117ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->time_screen_date_label, &lv_font_SourceHanSerifSC_Regular_19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->time_screen_date_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->time_screen_date_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->time_screen_date_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes time_screen_start_label
    ui->time_screen_start_label = lv_label_create(ui->time_screen);
    lv_label_set_text(ui->time_screen_start_label, "start");
    lv_label_set_long_mode(ui->time_screen_start_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->time_screen_start_label, 72, 170);
    lv_obj_set_size(ui->time_screen_start_label, 100, 32);

    //Write style for time_screen_start_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->time_screen_start_label, lv_color_hex(0x248a03), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->time_screen_start_label, &lv_font_SourceHanSerifSC_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->time_screen_start_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->time_screen_start_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->time_screen_start_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes time_screen_start_sw
    ui->time_screen_start_sw = lv_switch_create(ui->time_screen);
    lv_obj_set_pos(ui->time_screen_start_sw, 165, 174);
    lv_obj_set_size(ui->time_screen_start_sw, 40, 20);

    //Write style for time_screen_start_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->time_screen_start_sw, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->time_screen_start_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->time_screen_start_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->time_screen_start_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->time_screen_start_sw, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->time_screen_start_sw, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for time_screen_start_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->time_screen_start_sw, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->time_screen_start_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->time_screen_start_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->time_screen_start_sw, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for time_screen_start_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->time_screen_start_sw, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->time_screen_start_sw, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->time_screen_start_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->time_screen_start_sw, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->time_screen_start_sw, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes time_screen_slogan_label
    ui->time_screen_slogan_label = lv_label_create(ui->time_screen);
    lv_label_set_text(ui->time_screen_slogan_label, "开始搬砖！");
    lv_label_set_long_mode(ui->time_screen_slogan_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->time_screen_slogan_label, 13, 15);
    lv_obj_set_size(ui->time_screen_slogan_label, 152, 41);

    //Write style for time_screen_slogan_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->time_screen_slogan_label, lv_color_hex(0xe30202), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->time_screen_slogan_label, &lv_font_SourceHanSerifSC_Regular_23, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->time_screen_slogan_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->time_screen_slogan_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->time_screen_slogan_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of time_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->time_screen);

    //Init events for screen.
    events_init_time_screen(ui);
}
