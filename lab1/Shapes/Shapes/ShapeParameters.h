#pragma once
#include <vector>
#include <string>

struct ShapeParameters
{
	std::vector<double> layoutParams;
	std::string text = "";
};

enum class ShapeType
{
	CIRCLE,
	RECTANGLE,
	TEXT,
	TRIANGLE,
	LINE
};