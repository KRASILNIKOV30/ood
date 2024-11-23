#include <cmath>

inline bool AreEqual(const double leftValue, const double rightValue)
{
	return std::abs(leftValue - rightValue) <= 1e-7;
}
