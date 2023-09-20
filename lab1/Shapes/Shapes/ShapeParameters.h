#pragma once
#include <vector>
#include <string>

struct ShapeParameters
{
	std::vector<double> layoutParams;
	std::string text = "";
};

enum ShapeType
{
	TRIANGLE,
	CIRCLE,
	LINE,
	RECTANGLE,
	TEXT
};
