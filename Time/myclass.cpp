#include "myclass.h"

Time::Time() {
	hours = mins = secs = 0;
	format = "00:00:00";
}

Time::Time(const std::size_t secs_number) {
	hours = (secs_number / 3600) % 60;
	mins = (secs_number / 60) % 60;
	secs = secs_number % 60;
	update_format();
}

Time::Time(const std::string& formated_time) {
	bool wrong_format = false;
	if (formated_time.size() != req) 
		wrong_format = true;
	for (int i = 0; i < 8; ++i) {
		if ((i == 2 || i == 5) && formated_time[i] != ':') 
			wrong_format = true;
		if (i != 2 && i != 5 && (formated_time[i] < 48 || formated_time[i] > 57))
			wrong_format = true;
	}
	if (wrong_format) 
		format = "00:00:00";
	else 
		format = formated_time;
	hours = (format[0] - 48) * 10 + format[1] - 48;
	mins = (format[3] - 48) * 10 + format[4] - 48;
	secs = (format[6] - 48) * 10 + format[7] - 48;
}

Time::Time(const Time& other) {
	hours = other.hours;
	mins = other.mins;
	secs = other.secs;
	update_format();
}

Time Time::operator=(const Time& other)
{
	hours = other.hours;
	mins = other.mins;
	secs = other.secs;
	format = other.format;
	return *this;
}

Time Time::operator +(const Time& other) {
	Time new_object(*this);
	return new_object += other;
}

Time Time::operator -(const Time& other) {
	Time new_object(*this);
	return new_object -= other;
}

Time Time::operator +(std::size_t secs) {
	Time new_object(*this);
	return new_object += secs;
}

Time Time::operator -(const std::size_t secs) {
	Time new_object(*this);
	return new_object -= secs;
}

Time& Time::operator -=(const Time& other) {
	hours -= other.hours;
	mins -= other.mins;
	secs -= other.secs;
	update_time_down();
	return *this;
}

Time& Time::operator +=(const Time& other) {
	hours += other.hours;
	mins += other.mins;
	secs += other.secs;
	update_time_up();
	return *this;
}

Time& Time::operator +=(const std::size_t _secs) {
	hours += secs / 3600;
	mins += secs / 60;
	secs += _secs;
	update_time_up();
	return *this;
}

Time& Time::operator -=(const std::size_t _secs) {
	hours -= secs / 3600;
	mins -= secs / 60;
	secs -= _secs;
	update_time_down();
	return *this;
}

bool Time::operator ==(const Time& other) {
	return this->format == other.format;
}
bool Time::operator !=(const Time& other) {
	return !(*this == other);
}

void Time::update_format() {
	if (!format.size()) format = "00:00:00";
	format[0] = (hours / 10) + 48;
	format[1] = (hours % 10) + 48;
	format[3] = (mins / 10) + 48;
	format[4] = (mins % 10) + 48;
	format[6] = (secs / 10) + 48;
	format[7] = (secs % 10) + 48;
}

void Time::update_time_up() {
	mins += secs / 60;
	secs %= 60;
	hours += mins / 60;
	mins %= 60;
	hours %= 24;
	update_format();
}

void Time::update_time_down() {
	if (secs < 0) {
		mins--;
		secs += 60;
	}
	if (mins < 0) {
		hours--;
		mins += 60;
	}
	if (hours < 0) hours += 24;
	update_format();
}

void Time::parse_format() {
	bool wrong_format = false;
	if (format.size() != req) 
		wrong_format = true;
	for (int i = 0; i < 8; ++i) {
		if ((i == 2 || i == 5) && format[i] != ':') 
			wrong_format = true;
		if (i != 2 && i != 5 && (format[i] < 48 || format[i] > 57))
			wrong_format = true;
	}
	if (wrong_format) {
		format = "00:00:00";
	}
	hours = (format[0] - 48) * 10 + format[1] - 48;
	mins = (format[3] - 48) * 10 + format[4] - 48;
	secs = (format[6] - 48) * 10 + format[7] - 48;
}

std::ostream& operator <<(std::ostream& output, const Time& object) {
	output << object.format;
	return output;
}
std::istream& operator >>(std::istream& input, Time& object) {
	input >> object.format;
	object.parse_format();
	return input;
}
