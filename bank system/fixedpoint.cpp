#include "fixedpoint.h"

FixedPoint::FixedPoint(long long int value_) {
	value = value_;
}


FixedPoint::FixedPoint(int whole, int fraction) {

	value = (long long int)whole * (long long int)power + (long long int)fraction;
}


FixedPoint::FixedPoint() {
	value = 0;
}


string to_string(const FixedPoint& n) {
	return to_string(n.value / n.power) + '.' + to_string(abs(n.value % n.power));
}


bool FixedPoint::operator<(const FixedPoint& other) const {
	return value < other.value;
}

bool FixedPoint::operator>(const FixedPoint& other) const {
	return value > other.value;
}

bool FixedPoint::operator==(const FixedPoint& other) const {
	return value == other.value;
}

bool FixedPoint::operator!=(const FixedPoint& other) const {
	return value != other.value;
}


FixedPoint FixedPoint::operator+(const FixedPoint& other) const {
	return FixedPoint(value + other.value);
}

FixedPoint FixedPoint::operator-(const FixedPoint& other) const {
	return FixedPoint(value - other.value);
}

FixedPoint FixedPoint::operator*(const FixedPoint& other) const {
	return FixedPoint(value * other.value / power);
}



FixedPoint& FixedPoint::operator+=(const FixedPoint& other) {
	value += other.value;
	return *this;
}

FixedPoint& FixedPoint::operator-=(const FixedPoint& other) {
	value -= other.value;
	return *this;
}

FixedPoint& FixedPoint::operator*=(const FixedPoint& other) {
	value = value * other.value / power;
	return *this;
}


ostream& operator<<(ostream& os, const FixedPoint& f) {
	os << to_string(f);
	return os;
}