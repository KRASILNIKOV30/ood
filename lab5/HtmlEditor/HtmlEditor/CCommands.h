#pragma once
#include <memory>

#include "CDocumentItem.h"
#include "ICommand.h"
#include "IImage.h"
#include "IParagraph.h"
#include "IDocument.h"
#include "CDocument.h"

class ResizeImageCommand final : public ICommand
{
public:
	ResizeImageCommand(std::shared_ptr<IImage> const& image, const int width, const int height)
		: m_image(std::move(image)),
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

class ReplaceTextCommand final : public ICommand
{
public:
	ReplaceTextCommand(std::shared_ptr<IParagraph> const& paragraph, std::string const& text)
		: m_paragraph(paragraph)
		, m_text(text)
	{
		m_prevText = m_paragraph->GetText();
	}

	void Execute() override
	{
		m_paragraph->SetText(m_text);
	}

	void Unexecute() override
	{
		m_paragraph->SetText(m_prevText);
	}

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::string m_text;
	std::string m_prevText;
};

class InsertItemCommand final : public ICommand
{
public:
	InsertItemCommand(CDocumentItem& item, std::list<CDocumentItem>& list)
		: m_item(item)
		, m_list(list)
	{
	}

	void Execute() override
	{
		m_item.Restore();
	}

	void Unexecute() override
	{
		m_item.Remove();
	}

	~InsertItemCommand()
	{
		if (m_item.GetImage() && m_item.IsRemoved())
		{
			m_item.GetImage()->Remove();
		}
	}

private:
	CDocumentItem& m_item;
	std::list<CDocumentItem>& m_list;
};

class DeleteItemCommand final : public ICommand
{
	//Сделать лучше
public:
	DeleteItemCommand(CDocumentItem& item)
		: m_item(item)
	{
	}

	void Execute() override
	{
		m_item.Remove();
	}

	void Unexecute() override
	{
		m_item.Restore();
	}

	~DeleteItemCommand()
	{
		if (m_item.GetImage() && m_item.IsRemoved())
		{
			m_item.GetImage()->Remove();
		}
	}

private:
	CDocumentItem& m_item;
};

class ChangeTitleCommand final : public ICommand
{
public:
	ChangeTitleCommand(CDocument& document, std::string const& title)
		: m_document(document)
		, m_title(title)
	{
		m_prevTitle = m_document.GetTitle();
	}

	void Execute() override
	{
		m_document.ChangeTitle(m_title);
	}

	void Unexecute() override
	{
		m_document.ChangeTitle(m_prevTitle);
	}

private:
    CDocument& m_document;
	std::string m_title;
	std::string m_prevTitle;
};