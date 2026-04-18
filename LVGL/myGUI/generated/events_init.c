/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void time_screen_start_sw_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.time_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_time_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->time_screen_start_sw, time_screen_start_sw_event_handler, LV_EVENT_ALL, ui);
}

static void menu_screen_weather_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weaher_screen, guider_ui.weaher_screen_del, &guider_ui.menu_screen_del, setup_scr_weaher_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void menu_screen_t_h_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.t_h_screen, guider_ui.t_h_screen_del, &guider_ui.menu_screen_del, setup_scr_t_h_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void menu_screen_time_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.time_screen, guider_ui.time_screen_del, &guider_ui.menu_screen_del, setup_scr_time_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_menu_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menu_screen_weather_btn, menu_screen_weather_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_screen_t_h_btn, menu_screen_t_h_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_screen_time_btn, menu_screen_time_btn_event_handler, LV_EVENT_ALL, ui);
}

static void t_h_screen_back1_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.t_h_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_t_h_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->t_h_screen_back1_btn, t_h_screen_back1_btn_event_handler, LV_EVENT_ALL, ui);
}

static void weaher_screen_back2_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.weaher_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_weaher_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->weaher_screen_back2_btn, weaher_screen_back2_btn_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
