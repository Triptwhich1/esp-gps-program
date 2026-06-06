#pragma once

#include "gps_data_t.hpp"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "nmea_parser/nmea_parser.hpp"

#define BUFFER_SIZE 512

class gps
{
private:
    uart_port_t _port;
    gpio_num_t _rx_pin;
public:
    gps(uart_port_t port, gpio_num_t rx_pin);
    ~gps();
    void init();
    uart_port_t get_uart_port();
};