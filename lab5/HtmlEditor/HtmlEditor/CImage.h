#pragma once
#include <filesystem>
#include "IImage.h"

class CImage final : public IImage
{
public:
	CImage(const int m_width, const int m_height, std::filesystem::path const& path)
		: m_width(m_width)
		, m_height(m_height)
		, m_originPath(path)
	{
		Copy(path);
	}

	std::filesystem::path GetPath() const override
	{
		return m_path;
	}

	int GetWidth() const override
	{
		return m_width;
	}

	int GetHeight() const override
	{
		return m_height;
	}

	void Resize(const int width, const int height) override
	{
		m_width = width;
		m_height = height;
	}

	void Remove() override
	{
		if (m_removed)
		{
			return;
		}

		m_removed = true;
		std::filesystem::remove(m_path);
	}

	std::string ToString() const override
	{
		std::stringstream strm;
		strm << "Image: " << m_width << " " << m_height << " " << m_originPath;
		return strm.str();
	}

	~CImage() override
	{
		if (!m_removed)
		{
			std::filesystem::remove(m_path);
		}
	}

private:
	void Copy(std::filesystem::path const& path)
	{
		char localPath[L_tmpnam_s];
		tmpnam_s(localPath);
		std::filesystem::path filename = std::filesystem::path(std::string(localPath)).filename();
		std::filesystem::path const ext = path.extension();
		std::filesystem::create_directory("images");
		m_path.concat("images/") += filename += ext;
		copy_file(path, m_path);
	}

private:
	int m_width;
	int m_height;
	bool m_removed = false;
	std::filesystem::path m_path;
	std::filesystem::path m_originPath;
};
