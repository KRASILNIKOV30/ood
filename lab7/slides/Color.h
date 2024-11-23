#pragma once
#include <cstdint>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

constexpr int COLOR_LEN = 6;
constexpr int COLOR_RADIX = 16;

using Color = uint32_t;

inline uint32_t StringToUint32(std::string const& str)
{
	int i;
	try
	{
		i = std::stoi(str.substr(1, str.size() - 1), 0, COLOR_RADIX);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("invalid color: " + str);
	}
	if (i < 0 || i > UINT32_MAX)
	{
		throw std::invalid_argument("invalid color: " + str);
	}

	return i;
}

inline std::string GetHexStrFromUint32(uint32_t const& uint32, int len)
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(len) << std::hex << uint32;
	return stream.str();
}



