#include "bcalendar.hpp"

BCalendar::Bcalendar() {
    today = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

BCalendar::~Bcalendar() {
}

date_t BCalendar::get_business_day() {
    return today;
}

date_t::date_t(time_t current_time) {

}

date_t::date_t(string holiday) {
    
}
