#pragma once
#include "./IUndoableEdit.h"

class AbstractUndoableEdit : public IUndoableEdit
{
public:
	[[nodiscard]] bool CanUndo() const override;
	[[nodiscard]] bool CanRedo() const override;
	[[nodiscard]] bool CanBeReplaced() const override;
	void Undo() final;
	void Redo() final;
	void Destroy() noexcept final;
	bool AddEdit(const IUndoableEditPtr& edit) final;
	bool ReplaceEdit(const IUndoableEditPtr& edit) final;
	[[nodiscard]] std::string GetName() const override;
	void SetReplaceable(bool canBeReplaced);

protected:
	virtual void UndoImpl();
	virtual void RedoImpl();
	virtual void DestroyImpl() noexcept;
	virtual bool AddEditImpl(const IUndoableEditPtr& edit);
	virtual bool ReplaceEditImpl(const IUndoableEditPtr& edit);
	[[nodiscard]] virtual bool IsExecuted() const;
	virtual void SetExecuted(bool executed);
	virtual void SetName(const std::string& name);

private:
	bool m_executed = true;
	bool m_isAlive = true;
	bool m_canBeReplaced = true;
	std::string m_name;
};
