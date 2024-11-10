#pragma once
#include <utility>
#include "../history/AbstractUndoableEdit.h"
#include <functional>

using namespace undo;

class ResizeImageEdit final : public AbstractUndoableEdit
{
	using ResizeAction = std::function<void(int, int)>;

public:
	ResizeImageEdit(IImagePtr image, ResizeAction resize, const int prevWidth, const int prevHeight)
		: m_image(std::move(image))
		, m_prevWidth(prevWidth)
		, m_prevHeight(prevHeight)
		, m_resize(std::move(resize))
	{
		m_width = m_image->GetWidth();
		m_height = m_image->GetHeight();
	}

	void UndoImpl() override
	{
		m_resize(m_prevWidth, m_prevHeight);
	}

	void RedoImpl() override
	{
		m_resize(m_width, m_height);
	}

	bool ReplaceEditImpl(const IUndoableEditPtr& edit) override
	{
		if (const auto resize = dynamic_cast<ResizeImageEdit*>(edit.get()))
		{
			if (resize->m_image == m_image)
			{
				m_prevWidth = resize->m_prevWidth;
				m_prevHeight = resize->m_prevHeight;

				return true;
			}
		}

		return false;
	}

private:
	IImagePtr m_image;
	int m_width;
	int m_height;
	int m_prevWidth;
	int m_prevHeight;
	ResizeAction m_resize;
};
