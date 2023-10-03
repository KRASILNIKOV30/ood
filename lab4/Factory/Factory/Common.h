#pragma once
#include <iomanip>

inline bool IsEquals(const double leftValue, const double rightValue)
{
	return abs(leftValue - rightValue) <= 1e-7;
}


