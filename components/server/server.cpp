#include "server.hpp"

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {

}

namespace server {
    void wifi_init() {
        ESP_LOGI("Server", "Initializing Wi-Fi");
        
        wifi_config_t cfg = {
            .ap = {
                .ssid = "ESP32_AP",
                .password = "esp32password",
                .ssid_len = 0,
                .channel = 1,
                .authmode = WIFI_AUTH_WPA2_PSK,
                .ssid_hidden = 0,
                .max_connection = 1,
                .beacon_interval = 100
            },
        };

        esp_wifi_set_mode(WIFI_MODE_AP);
        esp_wifi_set_config(WIFI_IF_AP, &cfg);
        esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
        ESP_LOGI("Server", "Wi-Fi initialized");
    }

    void start_server() {
        ESP_LOGI("Server", "Starting server");
        // Start the server here
    }
}