#pragma once
#include "lvgl.h"
#include "esp_lvgl_port.h"

namespace lvgl_screens{
    void draw_overview_screen();
    void update_overview_screen(int point_number);
}