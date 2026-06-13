#include "route.hpp"

route::route(/* args */)
{
    _num_points = 0; // sets first current point
}

route::~route()
{
}

void route::append_to_route(const gps_data_t& point)
{
    if (_num_points >= GPS_POINTS_MAX)
    {
        ESP_LOGE("APPEND", "No space left within current route");
        return;
    }

    if (point.latitude == 0.0 && point.longitude == 0.0 && point.altitude == 0.0)
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