idf_component_register(SRCS "main.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES gps route args tasks timer screen button nav server)

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++11)