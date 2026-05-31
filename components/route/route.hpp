#pragma once

#include "gps_data.hpp"
#include <stdint.h>

class route
{
private:
    char _time_started[12];
    char _time_ended[12];
    gps_data _gps_points[2000]; // roughly 16 hours of route tracking (with points taken every 30 seconds)
    uint16_t _curr_point;
    gps_data *_first_gps_point;
    gps_data *_latest_gps_point;
    float distance;
public:
    route();
    ~route();
    void append_to_route(gps_data curr_gps_data);
};