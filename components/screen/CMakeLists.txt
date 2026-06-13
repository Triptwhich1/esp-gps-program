idf_component_register(SRCS "screen.cpp" "i2c_setup/i2c_setup.cpp" "lvgl_setup/lvgl_setup.cpp" "lvgl_screens/lvgl_screens.cpp" "lvgl_screens/images/paint_1.c" "lvgl_screens/images/paint_3.c"
                    INCLUDE_DIRS "." "i2c_setup" "lvgl_setup" "args" "lvgl_screens" "lvgl_screens/images"
                    REQUIRES driver esp_lcd lvgl esp_lvgl_port route)

