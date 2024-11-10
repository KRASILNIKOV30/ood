#pragma once
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace graphics_lib
{
inline std::string GetHexStrFromUint32(uint32_t const& uint32, int len)
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(len) << std::hex << uint32;
	return stream.str();
}

class ICanvas
{
public:
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

class Canvas final : public ICanvas
{
public:
	void SetColor(uint32_t const rgbColor) override
	{
		std::cout << "SetColor (#" << GetHexStrFromUint32(rgbColor, 6) << ')' << std::endl;
	}
	void MoveTo(int const x, int const y) override
	{
		std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
	}
	void LineTo(int const x, int const y) override
	{
		std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
	}
};
}