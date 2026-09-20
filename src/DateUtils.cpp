// DateUtils.cpp
#include "DateUtils.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>

std::string DateUtils::getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &t);   // MinGW/Windows: safer, thread-local version
#else
    localtime_r(&t, &localTime);   // POSIX (Linux/Mac): thread-safe equivalent
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    return oss.str();
}