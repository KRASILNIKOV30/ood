#pragma once
#include <utility>
#include "../documentItems/Image.h"
#include "../documentItems/IParagraph.h"
#include "../history/AbstractUndoableEdit.h"

#include <functional>

using namespace undo;

class ReplaceTextEdit final : public AbstractUndoableEdit
{
	using ReplaceAction = std::function<void(std::string)>;

public:
	ReplaceTextEdit(IParagraphPtr paragraph, ReplaceAction replace, std::string prevText)
		: m_paragraph(std::move(paragraph))
		, m_prevText(std::move(prevText))
		, m_replace(std::move(replace))
	{
		m_text = m_paragraph->GetText();
	}

	void UndoImpl() override
	{
		m_replace(m_prevText);
	}

	void RedoImpl() override
	{
		m_replace(m_text);
	}

	bool ReplaceEditImpl(const IUndoableEditPtr& edit) override
	{
		if (const auto replace = dynamic_cast<ReplaceTextEdit*>(edit.get()))
		{
			if (replace->m_paragraph == m_paragraph)
			{
				m_prevText = replace->m_prevText;
				return true;
			}
		}

		return false;
	}

private:
	IParagraphPtr m_paragraph;
	std::string m_text;
	std::string m_prevText;
	ReplaceAction m_replace;
};

