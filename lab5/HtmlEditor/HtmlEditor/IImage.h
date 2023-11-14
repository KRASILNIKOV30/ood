#pragma once
#include <string>
#include <filesystem>

class IImage
{
public:
	virtual std::filesystem::path GetPath() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual void Resize(int width, int height) = 0;
	virtual std::string ToString() const = 0;
	virtual void Remove() = 0;
	virtual ~IImage() = default;
};
