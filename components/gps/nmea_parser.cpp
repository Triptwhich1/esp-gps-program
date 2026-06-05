#include "nmea_parser.hpp"
#include <string>
#include "esp_log.h"

struct coordinate {
    float latitude;
    float longitude;
    float altitude;
};

namespace NMEA{
    //$GPGLL,5224.88965,N,00404.93354,W,233722.00,A,A*7D
    coordinate get_coordinate(char* buffer, int ptr) {
        if (!buffer) return {0};
        char* gpgll = buffer + ptr;
        char* tok = strtok(gpgll, ",");
        char* lat_r; 
        char* lon_r;
        char* tm;
        char lat_d, lon_d;

        for (size_t i = 0; i < 6; i++) { // gets the important parameters...
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
            ESP_LOGI("TOKEN", "%s", tok);
            tok = strtok(NULL, ",");
        }
        return {0}; 
    }

    gps_data parse_nmea(char* buffer) {
        gps_data new_gps_data = {0};
        int ptr = 0;
        std::string str_buffer = buffer;
        ptr = str_buffer.find("$GPGLL", ptr);
        coordinate coord = get_coordinate(buffer, ptr);

        return{};
    }
}