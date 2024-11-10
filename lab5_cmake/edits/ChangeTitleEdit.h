#pragma once
#include "../document/Document.h"
#include "../history/AbstractUndoableEdit.h"
#include <functional>

class Document;

class ChangeTitleEdit final : public AbstractUndoableEdit
{
	using ChangeTitleAction = std::function<void(const std::string&)>;
public:
	ChangeTitleEdit(IDocumentPtr document, std::string prevTitle, ChangeTitleAction action)
		: m_document(std::move(document))
		, m_prevTitle(std::move(prevTitle))
		, m_changeTitleAction(std::move(action))
	{
		m_title = m_document->GetTitle();
	}

	void UndoImpl() override
	{
		m_changeTitleAction(m_prevTitle);
	}

	void RedoImpl() override
	{
		m_changeTitleAction(m_title);
	}

	bool ReplaceEditImpl(const undo::IUndoableEditPtr& edit) override
	{
		if (auto const prev = dynamic_cast<ChangeTitleEdit*>(edit.get()))
		{
			if (m_document == prev->m_document)
			{
				m_prevTitle = prev->m_prevTitle;
				return true;
			}
		}

		return false;
	}

private:
	IDocumentPtr m_document;
	std::string m_title;
	std::string m_prevTitle;
	ChangeTitleAction m_changeTitleAction;
};
