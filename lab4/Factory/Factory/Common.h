#pragma once
#include <iomanip>
#include <sstream>
#include <iostream>

inline bool IsEquals(const double leftValue, const double rightValue)
{
	return abs(leftValue - rightValue) <= 1e-7;
}

struct CoutBufferFixture
{
	std::stringstream buffer;
	std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

	std::string GetOutput() const
	{
		return buffer.str();
	}

	void ClearOutput()
	{
		buffer.str(std::string());
	}

	~CoutBufferFixture()
	{
		std::cout.rdbuf(old);
	}
};