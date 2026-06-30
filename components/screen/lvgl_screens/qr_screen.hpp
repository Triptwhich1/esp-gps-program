#pragma once

#include "esp_lvgl_port.h"
#include "lvgl.h"
#include "qrcode.h"
#include "esp_log.h"
#include <cstring>

namespace qr_code {
    void qr_canvas_init();
    void draw_qr_code(const char* qrcode);
    void qr_screen_init();
    void load_qr_screen();
}