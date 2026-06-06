#include "nmea_parser.hpp"
#include <string>
#include "esp_log.h"

struct coordinate {
    float latitude;
    float longitude;
    float altitude;
};

namespace NMEA{
    float get_real_coordinate(const char* raw_data, char direction) {
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
    //$GPGLL,5224.88965,N,00404.93354,W,233722.00,A,A*7D
    coordinate get_coordinate(char* buffer, int ptr) {
        if (!buffer) return {0};
        coordinate new_coordinate{};

        char* start = buffer + ptr;
        char* end = nullptr;
        std::string lat_r; 
        std::string lon_r;
        std::string tm;
        char lat_d, lon_d;

        for (size_t i = 0; i < 6; i++) { // gets the important parameters...
            end = strchr(start, ',');

            if (!end) {
                ESP_LOGI("NMEA", "Incomplete GPGLL Seqeuence");
                return {0};
            }

            size_t len = end - start; 

            switch (i) {  
                case 1:
                    lat_r.assign(start, len);
                    break;
                case 2:
                    lat_d = *start;
                    break;
                case 3:
                    lon_r.assign(start, len);
                    break;
                case 4:
                    lon_d = *start;
                    break;
                case 5:
                    tm.assign(start, len);
                    break;
                default:
                    break;
            }
            start = end + 1;
        }

        new_coordinate.latitude = get_real_coordinate(lat_r.c_str(), lat_d);
        ESP_LOGI("COORD", "%f", new_coordinate.latitude);
        new_coordinate.longitude = get_real_coordinate(lon_r.c_str(), lon_d);
        ESP_LOGI("COORD", "%f", new_coordinate.longitude);

        return {0}; 
    }

    gps_data_t parse_nmea(char* buffer) {
        gps_data_t new_gps_data = {0};
        int ptr = 0;
        std::string str_buffer = buffer;
        ptr = str_buffer.find("$GPGLL", ptr);
        coordinate coord = get_coordinate(buffer, ptr);

        return{};
    }
}