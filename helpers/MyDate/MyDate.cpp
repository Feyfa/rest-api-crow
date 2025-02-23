#include "MyDate.h"

std::string MyDate::now()
{
    std::time_t epoch_time = std::time(nullptr); //epoch time
    std::tm time; //buat variable penampung time
    localtime_s(&time, &epoch_time); //conver epoch time to time

    std::ostringstream oss; //mirip seperti cout, oss bisa menerima input apa saja
    oss << std::put_time(&time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}