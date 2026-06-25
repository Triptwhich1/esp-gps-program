#pragma once

#include "draw_qr.hpp"

namespace qr_code {
    void qr_canvas_init();
    void draw_qr_code(const char* qrcode);
    void qr_screen_init();
    void load_qr_screen();
}