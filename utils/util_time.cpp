
#include "util_time.h"

string format_date()
{
    /// Although not defined, this is almost always an integral value holding the number of seconds (not counting leap seconds)
    /// since 00:00, Jan 1 1970 UTC, corresponding to POSIX time
    std::time_t t = std::time(nullptr);

    char mbstr[100] = {0};

    /// std::localtime:
    ///     Converts given time since epoch as std::time_t value into calendar time, expressed in local time.
    /// std::strftime:
    ///     Converts the date and time information from a given calendar time time to a null-terminated multibyte character
    ///     string str according to format string format. Up to count bytes are written.
    std::strftime(mbstr, sizeof(mbstr), "%Y%m%d-%H%M%S", std::localtime(&t));
    string time_str {mbstr};
    return time_str;
}

///
/// Converts seconds to HH:MM:SS formatted string
///
string format_seconds_duration(long seconds)
{
    const int hours = seconds / 3600;
    const int minutes = (seconds % 3600) / 60;
    const int remainingSeconds = seconds % 60;

    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << hours << ":"
           << std::setfill('0') << std::setw(2) << minutes << ":"
           << std::setfill('0') << std::setw(2) << remainingSeconds;

    string str = stream.str();
    return str;
}

