#pragma once

struct Point
{
	int x = 0;
	int y = 0;
};

inline Point operator+(const Point& lhs, const Point& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

inline bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

struct Size
{
	int width = 0;
	int height = 0;
};

inline bool operator==(const Size& lhs, const Size& rhs)
{
	return lhs.width == rhs.width && lhs.height == rhs.height;
}



// Точка передаётся в локальных координатах.
inline bool IsPointInSize(const Point p, const Size size) noexcept
{
	return p.x >= 0 && p.y >= 0 && p.x < size.width && p.y < size.height;
}