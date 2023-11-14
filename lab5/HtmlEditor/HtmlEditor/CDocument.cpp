#include "CDocument.h"
#include <iostream>
#include "CCommands.h"
#include "CImage.h"
#include <fstream>
#include "CParagraph.h"

void CDocument::InsertParagraph(const std::string& text, size_t position)
{
    auto it = m_items.emplace(GetIteratorByIndex(position), std::make_shared<CParagraph>(text));
    m_history.AddAndExecuteCommand(std::make_unique<InsertItemCommand>(*it, m_items));
}

void CDocument::InsertImage(const std::filesystem::path& path, int width, int height, size_t position)
{
	auto it = m_items.emplace(GetIteratorByIndex(position), std::make_shared<CImage>(width, height, path));
	m_history.AddAndExecuteCommand(std::make_unique<InsertItemCommand>(*it, m_items));
}

std::list<CDocumentItem>::iterator CDocument::GetIteratorByIndex(size_t const position)
{
    if (position == 0)
    {
        return m_items.end();
    }
	if (position - 1 > GetItemsCount())
	{
        throw std::out_of_range("Error: try to get access for non-existing item");
	}

    size_t count = 1;
    auto it = m_items.begin();
    for (it; count < position; ++it)
    {
        if (!it->IsRemoved())
        {
            ++count;
        }
    }

    return it;
}

std::list<CDocumentItem>::const_iterator CDocument::GetIteratorByIndex(size_t const position) const
{
    if (position == 0)
    {
        return m_items.cend();
    }
    if (position - 1 > GetItemsCount())
    {
        throw std::out_of_range("Error: try to get access for non-existing item");
    }

    size_t count = 1;
    auto it = m_items.cbegin();
    for (it; count < position; ++it)
    {
        if (!it->IsRemoved())
        {
            ++count;
        }
    }

    return it;
}

size_t CDocument::GetItemsCount() const
{
    size_t count = 0;
    for (auto const& item : m_items)
    {
	    if (!item.IsRemoved())
	    {
            ++count;
	    }
    }

    return count;
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
    auto it = GetIteratorByIndex(index);
    if (it == m_items.end())
    {
        throw std::out_of_range("Can not delete non exesting item");
    }
    return *it;
}

CDocumentItem CDocument::GetItem(size_t index)
{
    auto it = GetIteratorByIndex(index);
    if (it == m_items.end())
    {
        throw std::out_of_range("Can not delete non exesting item");
    }
    return *it;
}

void CDocument::DeleteItem(size_t index)
{
    auto it = GetIteratorByIndex(index);
    if (it == m_items.end())
    {
        throw std::out_of_range("Can not delete non exesting item");
    }
    m_history.AddAndExecuteCommand(std::make_unique<DeleteItemCommand>(*it));
}

std::string CDocument::GetTitle() const
{
    return m_title;
}

void CDocument::SetTitle(const std::string& title)
{
    m_history.AddAndExecuteCommand(std::make_unique<ChangeTitleCommand>(*this, title));
}

bool CDocument::CanUndo() const
{
    return m_history.CanUndo();
}

void CDocument::Undo()
{
    m_history.Undo();
}

bool CDocument::CanRedo() const
{
    return m_history.CanRedo();
}

void CDocument::Redo()
{
    m_history.Redo();
}

void CDocument::WriteHtmlHead(std::ostream& strm) const
{
    strm << "<html>" << std::endl;
    strm << "<head>" << std::endl;
    strm << "  <title>" << m_title << "</title>" << std::endl;
    strm << "</head>" << std::endl;
}

void CDocument::Save(const std::filesystem::path& path) const
{
    std::filesystem::path imgPath = path;
    imgPath.concat("/images");
    std::filesystem::create_directory(path);
    std::filesystem::create_directory(imgPath);
    std::filesystem::path htmlPath = path;
    htmlPath.concat("/index.html");
    std::ofstream strm = std::ofstream(htmlPath.c_str());
    WriteHtmlHead(strm);
    strm << "<body>" << std::endl;
    for (auto const& item : m_items)
    {
        if (!item.IsRemoved())
        {
            item.ToHtml(strm, imgPath);
        }
    }
    strm << "</body>" << std::endl;
    strm << "</html>" << std::endl;
}

void CDocument::List() const
{
    size_t i = 1;
    for (auto const& item : m_items)
    {
        if (!item.IsRemoved())
        {
            std::cout << i++ << ". " << item.ToString() << std::endl;
        }
    }
}

void CDocument::ChangeTitle(std::string const& title)
{
    m_title = title;
}
