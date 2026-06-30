#include "screens.hpp"

LV_IMAGE_DECLARE(image_paint_3_dsc);
LV_IMAGE_DECLARE(image_paint_1_dsc);

lv_obj_t * label_time = nullptr;
lv_obj_t * label_route_points = nullptr;
lv_obj_t * label_latitude = nullptr;
lv_obj_t * label_longitude = nullptr;

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
            lv_label_set_text(label_route_points, "Point no: 0");
            lv_obj_set_style_text_font(label_route_points, &lv_font_montserrat_8, 0);

            label_latitude = lv_label_create(lv_screen_active());
            lv_obj_set_pos(label_latitude, 52, 17);
            lv_label_set_text(label_latitude, "");
            lv_obj_set_style_text_font(label_latitude, &lv_font_montserrat_8, 0);

            label_longitude = lv_label_create(lv_screen_active());
            lv_obj_set_pos(label_longitude, 52, 26);
            lv_label_set_text(label_longitude, "");
            lv_obj_set_style_text_font(label_longitude, &lv_font_montserrat_8, 0);

            lvgl_port_unlock();
        }
    }

    char* get_coord_as_string(float coord) {
        static char buffer[20];
        snprintf(buffer, sizeof(buffer), "%.6f", coord);
        return buffer;
    }

    void update_overview_screen(route* route_arg) {
        if (route_arg == nullptr) {
            ESP_LOGE("LVGL", "Route argument is null");
            return;
        }
        gps_data_t* latest_point = route_arg->get_latest_gps_point();
        if (latest_point == nullptr) {
            ESP_LOGW("LVGL", "No GPS points available in the route");
            return;
        }
        if (lvgl_port_lock(0)) {
            lv_label_set_text_fmt(label_route_points, "Point no: %d", route_arg->get_num_points());
            lv_label_set_text(label_latitude, get_coord_as_string(latest_point->latitude));
            lv_label_set_text(label_longitude, get_coord_as_string(latest_point->longitude));
            lv_label_set_text_fmt(label_time,
                                "%.2s:%.2s:%.2s",
                                latest_point->time,
                                latest_point->time + 2,
                                latest_point->time + 4);
            lvgl_port_unlock();
        }
    }
}