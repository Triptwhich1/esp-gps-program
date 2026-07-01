#include "screens.hpp"

static main_menu_screen_t main_menu_data;

namespace main_menu {
    void draw_main_menu() {
        if (lvgl_port_lock(0)) {
            main_menu_data.root = lv_obj_create(NULL);
            lv_screen_load(main_menu_data.root);
            lvgl_port_unlock();
        }
    }
}