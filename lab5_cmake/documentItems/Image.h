#pragma once
#include <utility>

#include "IImage.h"
#include "../edits/EditSink.h"
#include "../fileStorage/FileRef.h"

class Image final : public IImage, public std::enable_shared_from_this<IImage>
{
public:
	Image(const int width, const int height, FileRefPtr file, EditSink editSink)
		: m_width(width)
		, m_height(height)
		, m_file(std::move(file))
		, m_sink(std::move(editSink))
	{
	}

	[[nodiscard]] Path GetPath() const override
	{
		return m_file->GetPath();
	}

	[[nodiscard]] int GetWidth() const override
	{
		return m_width;
	}

	[[nodiscard]] int GetHeight() const override
	{
		return m_height;
	}

	void Resize(const int width, const int height) override
	{
		auto prevWidth = m_width;
		auto prevHeight = m_height;
		DoResize(width, height);

		m_sink(std::make_shared<ResizeImageEdit>(
			shared_from_this(),
			[&](const int w, const int h) { DoResize(w, h); },
			prevWidth, prevHeight));
	}

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream strm;
		strm << "Image: " << m_width << " " << m_height << " " << m_file->GetPath();
		return strm.str();
	}

private:
	void DoResize(int const width, int const height)
	{
		m_width = width;
		m_height = height;
	}

	int m_width;
	int m_height;
	FileRefPtr m_file;
	EditSink m_sink;
};

using ImagePtr = std::shared_ptr<Image>;
