#include "screen.hpp"

static title_screen_t title_screen_data;

namespace title_screen {
    void draw_title_screen() {
        if (lvgl_port_lock(0)) {
            title_screen_data.root = lv_obj_create(NULL);
            lv_screen_load(title_screen_data.root);

            title_screen_data.label_title = lv_label_create(lv_scr_act());
            lv_label_set_text(title_screen_data.label_title, "GPS Nav System");
            lv_obj_set_pos(title_screen_data.label_title, 4, 5);
            lv_obj_set_style_text_font(title_screen_data.label_title, &lv_font_montserrat_14, 0);

            title_screen_data.label_continue = lv_label_create(lv_scr_act());
            lv_label_set_text(title_screen_data.label_continue, "Press button to continue");
            lv_obj_set_pos(title_screen_data.label_continue, 20, 50);
            lv_obj_set_style_text_font(title_screen_data.label_continue, &lv_font_montserrat_8, 0);

            lvgl_port_unlock();
        }
    }
}