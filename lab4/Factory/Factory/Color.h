#pragma once
#include <string>

enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black
};

inline std::string ColorToStr(const Color e)
{
	switch (e)
	{
	case Color::Green: return "green";
	case Color::Red: return "red";
	case Color::Blue: return "blue";
	case Color::Yellow: return "yellow";
	case Color::Pink: return "pink";
	case Color::Black: return "black";
	default: return "unknown";
	}
}

inline Color StrToColor(std::string const& s)
{
	if (s == "green")
	{
		return Color::Green;
	}
	if (s == "red")
	{
		return Color::Red;
	}
	if (s == "blue")
	{
		return Color::Blue;
	}
	if (s == "yellow")
	{
		return Color::Yellow;
	}
	if (s == "pink")
	{
		return Color::Pink;
	}
	if (s == "black")
	{
		return Color::Black;
	}
	throw std::exception("Unknown color");
}
