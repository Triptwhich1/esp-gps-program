#include "screens.hpp"

LV_IMAGE_DECLARE(image_paint_3_dsc);
LV_IMAGE_DECLARE(image_paint_1_dsc);

lv_obj_t * label_time = nullptr;
lv_obj_t * label_route_points = nullptr;

namespace lvgl_screens {
    void draw_overview_screen() {
        if (lvgl_port_lock(0)) {
            lv_obj_t * image_paint_1 = lv_image_create(lv_screen_active());
            lv_image_set_src(image_paint_1, &image_paint_1_dsc);
            lv_obj_set_pos(image_paint_1, 4, 4);
            lv_obj_set_size(image_paint_1, 120, 56);

            lv_obj_t * image_paint_3 = lv_image_create(lv_screen_active());
            lv_image_set_src(image_paint_3, &image_paint_3_dsc);
            lv_obj_set_pos(image_paint_3, 47, 7);
            lv_obj_set_size(image_paint_3, 4, 53);

            label_time = lv_label_create(lv_screen_active());
            lv_obj_set_pos(label_time, 9, 9);
            lv_label_set_text(label_time, "00:00:00");
            lv_obj_set_style_text_font(label_time, &lv_font_montserrat_8, 0);

            label_route_points = lv_label_create(lv_screen_active());
            lv_obj_set_pos(label_route_points, 52, 9);
            lv_label_set_text(label_route_points, "Point no: %s");
            lv_obj_set_style_text_font(label_route_points, &lv_font_montserrat_8, 0);

            lvgl_port_unlock();
        }
    }
    void update_overview_screen(int point_number) {
        if (lvgl_port_lock(0)) {
            lv_label_set_text_fmt(label_route_points, "Point no: %d", point_number);
            lvgl_port_unlock();
        }
    }
}