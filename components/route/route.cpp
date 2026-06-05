#include "route.hpp"

route::route(/* args */)
{
    _num_points = 0; // sets first current point
}

route::~route()
{
}

void route::append_to_route(const gps_data& point)
{
    if (_num_points >= GPS_POINTS_MAX)
    {
        ESP_LOGE("APPEND", "No space left within current route");
        return;
    }

    _gps_points[_num_points] = point;
    _num_points++;
}