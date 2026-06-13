#include "timer.hpp"

timer::timer(uint8_t interval) : _interval(interval) {
}

timer::~timer() {}

void timer::set_interval(uint8_t interval) {
    _interval = interval;
}

uint8_t timer::get_interval() {
    return _interval;
}