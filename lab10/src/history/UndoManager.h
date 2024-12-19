#pragma once
#include "CompoundEdit.h"

namespace undo
{

class UndoManager final : public CompoundEdit
{
public:
	[[nodiscard]] bool CanUndo() const override;
	[[nodiscard]] bool CanRedo() const override;

	[[nodiscard]] size_t GetCurrentEditIndex() const;

	void Clear();

private:
	bool AddEditImpl(const IUndoableEditPtr& edit) override;
	void UndoImpl() override;
	void RedoImpl() override;
	void EndImpl() override;
	void SetExecuted(bool executed) override;
	void DestroyImpl() noexcept override;

	[[nodiscard]] IUndoableEditPtr GetEditToBeUndone() const;
	[[nodiscard]] IUndoableEditPtr GetEditToBeRedone() const;
	void UndoTo(const IUndoableEditPtr& edit);
	void RedoTo(const IUndoableEditPtr& edit);
	void TrimEdits(size_t from, size_t to);

private:
	size_t m_indexOfNextAdd = 0;
	static constexpr int HISTORY_LIMIT = 5;
};

} // namespace undo
