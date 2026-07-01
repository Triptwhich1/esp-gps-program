#include "screens.hpp"

static overview_screen_t overview_screen_data;

namespace overview_screen {
    void draw_overview_screen() {
        if (lvgl_port_lock(0)) {
            overview_screen_data.root = lv_obj_create(NULL);
            lv_screen_load(overview_screen_data.root);

            lv_obj_t * image_paint_1 = lv_image_create(lv_screen_active());
            lv_image_set_src(image_paint_1, &image_paint_1_dsc);
            lv_obj_set_pos(image_paint_1, 4, 4);
            lv_obj_set_size(image_paint_1, 120, 56);

            lv_obj_t * image_paint_3 = lv_image_create(lv_screen_active());
            lv_image_set_src(image_paint_3, &image_paint_3_dsc);
            lv_obj_set_pos(image_paint_3, 47, 7);
            lv_obj_set_size(image_paint_3, 4, 53);

            overview_screen_data.label_time = lv_label_create(lv_screen_active());
            lv_obj_set_pos(overview_screen_data.label_time, 9, 9);
            lv_label_set_text(overview_screen_data.label_time, "00:00:00");
            lv_obj_set_style_text_font(overview_screen_data.label_time, &lv_font_montserrat_8, 0);

            overview_screen_data.label_route_points = lv_label_create(lv_screen_active());
            lv_obj_set_pos(overview_screen_data.label_route_points, 52, 9);
            lv_label_set_text(overview_screen_data.label_route_points, "Point no: 0");
            lv_obj_set_style_text_font(overview_screen_data.label_route_points, &lv_font_montserrat_8, 0);

            overview_screen_data.label_latitude = lv_label_create(lv_screen_active());
            lv_obj_set_pos(overview_screen_data.label_latitude, 52, 17);
            lv_label_set_text(overview_screen_data.label_latitude, "");
            lv_obj_set_style_text_font(overview_screen_data.label_latitude, &lv_font_montserrat_8, 0);

            overview_screen_data.label_longitude = lv_label_create(lv_screen_active());
            lv_obj_set_pos(overview_screen_data.label_longitude, 52, 26);
            lv_label_set_text(overview_screen_data.label_longitude, "");
            lv_obj_set_style_text_font(overview_screen_data.label_longitude, &lv_font_montserrat_8, 0);

            lvgl_port_unlock();
        }
    }

    char* get_coord_as_string(float coord) {
        static char buffer[20];
        snprintf(buffer, sizeof(buffer), "%.6f", coord);
        return buffer;
    }

    void update_overview_screen(route* route_arg) {
        if (lv_scr_act() != overview_screen_data.root) {
            ESP_LOGW("LVGL", "Overview screen is not active, skipping update");
            return;
        }

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
            lv_label_set_text_fmt(overview_screen_data.label_route_points, "Point no: %d", route_arg->get_num_points());
            lv_label_set_text(overview_screen_data.label_latitude, get_coord_as_string(latest_point->latitude));
            lv_label_set_text(overview_screen_data.label_longitude, get_coord_as_string(latest_point->longitude));
            lvgl_port_unlock();
        }
    }

    void update_overview_screen_time(const char* time_str) {
        if (lvgl_port_lock(0)) {
            lv_label_set_text_fmt(overview_screen_data.label_time,
                "%.2s:%.2s:%.2s",
                time_str,
                time_str + 2,
                time_str + 4);
            lvgl_port_unlock();
        }
    }
}