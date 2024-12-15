#pragma once

struct Size
{
	int width;
	int height;
};

inline bool operator==(const Size& lhs, const Size& rhs)
{
	return lhs.width == rhs.width && lhs.height == rhs.height;
}

struct Point
{
	int x;
	int y;
};

inline bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

struct Frame
{
	Point position;
	Size size;
};

inline bool operator==(const Frame& lhs, const Frame& rhs)
{
	return lhs.position == rhs.position && lhs.size == rhs.size;
}