#include "draw_qr.hpp"

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
        lv_color_t fg_color = lv_color_black();
        lv_color_t bg_color = lv_color_white();

        ESP_LOGI("info", "Drawing QR code: %s", text);

        lv_obj_t *qr = lv_qrcode_create(canvas_obj);

        lv_qrcode_set_size(qr, QRCODE_SIZE * 2);
        lv_qrcode_update(qr, text, strlen(text));
        lv_obj_center(qr);

        lv_obj_set_style_border_color(qr, bg_color, 0);
        lv_obj_set_style_border_width(qr, 5, 0);
    }

    void qr_screen_init() {
        qr_screen = lv_obj_create(NULL);
    }

    void load_qr_screen() {
        lv_scr_load(qr_screen);
    }

}