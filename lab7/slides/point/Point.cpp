#include "Point.h"

#include "AreEqual.h"


bool Point::operator==(Point const& right) const
{
	return AreEqual(x, right.x) && AreEqual(y, right.y);
}

Point& Point::operator+=(Point const& right)
{
	return *this = *this + right;
}

Point Point::operator-() const
{
	return Point{ -x, -y };
}

Point operator+(Point const left, Point const right)
{
	return Point{ left.x + right.x, left.y + right.y };
}

Point operator-(Point const left, Point const right)
{
	return left + (-right);
}

std::ostream& operator<<(std::ostream& stream, Point const point)
{
	stream << "(" << point.x << ", " << point.y << ")";
	return stream;
}