#include "route.hpp"

route::route(/* args */)
{
    _num_points = 0; // sets first current point
}

route::~route()
{
}

bool check_if_valid_gps_point(gps_data_t point, gps_data_t prev_point) {
    if (point.latitude == 0.0 && point.longitude == 0.0 && point.altitude == 0.0) return false;
    if (abs(point.latitude) > 90 || abs(point.longitude) > 180) return false;
    return true;
}

void route::append_to_route(const gps_data_t& point)
{
    if (_num_points >= GPS_POINTS_MAX)
    {
        ESP_LOGE("APPEND", "No space left within current route");
        return;
    }

    switch (_num_points) {
        case 0:
            _first_gps_point = &_gps_points[0];
            _latest_gps_point = &_gps_points[0];
            break;
        default:
            _latest_gps_point = &_gps_points[_num_points - 1];
            break;
    }

    _latitude_sum += point.latitude;
    _longitude_sum += point.longitude;
    float avg_latitude = _latitude_sum / (_num_points + 1);
    float avg_longitude = _longitude_sum / (_num_points + 1);

    const float padding = 3.0f;
    if (point.latitude < (avg_latitude - padding) ||
        point.longitude < (avg_longitude - padding)) {
            ESP_LOGW("APPEND", "Point is outside of average bounds, skipping");
            return;
        }

    if (!check_if_valid_gps_point(point, *_latest_gps_point))
    {
        ESP_LOGW("APPEND", "Invalid point, skipping");
        return;
    }

    _gps_points[_num_points] = point;
    _num_points++;
    ESP_LOGI("APPEND", "Number of points: %d", _num_points);
}

uint16_t route::get_num_points() {
    return _num_points;
}

gps_data_t* route::get_latest_gps_point() {
    if (_num_points == 0) {
        return nullptr;
    }
    return &_gps_points[_num_points - 1];
}