#pragma once
#include <iostream>

class Point
{
public:
	double x;
	double y;

	bool operator ==(Point const& right) const;
	Point& operator +=(Point const& right);
	Point operator -() const;
};

Point operator +(Point left, Point right);
Point operator -(Point left, Point right);
std::ostream& operator <<(std::ostream& stream, Point point);