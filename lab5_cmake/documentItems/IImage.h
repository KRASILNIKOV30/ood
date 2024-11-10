#pragma once
#include "../fileStorage/Path.h"
#include <string>

class IImage
{
public:
	virtual Path GetPath() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void Resize(int width, int height) = 0;
	virtual std::string ToString() const = 0;
	virtual ~IImage() = default;
};

using IImagePtr = std::shared_ptr<IImage>;
