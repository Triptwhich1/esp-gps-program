#include "tasks.hpp"
namespace gps_tasks {
    void rx_task(void *arg)
    {
        gps_rx_task_args_t *task_args = static_cast<gps_rx_task_args_t*>(arg);
        gps *gps_arg = task_args->gps_arg;
        QueueHandle_t queue_arg = task_args->queue_arg;
        ESP_LOGI("GPS", "port: %d", (int)gps_arg->get_uart_port());
        uint8_t buffer[BUFFER_SIZE];
        while (1) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            const int rxBytes = uart_read_bytes(gps_arg->get_uart_port(), buffer, BUFFER_SIZE, pdMS_TO_TICKS(1000));
            if (rxBytes > 0) {
                gps_data_t gps_data = NMEA::parse_nmea((char*)buffer);
                if (gps_data.altitude == 0.0 && gps_data.latitude == 0.0 && gps_data.longitude == 0) {
                    ESP_LOGI("GPS", "Invalid data");
                } else {
                    xQueueSend(queue_arg, &gps_data, pdMS_TO_TICKS(10));
                }
            } else {
                ESP_LOGW("GPS", "No data received");
            }
        }
    }
}
