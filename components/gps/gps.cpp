#include "gps.hpp"

gps::gps(uart_port_t port, gpio_num_t rx_pin) : _port(port), _rx_pin(rx_pin)
{
}

gps::~gps()
{
}

uart_port_t gps::get_uart_port() {
    return _port;
}

void gps::init() {
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    ESP_ERROR_CHECK(uart_param_config(_port, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(_port, UART_PIN_NO_CHANGE, _rx_pin, GPIO_NUM_NC, GPIO_NUM_NC));
    ESP_ERROR_CHECK(uart_driver_install(_port, BUFFER_SIZE, 0, 0, NULL, 0));
}