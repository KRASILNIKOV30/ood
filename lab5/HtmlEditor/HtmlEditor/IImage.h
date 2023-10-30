#pragma once
#include <string>

class IImage
{
public:
	virtual std::filesystem::path GetPath() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void Resize(int width, int height) = 0;
	virtual ~IImage() = default;
};
