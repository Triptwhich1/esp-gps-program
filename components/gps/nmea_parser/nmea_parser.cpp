#include "nmea_parser.hpp"
#include <string>
#include "esp_log.h"

struct coordinate {
    float latitude;
    float longitude;
    float altitude;
};

namespace NMEA{
    float get_real_coordinate(char* raw_data, char direction) {
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
        coordinate new_coordinate;
        char* gpgll = buffer + ptr;
        char* tok = strtok(gpgll, ",");
        char* lat_r; 
        char* lon_r;
        char* tm;
        char lat_d, lon_d;

        for (size_t i = 0; i < 6; i++) { // gets the important parameters...
            if (tok == nullptr) {
                ESP_LOGI("NMEA", "Incomplete GPGLL Seqeuence");
                return {0};
            }
            switch (i) {  
                case 1:
                    lat_r = tok;
                    break;
                case 2:
                    lat_d = tok[0];
                    break;
                case 3:
                    lon_r = tok;
                    break;
                case 4:
                    lon_d = tok[0];
                    break;
                case 5:
                    tm = tok;
                    break;
                default:
                    break;
            }
            // ESP_LOGI("TOKEN", "%s", tok);
            tok = strtok(NULL, ",");
        }

        new_coordinate.latitude = get_real_coordinate(lat_r, lat_d);
        ESP_LOGI("COORD", "%f", new_coordinate.latitude);
        new_coordinate.longitude = get_real_coordinate(lon_r, lon_d);
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