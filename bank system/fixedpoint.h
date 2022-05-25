#pragma once
#include <string>
#include <iostream>

using namespace std;


class FixedPoint {
private:
	long long int value = 0;
	int power = 100;

	FixedPoint(long long int value_);
public:

	FixedPoint(int whole, int fraction);
	FixedPoint();
	friend string to_string(const FixedPoint& n);

	bool operator<(const FixedPoint& other) const;
	bool operator>(const FixedPoint& other) const;
	bool operator==(const FixedPoint& other) const;
	bool operator!=(const FixedPoint& other) const;

	FixedPoint operator+(const FixedPoint& other) const;
	FixedPoint operator-(const FixedPoint& other) const;
	FixedPoint operator*(const FixedPoint& other) const;

	FixedPoint& operator+=(const FixedPoint& other);
	FixedPoint& operator-=(const FixedPoint& other);
	FixedPoint& operator*=(const FixedPoint& other);

	friend ostream& operator <<(ostream& os, const FixedPoint& f);
};


