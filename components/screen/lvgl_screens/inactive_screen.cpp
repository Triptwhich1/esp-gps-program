#include "screens.hpp"

static inactive_screen_t inactive_screen_data;

namespace inactive_screen {
    void draw_inactive_screen() {
        if (lvgl_port_lock(0)) {
            inactive_screen_data.root = lv_obj_create(NULL);
            lv_screen_load(inactive_screen_data.root);
            lvgl_port_unlock();
        }
    }
}