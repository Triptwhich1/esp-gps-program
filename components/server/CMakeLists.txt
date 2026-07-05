idf_component_register(SRCS "server.cpp" "dns_server/dns_server.cpp"
                    INCLUDE_DIRS "." "dns_server"
                    REQUIRES esp_wifi esp_netif nvs_flash lwip tasks) 

