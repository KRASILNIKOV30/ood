#include "CMenu.h"

CMenu::CMenu(std::istream& input, std::ostream& output, std::shared_ptr<IDocument> document)
	: m_input(input)
	, m_document(document)
	, m_output(output)
	, m_actionMap({
			{ "InsertParagraph", { bind(&CMenu::InsertParagraph, this, std::placeholders::_1), " <position|end> <text>"} },
			{ "InsertImage", {bind(&CMenu::InsertImage, this, std::placeholders::_1), " <position|end> <width> <height> <path>"}},
			{ "GetItemsCount", {bind(&CMenu::GetItemsCount, this, std::placeholders::_1), ""}},
			{ "DeleteItem", {bind(&CMenu::DeleteItem, this, std::placeholders::_1), " <position>"}},
			{ "GetTitle", {bind(&CMenu::GetTitle, this, std::placeholders::_1), ""}},
			{ "SetTitle", {bind(&CMenu::SetTitle, this, std::placeholders::_1), " <title>"}},
			{ "Undo", {bind(&CMenu::Undo, this, std::placeholders::_1), ""}},
			{ "Redo", {bind(&CMenu::Redo, this, std::placeholders::_1), ""} },
			{ "List", {bind(&CMenu::List, this, std::placeholders::_1), ""} },
			{ "Save", {bind(&CMenu::Save, this, std::placeholders::_1), " <path>"} },
			{ "Help", {bind(&CMenu::Help, this, std::placeholders::_1), ""} },
		})
{
	Help(m_input);
}

void CMenu::HandleCommand()
{
	std::string command;
	m_input >> command;
	std::istringstream strm(command);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second.handler(strm);
	}
	else
	{
		m_output << "Unknown command";
	}
}

void CMenu::InsertParagraph(std::istream& args)
{
	std::string pos;
	m_input >> pos;
	std::string text;	
	m_input >> text;
	m_document->InsertParagraph(text, GetPos(pos));
}

void CMenu::InsertImage(std::istream& args)
{
	std::string pos;
	m_input >> pos;
	int width;
	m_input >> width;
	int height;
	m_input >> height;
	std::string path;
	m_input >> path;
	m_document->InsertImage(path, width, height, GetPos(pos));
}

void CMenu::GetItemsCount(std::istream& args) const
{
	m_output << m_document->GetItemsCount();
}

void CMenu::DeleteItem(std::istream& args)
{
	std::string pos;
	m_input >> pos;
	try
	{
		m_document->DeleteItem(GetPos(pos));
	}
	catch (std::out_of_range e)
	{
		m_output << e.what() << std::endl;
	}
}

void CMenu::GetTitle(std::istream& args) const
{
	m_output << m_document->GetTitle() << std::endl;
}

void CMenu::SetTitle(std::istream& args)
{
	std::string str;
	m_input >> str;
	m_document->SetTitle(str);
}

void CMenu::Undo(std::istream& args)
{
	if (!m_document->CanUndo())
	{
		m_output << "Can not undo";
		return;
	}
	m_document->Undo();
}

void CMenu::Redo(std::istream& args)
{
	if (!m_document->CanRedo())
	{
		m_output << "Can not redo";
		return;
	}
	m_document->Redo();
}

void CMenu::Save(std::istream& args) const
{
	std::string str;
	m_input >> str;
	m_document->Save(str);
}

void CMenu::List(std::istream& args) const
{
	m_document->List();
}

void CMenu::Help(std::istream& args) const
{
	for (auto const& [key, value] : m_actionMap)
	{
		m_output << key << value.description << std::endl;
	}
}

size_t CMenu::GetPos(std::string str) const
{
	size_t pos;
	if (str == "end")
	{
		pos = 0;
	}
	else
	{
		pos = std::stoull(str);
	}

	return pos;
}

bool CMenu::CanUndo() const
{
	return m_document->CanUndo();
}

bool CMenu::CanRedo() const
{
	return m_document->CanRedo();
}
