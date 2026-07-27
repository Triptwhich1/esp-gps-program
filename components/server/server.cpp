#include "server.hpp"

extern const char script_js_start[] asm("_binary_script_js_start");
extern const char script_js_end[]   asm("_binary_script_js_end");

extern const char style_css_start[] asm("_binary_style_css_start");
extern const char style_css_end[]   asm("_binary_style_css_end");

extern const char three_min_js_start[] asm("_binary_three_min_js_start");
extern const char three_min_js_end[]   asm("_binary_three_min_js_end");

extern const char three_controls_js_start[] asm("_binary_OrbitControls_js_start");
extern const char three_controls_js_end[]   asm("_binary_OrbitControls_js_end");

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *)event_data;
        ESP_LOGI("Server", "station " MACSTR " join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *)event_data;
        ESP_LOGI("Server", "station " MACSTR " leave, AID=%d, reason=%d",
                 MAC2STR(event->mac), event->aid, event->reason);
    }
}

namespace server {
    void wifi_init() {
        ESP_LOGI("Server", "Initializing Wi-Fi");
        
        esp_netif_init();
        esp_event_loop_create_default();
        esp_netif_create_default_wifi_ap();

        wifi_init_config_t init_cfg = WIFI_INIT_CONFIG_DEFAULT();

        esp_wifi_init(&init_cfg);

        esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);

        wifi_config_t wifi_cfg = {
            .ap = {
                .ssid = "ESP32_AP",
                .password = "esp32password",
                .ssid_len = 0,
                .channel = 1,
                .authmode = WIFI_AUTH_WPA2_PSK,
                .ssid_hidden = 0,
                .max_connection = 1,
                .beacon_interval = 100
            },
        };

        esp_wifi_set_mode(WIFI_MODE_AP);
        esp_wifi_set_config(WIFI_IF_AP, &wifi_cfg);
        esp_wifi_start();
        ESP_LOGI("Server", "Wi-Fi initialized");
    }

    static esp_err_t root_get_handler(httpd_req_t *req)
    {
        const uint32_t root_len = root_end - root_start;

        ESP_LOGI("Server", "Serve root");
        httpd_resp_set_type(req, "text/html");
        httpd_resp_send(req, root_start, root_len);

        return ESP_OK;
    }

    static const httpd_uri_t root = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = root_get_handler
    };

        static esp_err_t script_js_get_handler(httpd_req_t *req)
    {
        const uint32_t len = script_js_end - script_js_start;
        httpd_resp_set_type(req, "application/javascript");
        httpd_resp_send(req, script_js_start, len);
        return ESP_OK;
    }

    static const httpd_uri_t script_js_uri = {
        .uri = "/script.js",
        .method = HTTP_GET,
        .handler = script_js_get_handler
    };

    static esp_err_t style_css_get_handler(httpd_req_t *req)
    {
        const uint32_t len = style_css_end - style_css_start;
        httpd_resp_set_type(req, "text/css");
        httpd_resp_send(req, style_css_start, len);
        return ESP_OK;
    }

    static const httpd_uri_t style_css_uri = {
        .uri = "/style.css",
        .method = HTTP_GET,
        .handler = style_css_get_handler
    };

    static esp_err_t three_min_js_get_handler(httpd_req_t *req)
    {
        const uint32_t len = three_min_js_end - three_min_js_start;
        httpd_resp_set_type(req, "application/javascript");
        httpd_resp_send(req, three_min_js_start, len);
        return ESP_OK;
    }

    static const httpd_uri_t three_min_js_uri = {
        .uri = "/inc/three.min.js",
        .method = HTTP_GET,
        .handler = three_min_js_get_handler
    };

    static esp_err_t three_controls_js_get_handler(httpd_req_t *req)
    {
        const uint32_t len = three_controls_js_end - three_controls_js_start;
        httpd_resp_set_type(req, "application/javascript");
        httpd_resp_send(req, three_controls_js_start, len);
        return ESP_OK;
    }

    static const httpd_uri_t three_controls_js_uri = {
        .uri = "/inc/OrbitControls.js",
        .method = HTTP_GET,
        .handler = three_controls_js_get_handler
    };

    // HTTP Error (404) Handler - Redirects all requests to the root page
    esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
    {
        const uint32_t root_len = root_end - root_start;

        // Set status
        httpd_resp_set_status(req, "200 OK");
        // Redirect to the "/" root directory
        httpd_resp_set_type(req, "text/html");
        // iOS requires content in the response to detect a captive portal, simply redirecting is not sufficient.
        httpd_resp_send(req, root_start, root_len);

        ESP_LOGI("Server", "Redirecting to root (requested: %s)", req->uri);
        return ESP_OK;
    }

    static httpd_handle_t start_webserver(void)
    {
        httpd_handle_t server = NULL;
        httpd_config_t config = HTTPD_DEFAULT_CONFIG();
        config.max_open_sockets = 5;
        config.lru_purge_enable = true;

        // Start the httpd server
        ESP_LOGI("Server", "Starting server on port: '%d'", config.server_port);
        if (httpd_start(&server, &config) == ESP_OK) {
            // Set URI handlers
            ESP_LOGI("Server", "Registering URI handlers");
            httpd_register_uri_handler(server, &root);
            httpd_register_uri_handler(server, &script_js_uri);
            httpd_register_uri_handler(server, &style_css_uri);
            httpd_register_uri_handler(server, &three_min_js_uri);
            httpd_register_uri_handler(server, &three_controls_js_uri);
            httpd_register_err_handler(server, HTTPD_404_NOT_FOUND, http_404_error_handler);
        }
        return server;
    }

    void start_server() {
        wifi_init();
        ESP_LOGI("Server", "Starting server");

        // Configure DNS-based captive portal, if configured
        #ifdef CONFIG_ESP_ENABLE_DHCP_CAPTIVEPORTAL
            dhcp_set_captiveportal_url();
        #endif

        // Start the server for the first time
        start_webserver();

        // Start the DNS server that will redirect all queries to the softAP IP
        dns_server_config_t config = DNS_SERVER_CONFIG_SINGLE("*" /* all A queries */, "WIFI_AP_DEF" /* softAP netif ID */);
        dns_server::start_dns_server(&config);
    }
}