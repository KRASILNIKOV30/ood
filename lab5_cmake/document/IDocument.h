#pragma once
#include <string>
#include <filesystem>
#include "../documentItems/DocumentItem.h"

class IDocument
{
public:
	virtual void InsertParagraph(const std::string& text,size_t position = 0) = 0;
	virtual void InsertImage(const std::filesystem::path& path, int width, int height, size_t position = 0) = 0;
	[[nodiscard]] virtual size_t GetItemsCount() const = 0;
	[[nodiscard]] virtual ConstDocumentItem GetItem(size_t index) const = 0;
	virtual DocumentItem GetItem(size_t index) = 0;
	virtual void DeleteItem(size_t index) = 0;
	[[nodiscard]] virtual std::string GetTitle() const = 0;
	virtual void SetTitle(const std::string& title) = 0;
	virtual void List() const = 0;
	[[nodiscard]] virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;
	[[nodiscard]] virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;
	virtual void Save(const std::filesystem::path& path) const = 0;
	virtual ~IDocument() = default;
};

using IDocumentPtr = std::shared_ptr<IDocument>;