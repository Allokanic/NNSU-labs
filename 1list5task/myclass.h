#pragma once
#include <string>
#include <iostream>

class Time {
public:
	Time();
	Time(const std::size_t secs_number);
	Time(const std::string& formated_time);
	Time(const Time& other);

	~Time() = default;

	Time operator =(const Time& other);
	Time operator +(const Time& other);
	Time operator +(const std::size_t secs);
	Time operator -(const Time& other);
	Time operator -(const std::size_t secs);
	Time& operator -=(const Time& other);
	Time& operator +=(const Time& other);
	Time& operator +=(const std::size_t secs);
	Time& operator -=(const std::size_t secs);

	bool operator ==(const Time& other);
	bool operator !=(const Time& other);

	friend std::ostream& operator <<(std::ostream& output, const Time& object);
	friend std::istream& operator >>(std::istream& input, Time& object);

private:
	void update_format();
	void update_time_up();
	void update_time_down();
	void parse_format();

	int hours, mins, secs;
	std::string format;

	static constexpr int req = 8;
};
