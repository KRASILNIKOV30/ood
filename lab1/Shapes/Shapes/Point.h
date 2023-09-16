#pragma once

class Point
{
public:
	double x;
	double y;

	bool operator ==(Point const& right) const;
	Point& operator +=(Point const& right);
};

Point operator +(Point const left, Point const right);
