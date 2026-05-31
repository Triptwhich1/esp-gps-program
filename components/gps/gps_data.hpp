#pragma once

struct gps_data {
    float latitude;
    float longitude;
    float altitude;
    char time[12];
    char date[8];
};