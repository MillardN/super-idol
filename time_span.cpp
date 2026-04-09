#include "time_span.h"

//Constructors

TimeSpan::TimeSpan() : hours_(0), minutes_(0), seconds_(0) {} 

TimeSpan::TimeSpan(int seconds) : hours_(0), minutes_(0), seconds_(seconds) { //initialize with seconds only
    normalize();
}

TimeSpan::TimeSpan(int minutes, int seconds) //initialize with minutes and seconds
    : hours_(0), minutes_(minutes), seconds_(seconds) {
    normalize();
}

TimeSpan::TimeSpan(int hours, int minutes, int seconds) //initialize with hours, minutes, and seconds
    : hours_(hours), minutes_(minutes), seconds_(seconds) {
    normalize();
}

// Getters

int TimeSpan::hours() const { return hours_; } 
int TimeSpan::minutes() const { return minutes_; }
int TimeSpan::seconds() const { return seconds_; }

void TimeSpan::set_time(int hours, int minutes, int seconds) { //set time and normalize
    hours_ = hours;
    minutes_ = minutes;
    seconds_ = seconds;
    normalize();
}

//Normalize

void TimeSpan::normalize() {
    int total_seconds = hours_ * 3600 + minutes_ * 60 + seconds_; //convert all to seconds

    hours_ = total_seconds / 3600; //get hours
    int remainder = total_seconds % 3600; //get remaining seconds after hours

    if (remainder < 0) { //adjust for negative remainder
        remainder += 3600;
        hours_--;
    }

    minutes_ = remainder / 60;
    seconds_ = remainder % 60;
}

//Math operators

TimeSpan TimeSpan::operator+(const TimeSpan& rhs) const { //add corresponding fields
    return TimeSpan(hours_ + rhs.hours_,
                    minutes_ + rhs.minutes_,
                    seconds_ + rhs.seconds_);
}

TimeSpan TimeSpan::operator-(const TimeSpan& rhs) const {
    return TimeSpan(hours_ - rhs.hours_,
                    minutes_ - rhs.minutes_,
                    seconds_ - rhs.seconds_);
}

TimeSpan TimeSpan::operator-() const {
    return TimeSpan(-hours_, -minutes_, -seconds_);
}

TimeSpan& TimeSpan::operator+=(const TimeSpan& rhs) {
    hours_ += rhs.hours_;
    minutes_ += rhs.minutes_;
    seconds_ += rhs.seconds_;
    normalize();
    return *this;
}

TimeSpan& TimeSpan::operator-=(const TimeSpan& rhs) {
    hours_ -= rhs.hours_;
    minutes_ -= rhs.minutes_;
    seconds_ -= rhs.seconds_;
    normalize();
    return *this;
}

//compare

bool TimeSpan::operator==(const TimeSpan& rhs) const { //check if all fields are equal
    return hours_ == rhs.hours_ &&
           minutes_ == rhs.minutes_ &&
           seconds_ == rhs.seconds_;
}

bool TimeSpan::operator!=(const TimeSpan& rhs) const { //check if any field is not equal
    return !(*this == rhs);
}

bool TimeSpan::operator<(const TimeSpan& rhs) const { //check if less than
    if (hours_ != rhs.hours_) return hours_ < rhs.hours_;
    if (minutes_ != rhs.minutes_) return minutes_ < rhs.minutes_;
    return seconds_ < rhs.seconds_;
}

bool TimeSpan::operator<=(const TimeSpan& rhs) const { //check less than or equal
    return *this < rhs || *this == rhs;
}

bool TimeSpan::operator>(const TimeSpan& rhs) const { //check greater than
    return !(*this <= rhs);
}

bool TimeSpan::operator>=(const TimeSpan& rhs) const { //check greater than or equal
    return !(*this < rhs);
}

//Stream operators

ostream& operator<<(ostream& out, const TimeSpan& ts) {
    out << "Hours: " << ts.hours_
        << ", Minutes: " << ts.minutes_
        << ", Seconds: " << ts.seconds_;
    return out;
}

istream& operator>>(istream& in, TimeSpan& ts) {
    in >> ts.hours_ >> ts.minutes_ >> ts.seconds_;
    ts.normalize();
    return in;
}

