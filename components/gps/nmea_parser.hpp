#pragma once
#include "gps_data.hpp"
#include "string.h"

namespace NMEA{
    gps_data parse_nmea(char* buffer);
}