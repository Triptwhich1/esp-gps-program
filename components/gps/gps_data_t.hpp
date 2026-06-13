#pragma once
#include <string>

struct gps_data_t {
    float latitude;
    float longitude;
    float altitude;
    char time[7];
};