#pragma once
#include <ostream>
#include "IDocument.h"
#include <map>
#include <functional>
class CMenu
{
public:
	CMenu(std::istream& input, std::ostream& output, std::shared_ptr<IDocument> document);
	void HandleCommand();

private:
	void InsertParagraph(std::istream& args);
	void InsertImage(std::istream& args);
	void GetItemsCount(std::istream& args) const;
	void DeleteItem(std::istream& args);
	void GetTitle(std::istream& args) const;
	void SetTitle(std::istream& args);
	void Undo(std::istream& args);
	void Redo(std::istream& args);
	void Save(std::istream& args) const;
	void List(std::istream& args) const;
	void Help(std::istream& args) const;
	size_t GetPos(std::string str) const;
	bool CanUndo() const;
	bool CanRedo() const;

private:
	using Handler = std::function<void(std::istream& args)>;
	struct Item
	{
		Handler handler;
		std::string description;
	};
	using ActionMap = std::map<std::string, Item>;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	std::shared_ptr<IDocument> m_document;
};

