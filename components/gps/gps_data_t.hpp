#pragma once
#include <string>

struct gps_data_t {
    float latitude;
    float longitude;
    float altitude;
    std::string time;
};