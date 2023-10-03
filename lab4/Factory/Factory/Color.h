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
	switch (s)
	{
	case "green": return Color::Green;
	case "red": return Color::Red;
	case "blue": return Color::Blue;
	case "yellow": return Color::Yellow;
	case "pink": return Color::Pink;
	case "black": return Color::Black;
	default: throw std::exception("Unknown color");
	}
}
