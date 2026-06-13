#pragma once
#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "route.hpp"

namespace lvgl_screens{
    void draw_overview_screen();
    void update_overview_screen(route* route_arg);
}