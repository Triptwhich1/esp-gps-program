#pragma once

#include "qrcode_gen.h"
#include "esp_lvgl_port.h"
#include "lvgl.h"

#define QRCODE_SIZE 32
#define MODULE_SIZE 2

static uint8_t canvas_buffer[LV_CANVAS_BUF_SIZE(QRCODE_SIZE, QRCODE_SIZE, 1, 1)];
static lv_obj_t *canvas_obj;
static lv_obj_t *qr_screen;

namespace qr_code {
    void qr_canvas_init() {
        canvas_obj = lv_canvas_create(lv_scr_act());
        lv_canvas_set_buffer(canvas_obj, canvas_buffer, QRCODE_SIZE, QRCODE_SIZE, LV_COLOR_FORMAT_I1);
        lv_obj_center(canvas_obj);
    }

    void draw_qr_code(const char* text)
    {
        const uint8_t* qrcode_text = reinterpret_cast<const uint8_t*>(text);
        int border = 4;
        int start_x = 31;
        int start_y = 0;

        for (int y = -border; y < qrcodegen_getSize(qrcode_text) + border; y++) {
            for (int x = -border; x < qrcodegen_getSize(qrcode_text) + border; x++) {

                lv_color_t color = qrcodegen_getModule(qrcode_text, x, y)
                    ? lv_color_black()
                    : lv_color_white();

                int px = start_x + (x + border) * MODULE_SIZE;
                int py = start_y + (y + border) * MODULE_SIZE;

                lv_canvas_set_px(canvas_obj, px,     py,     color, LV_OPA_COVER);
                lv_canvas_set_px(canvas_obj, px + 1, py,     color, LV_OPA_COVER);
                lv_canvas_set_px(canvas_obj, px,     py + 1, color, LV_OPA_COVER);
                lv_canvas_set_px(canvas_obj, px + 1, py + 1, color, LV_OPA_COVER);
            }
        }
    }

    void qr_screen_init() {
        qr_screen = lv_obj_create(NULL);
    }

    void load_qr_screen() {
        lv_scr_load(qr_screen);
    }

}