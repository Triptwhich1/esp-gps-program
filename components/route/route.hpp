#pragma once

#include "gps_data.hpp"
#include <stdint.h>
#include "esp_log.h"

#define GPS_POINTS_MAX 2000

class route
{
private:
    uint8_t _route_id;
    char _time_started[12];
    char _time_ended[12];
    gps_data _gps_points[GPS_POINTS_MAX]; // roughly 16 hours of route tracking (with points taken every 30 seconds)
    gps_data *_first_gps_point;
    gps_data *_latest_gps_point;
    float _distance;
    uint16_t _num_points;
public:
    route();
    ~route();
    void append_to_route(const gps_data& point);
};