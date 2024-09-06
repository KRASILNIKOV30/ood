#pragma once
#include <limits>
#include <algorithm>


inline bool isEqual(double left, double right)
{
	return std::abs(left - right) < std::numeric_limits<double>::epsilon();
}