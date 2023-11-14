#pragma once
#include "History.h"
#include "IDocument.h"

class CDocument final : public IDocument
{
public:
	void InsertParagraph(const std::string& text, size_t position = 0) override;
	void InsertImage(const std::filesystem::path& path, int width, int height, size_t position = 0) override;
	size_t GetItemsCount() const override;
	CConstDocumentItem GetItem(size_t index) const override;
	CDocumentItem GetItem(size_t index) override;
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
	std::list<CDocumentItem>::iterator GetIteratorByIndex(size_t position);
	std::list<CDocumentItem>::const_iterator GetIteratorByIndex(size_t position) const;
	void WriteHtmlHead(std::ostream& strm) const;

private:
	History m_history;
	std::list<CDocumentItem> m_items;
	std::string m_title;
};

