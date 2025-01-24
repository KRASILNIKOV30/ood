#pragma once
#include "./IUndoableEdit_fwd.h"
#include <string>

class IUndoableEdit
{
public:
	[[nodiscard]] virtual bool CanUndo() const = 0;
	[[nodiscard]] virtual bool CanRedo() const = 0;
	[[nodiscard]] virtual bool CanBeReplaced() const = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual void Destroy() noexcept = 0;

	virtual bool AddEdit(const IUndoableEditPtr& edit) = 0;

	virtual bool ReplaceEdit(const IUndoableEditPtr& edit) = 0;

	[[nodiscard]] virtual std::string GetName() const = 0;

	virtual ~IUndoableEdit() = default;
};
