#pragma once
#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "route.hpp"
#include "qrcode.h"
#include "esp_log.h"
#include <cstring>


LV_IMAGE_DECLARE(image_paint_3_dsc);
LV_IMAGE_DECLARE(image_paint_1_dsc);

struct overview_screen_t {
    lv_obj_t * root;
    lv_obj_t * label_time;
    lv_obj_t * label_route_points;
    lv_obj_t * label_latitude;
    lv_obj_t * label_longitude;
};

struct qr_screen_t {
    lv_obj_t * root;
    lv_obj_t * canvas;
};

struct route_summary_screen_t {
    lv_obj_t * root;
    lv_obj_t * label_total_points;
    lv_obj_t * label_total_distance;
};

struct inactive_screen_t {
    lv_obj_t * root;
};

struct title_screen_t {
    lv_obj_t * root;
    lv_obj_t * label_title;
    lv_obj_t * label_continue;
};

struct main_menu_screen_t {
    lv_obj_t * root;
    lv_obj_t * button_start;
    lv_obj_t * button_settings;
};

struct popup_screen_t {
    lv_obj_t * root;
    lv_obj_t * label_message;
    lv_obj_t * button_ok;
    lv_obj_t * button_cancel;
};

namespace overview_screen {
    void draw_overview_screen();
    void update_overview_screen(route* route_arg);
}

namespace qr_code_screen {
    void draw_qr_screen();
}

namespace route_summary_screen {
    void draw_route_summary_screen();
}

namespace inactive_screen {
    void draw_inactive_screen();
}

namespace main_menu_screen {
    void draw_main_menu_screen();
}

namespace popup_screen {
    void draw_popup(const char* message);
}

namespace title_screen {
    void draw_title_screen();
}