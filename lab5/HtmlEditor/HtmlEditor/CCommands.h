#pragma once
#include <memory>
#include "ICommand.h"
#include "IImage.h"

class ResizeImageCommand final : public ICommand
{
public:
	ResizeImageCommand(const std::shared_ptr<IImage>& image, const int width, const int height)
		: m_image(image),
		  m_width(width),
		  m_height(height)
	{
		m_prevWidth = m_image->GetWidth();
		m_prevHeight = m_image->GetHeight();
	}

	void Execute() override
	{
		m_image->Resize(m_width, m_height);
	}

	void Unexecute() override
	{
		m_image->Resize(m_prevWidth, m_prevHeight);
	}

private:
	std::shared_ptr<IImage> m_image;
	int m_width;
	int m_height;
	int m_prevWidth;
	int m_prevHeight;
};
