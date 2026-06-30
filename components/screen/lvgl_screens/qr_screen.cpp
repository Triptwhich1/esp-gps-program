#include "screens.hpp"

#define QRCODE_SIZE 32
#define MODULE_SIZE 2

static uint8_t canvas_buffer[LV_CANVAS_BUF_SIZE(QRCODE_SIZE, QRCODE_SIZE, 1, 1)];
static qr_screen_t qr_screen_data;

namespace qr_code_screen {
    void qr_canvas_init() {
        qr_screen_data.canvas = lv_canvas_create(lv_scr_act());
        lv_canvas_set_buffer(qr_screen_data.canvas, canvas_buffer, QRCODE_SIZE, QRCODE_SIZE, LV_COLOR_FORMAT_I1);
        lv_obj_center(qr_screen_data.canvas);
    }

    void draw_qr_code(const char* text)
    {
        lv_color_t fg_color = lv_color_black();
        lv_color_t bg_color = lv_color_white();

        ESP_LOGI("info", "Drawing QR code: %s", text);

        lv_obj_t *qr = lv_qrcode_create(qr_screen_data.canvas);

        lv_qrcode_set_size(qr, QRCODE_SIZE * 2);
        lv_qrcode_update(qr, text, strlen(text));
        lv_obj_center(qr);

        lv_obj_set_style_border_color(qr, bg_color, 0);
        lv_obj_set_style_border_width(qr, 5, 0);
    }

    void draw_qr_screen() {
        if (lvgl_port_lock(0)) {
            qr_screen_data.root = lv_obj_create(NULL);
            lv_screen_load(qr_screen_data.root);

            lv_obj_t * image_paint_1 = lv_image_create(lv_screen_active());
            lv_image_set_src(image_paint_1, &image_paint_1_dsc);
            lv_obj_set_pos(image_paint_1, 4, 4);
            lv_obj_set_size(image_paint_1, 120, 56);

            qr_canvas_init();
            draw_qr_code("Hello, QR Code!");

            lvgl_port_unlock();
        }
    }



}