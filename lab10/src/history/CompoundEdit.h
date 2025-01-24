#pragma once
#include "AbstractUndoableEdit.h"
#include <optional>
#include <vector>

class CompoundEdit : public AbstractUndoableEdit
{
public:
	explicit CompoundEdit(const std::optional<std::string>& customName = std::nullopt);
	~CompoundEdit() override;
	[[nodiscard]] bool CanUndo() const override;
	[[nodiscard]] bool CanRedo() const override;
	[[nodiscard]] std::string GetName() const override;
	void End();
	[[nodiscard]] size_t GetEditCount() const;
	[[nodiscard]] IUndoableEditPtr GetEdit(size_t index) const;

protected:
	void DestroyImpl() noexcept override;
	void UndoImpl() override;
	void RedoImpl() override;
	bool AddEditImpl(const IUndoableEditPtr& edit) override;
	virtual void EndImpl();
	void SetName(const std::string& name) override;

protected:
	std::vector<IUndoableEditPtr> m_edits;
	bool m_inProgress = true;

private:
	bool m_hasCustomName = false;
};

typedef std::unique_ptr<CompoundEdit> CompoundEditUniquePtr;