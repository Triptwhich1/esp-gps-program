#include "nmea_parser.hpp"
#include <string>
#include "esp_log.h"

struct gpgga_data_t {
    char time[7];
    float latitude;
    float longitude;
    uint8_t fix_quality;
    float altitude;
};

namespace NMEA{
    float get_real_coordinate(const char* raw_data, char direction) { // gets decimal coordinate
        if (!raw_data || !direction) return 0; 
        float long_data = strtof(raw_data, NULL);
        int degrees = (int)long_data / 100;
        float minutes = long_data - degrees * 100;
        float decimal_val = degrees + (minutes/60);
        if (direction == 'S' || direction == 'W') {
            return -decimal_val;
        } else {
            return decimal_val;
        }
    }

   
    gpgga_data_t parse_gpgga(char* buffer, int ptr) {
        if (!buffer) return {};
        gpgga_data_t gpgga_data{};

        char* start = buffer + ptr;
        char* end = nullptr;
        std::string lat_r; 
        std::string lon_r;
        std::string gpgga_tm;
        char lat_d = '\0';
        char lon_d = '\0';

        for (size_t i = 0; i < 10; i++) { // gets the important parameters...
            end = strchr(start, ',');

            if (!end) {
                ESP_LOGI("NMEA", "Incomplete GPGGA Sequence");
                return {};
            }

            size_t len = end - start; 

            switch (i) {  
                case 1:
                    gpgga_tm.assign(start, len);
                    strncpy(gpgga_data.time, gpgga_tm.c_str(), sizeof(gpgga_data.time) - 1);
                    break;
                case 2:
                    lat_r.assign(start, len);
                    break;
                case 3:
                    lat_d = (len > 0) ? *start : '\0';
                    break;
                case 4:
                    lon_r.assign(start, len);
                    break;
                case 5:
                    lon_d = (len > 0) ? *start : '\0';
                    break;
                case 6:
                    gpgga_data.fix_quality = (len > 0) ? *start - '0' : 0;
                    break;
                case 9: 
                    gpgga_data.altitude = std::atof(start);
                    break;
                default:
                    break;
            }
            start = end + 1;
        }

        gpgga_data.latitude = get_real_coordinate(lat_r.c_str(), lat_d);
        gpgga_data.longitude = get_real_coordinate(lon_r.c_str(), lon_d);

        ESP_LOGI("GPGGA", "Time: %s", gpgga_data.time);
        if (gpgga_data.fix_quality == 0) {
            ESP_LOGW("GPGGA", "No GPS fix");
            return {};
        } else {
            ESP_LOGI("GPGGA", "Fix acquired: quality=%d", gpgga_data.fix_quality);
        }
        ESP_LOGI("GPGGA", "Parsed lat=%.6f lon=%.6f fix=%d",
                    gpgga_data.latitude,
                    gpgga_data.longitude,
                    gpgga_data.fix_quality);
        ESP_LOGI("GPGGA", "Altitude: %.2f", gpgga_data.altitude);

        return gpgga_data;
    }

    gps_data_t parse_nmea(char* buffer) {
        gps_data_t gps_data = {0};
        size_t ptr = 0;
        std::string str_buffer = buffer;

        ptr = str_buffer.find("$GPGGA");
        gpgga_data_t gpgga_data = parse_gpgga(buffer, ptr);

        if (gpgga_data.fix_quality == 0) return {}; // if nothing 

        gps_data.altitude = gpgga_data.altitude;
        gps_data.latitude = gpgga_data.latitude;
        gps_data.longitude = gpgga_data.longitude;
        strncpy(gps_data.time, gpgga_data.time, sizeof(gpgga_data.time) - 1);

        return gps_data;
    }
}