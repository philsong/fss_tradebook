#ifndef BCALENDAR_HPP
#define BCALENDAR_HPP

#include <chrono>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

// http://www.cplusplus.com/reference/iomanip/get_time/

class date_t {
private:
    time_t time;
public:
    date_t(time_t current_time);
    date_t(string holiday);
}

class BCalendar {
private:
    /// NYSE Holiday Calendar
    vector<date_t> holidays {
        "1/1/2015",
        "1/1/2016",
        "1/19/2015",
        "1/18/2016",
        "2/16/2015",
        "2/15/2016",
        "4/3/2015",
        "3/25/2016",
        "5/25/2015",
        "5/30/2016",
        "7/3/2015",
        "7/4/2016",
        "9/7/2015",
        "9/5/2016",
        "11/26/2015",
        "11/24/2016",
        "12/25/2015",
        "12/26/2015"
    };
    /// Current date
    date_t today;
    /// Next business day (today if not a holiday)
    date_t nextBusinessDay;
public:
    BCalendar();
    ~BCalendar();
    date_t get_business_day();
};

#endif // BCALENDAR_HPP
