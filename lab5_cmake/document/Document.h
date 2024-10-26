#pragma once
#include "IDocument.h"
#include "../fileStorage/FileStorage.h"
#include "../history/UndoManager.h"

#include <list>

using DocumentItems = std::list<DocumentItem>;
using DocumentIterator = std::list<DocumentItem>::iterator;
using ConstDocumentIterator = std::list<DocumentItem>::const_iterator;

class Document final : public IDocument, public std::enable_shared_from_this<IDocument>
{
public:
	explicit Document(Path const& storageDirPath);
	void InsertParagraph(const std::string& text, size_t position = 0) override;
	void InsertImage(const std::filesystem::path& path, int width, int height, size_t position = 0) override;
	size_t GetItemsCount() const override;
	ConstDocumentItem GetItem(size_t index) const override;
	DocumentItem GetItem(size_t index) override;
	void DeleteItem(size_t index) override;
	std::string GetTitle() const override;
	void SetTitle(const std::string& title) override;
	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;
	void Save(const std::filesystem::path& path) const override;
	void List() const override;
	void ChangeTitle(std::string const& title);

private:
	DocumentIterator GetIteratorByIndex(size_t position);
	ConstDocumentIterator GetIteratorByIndex(size_t position) const;
	void WriteHtmlHead(std::ostream& strm) const;

private:
	undo::UndoManager m_history;
	DocumentItems m_items;
	std::string m_title;
	FileStorage m_storage;
};

