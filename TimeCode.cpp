#include "TimeCode.h"
#include <stdexcept>

// Used ChatGPT for help understanding parts of the assignment
// and debugging the code.

long long unsigned int TimeCode::ComponentsToSeconds(
    unsigned int hr,
    unsigned int min,
    unsigned long long int sec)
{
    // Converting everything to seconds keeps the TimeCode stored in one value.
    return (hr * 3600ULL) + (min * 60ULL) + sec;
}

void TimeCode::GetComponents(
    unsigned int& hr,
    unsigned int& min,
    unsigned int& sec) const
{
    // Breaks t back into hours, minutes, and seconds when they are needed.
    hr = t / 3600;

    unsigned long long remaining = t % 3600;

    min = remaining / 60;
    sec = remaining % 60;
}

TimeCode::TimeCode(
    unsigned int hr,
    unsigned int min,
    unsigned long long int sec)
{
    // Uses the same conversion method so rollover works automatically.
    t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc)
{
    // t represents the whole TimeCode, so only t needs to be copied.
    t = tc.t;
}

string TimeCode::ToString() const
{
    // Uses GetComponents instead of repeating the conversion math.
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return to_string(hr) + ":" +
           to_string(min) + ":" +
           to_string(sec);
}

unsigned int TimeCode::GetHours() const
{
    // Gets all components and returns only the hours.
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return hr;
}

unsigned int TimeCode::GetMinutes() const
{
    // Gets all components and returns only the minutes.
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return min;
}

unsigned int TimeCode::GetSeconds() const
{
    // Gets all components and returns only the seconds.
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return sec;
}

void TimeCode::reset()
{
    // Zero total seconds represents 0:0:0.
    t = 0;
}

void TimeCode::SetHours(unsigned int hours)
{
    // Keeps the current minutes and seconds while changing only hours.
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hours, min, sec);
}

void TimeCode::SetMinutes(unsigned int minutes)
{
    // Minutes cannot roll over in a setter, so 60 or more is invalid.
    if (minutes >= 60)
    {
        throw invalid_argument("Minutes must be less than 60.");
    }

    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hr, minutes, sec);
}

void TimeCode::SetSeconds(unsigned int seconds)
{
    // Seconds cannot roll over in a setter, so 60 or more is invalid.
    if (seconds >= 60)
    {
        throw invalid_argument("Seconds must be less than 60.");
    }

    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hr, min, seconds);
}

TimeCode TimeCode::operator+(const TimeCode& other) const
{
    // Adding total seconds avoids handling rollover by hand.
    unsigned long long total = t + other.GetTimeCodeAsSeconds();

    return TimeCode(0, 0, total);
}

TimeCode TimeCode::operator-(const TimeCode& other) const
{
    // Checks first because TimeCodes are not allowed to become negative.
    if (t < other.GetTimeCodeAsSeconds())
    {
        throw invalid_argument("TimeCode cannot be negative.");
    }

    unsigned long long total = t - other.GetTimeCodeAsSeconds();

    return TimeCode(0, 0, total);
}

TimeCode TimeCode::operator*(double a) const
{
    // Negative multiplication would create an invalid TimeCode.
    if (a < 0)
    {
        throw invalid_argument("Cannot multiply by a negative number.");
    }

    unsigned long long total = t * a;

    return TimeCode(0, 0, total);
}

TimeCode TimeCode::operator/(double a) const
{
    // Zero or negative division would not create a valid TimeCode.
    if (a <= 0)
    {
        throw invalid_argument("Cannot divide by zero or a negative number.");
    }

    unsigned long long total = t / a;

    return TimeCode(0, 0, total);
}

bool TimeCode::operator==(const TimeCode& other) const
{
    // Total seconds are enough to tell if two TimeCodes are equal.
    return t == other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator!=(const TimeCode& other) const
{
    // Total seconds are enough to tell if two TimeCodes are different.
    return t != other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator<(const TimeCode& other) const
{
    // Comparing t directly keeps the comparison simple.
    return t < other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator<=(const TimeCode& other) const
{
    // Comparing t directly keeps the comparison simple.
    return t <= other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator>(const TimeCode& other) const
{
    // Comparing t directly keeps the comparison simple.
    return t > other.GetTimeCodeAsSeconds();
}

bool TimeCode::operator>=(const TimeCode& other) const
{
    // Comparing t directly keeps the comparison simple.
    return t >= other.GetTimeCodeAsSeconds();
}