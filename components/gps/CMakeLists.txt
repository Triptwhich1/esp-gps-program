idf_component_register(SRCS "gps.cpp" "nmea_parser/nmea_parser.cpp"
                    INCLUDE_DIRS "." "nmea_parser"
                    REQUIRES driver)