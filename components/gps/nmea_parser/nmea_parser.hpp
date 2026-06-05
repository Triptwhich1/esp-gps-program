#pragma once
#include "../gps_data_t.hpp"
#include "string.h"

namespace NMEA{
    gps_data_t parse_nmea(char* buffer);
}