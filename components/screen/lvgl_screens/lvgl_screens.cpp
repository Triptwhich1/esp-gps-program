#include "screens.hpp"

LV_IMAGE_DECLARE(image_paint_3_dsc);
LV_IMAGE_DECLARE(image_paint_1_dsc);

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

            lvgl_port_unlock();
        }
    }
}