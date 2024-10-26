#include "Document.h"
#include <iostream>
#include "../documentItems/Image.h"
#include <fstream>
#include <list>
#include "../documentItems/Paragraph.h"
#include "../edits/ChangeTitleEdit.h"
#include "../edits/DeleteItemEdit.h"
#include "../edits/InsetrtItemEdit.h"

Document::Document(Path const& storageDirPath)
	: m_storage(storageDirPath)
{
}

void Document::InsertParagraph(const std::string& text, const size_t position)
{
    auto it = m_items.emplace(
    	GetIteratorByIndex(position),
    	std::make_shared<Paragraph>(text, [&](auto edit) { m_history.AddEdit(edit); }));
    m_history.AddEdit(std::make_shared<InsertItemEdit>(*it, it, m_items));
}

void Document::InsertImage(const Path& path, int width, int height, const size_t position)
{
	auto file = m_storage.AddFile(path);
	auto it = m_items.emplace(
		GetIteratorByIndex(position),
		std::make_shared<Image>(width, height, file, [&](auto edit) { m_history.AddEdit(edit); }));
	m_history.AddEdit(std::make_shared<InsertItemEdit>(*it, it, m_items));
}

DocumentIterator Document::GetIteratorByIndex(size_t const position)
{
    if (position == 0)
    {
        return m_items.end();
    }
	if (position - 1 > GetItemsCount())
	{
		throw std::out_of_range("Error: try to get access for non-existing item");
	}
	return std::next(m_items.begin(), position - 1);
}

ConstDocumentIterator Document::GetIteratorByIndex(size_t const position) const
{
	if (position == 0)
	{
		return m_items.end();
	}
	if (position - 1 > GetItemsCount())
	{
		throw std::out_of_range("Error: try to get access for non-existing item");
	}
	return std::next(m_items.begin(), position - 1);
}

size_t Document::GetItemsCount() const
{
    return m_items.size();
}

ConstDocumentItem Document::GetItem(const size_t index) const
{
	const auto it = GetIteratorByIndex(index);
    if (it == m_items.end())
    {
        throw std::out_of_range("Can not delete non exesting item");
    }
    return static_cast<ConstDocumentItem>(*it);
}

DocumentItem Document::GetItem(size_t const index)
{
    auto const it = GetIteratorByIndex(index);
    if (it == m_items.end())
    {
        throw std::out_of_range("Can not delete non exesting item");
    }
    return *it;
}

void Document::DeleteItem(size_t index)
{
    auto it = GetIteratorByIndex(index);
    if (it == m_items.end())
    {
        throw std::out_of_range("Can not delete non exesting item");
    }
	auto iter = m_items.erase(it);
    m_history.AddEdit(std::make_shared<DeleteItemEdit>(*iter, iter, m_items));
}

std::string Document::GetTitle() const
{
    return m_title;
}

void Document::SetTitle(const std::string& title)
{
	auto prevTitle = m_title;
	m_title = title;

	m_history.AddEdit(std::make_shared<ChangeTitleEdit>(
		shared_from_this(),
		prevTitle,
		[&](auto t) { m_title = t; }));
}

bool Document::CanUndo() const
{
    return m_history.CanUndo();
}

void Document::Undo()
{
    m_history.Undo();
}

bool Document::CanRedo() const
{
    return m_history.CanRedo();
}

void Document::Redo()
{
    m_history.Redo();
}

void Document::WriteHtmlHead(std::ostream& strm) const
{
    strm << "<html>" << std::endl;
    strm << "<head>" << std::endl;
    strm << "  <title>" << m_title << "</title>" << std::endl;
    strm << "</head>" << std::endl;
}

void Document::Save(const std::filesystem::path& path) const
{
    std::filesystem::path imgPath = path;
    imgPath.concat("/images");
    create_directory(path);
    create_directory(imgPath);
    std::filesystem::path htmlPath = path;
    htmlPath.concat("/index.html");
    std::ofstream strm = std::ofstream(htmlPath.c_str());
    WriteHtmlHead(strm);
    strm << "<body>" << std::endl;
    for (auto const& item : m_items)
    {
    	item.ToHtml(strm, imgPath);
    }
    strm << "</body>" << std::endl;
    strm << "</html>" << std::endl;
}

void Document::List() const
{
    size_t i = 1;
    for (auto const& item : m_items)
    {
    	std::cout << i++ << ". " << item.ToString() << std::endl;
    }
}

void Document::ChangeTitle(std::string const& title)
{
    m_title = title;
}
