#pragma once
#include "../appModel/IShapesAppModel.h"
#include "../repository/Repository.h"
#include "IShapesViewModel.h"

using Ids = std::vector<std::string>;

class ShapesViewModel final : public IShapesViewModel
{
public:
	ShapesViewModel(IShapesAppModelPtr const& shapesAppModel);
	void AddShape(const std::string& shapeType) override;
	void RemoveSelectedShapes() override;

	[[nodiscard]] IShapeViewModelPtr GetShape(const std::string& id) const override;
	IShapeViewModelPtr GetShape(const std::string& id) override;
	[[nodiscard]] IShapeViewModelPtr GetShape(size_t position) const override;
	IShapeViewModelPtr GetShape(size_t position) override;
	void ForEach(std::function<bool(IShapeViewModelPtr)> callback) const override;
	[[nodiscard]] size_t GetSize() const override;
	[[nodiscard]] Ids GetSelectedShapeId() const override;

	void Undo() override;
	void Redo() override;
	[[nodiscard]] bool CanUndo() const override;
	[[nodiscard]] bool CanRedo() const override;

	ScopedConnection DoOnAddShape(const AddShapeSlot& slot) override;
	ScopedConnection DoOnRemoveShape(const RemoveShapeSlot& slot) override;
	ScopedConnection DoOnSelectionChange(const SelectionChangeSlot& slot) override;
	ScopedConnection DoOnUpdate(UpdateSlot const& slot) override;

	void ReframeSelected(const Frame& frame) override;
	void ApplyReframeSelected(const Frame& frame) override;
	void ResetSelection() override;
	std::optional<Frame> GetSelectedFrame() const override;

private:
	void ReselectShape(std::string const& id);
	void SelectShape(std::string const& id);
	void DoAddShape(IShapeAppModelPtr const& shape, size_t position);
	void DoRemoveShape(std::string const& id);
	std::vector<IShapeViewModelPtr> GetSelectedShapes() const;

private:
	IShapesAppModelPtr m_shapesAppModel;
	Repository<IShapeViewModel> m_shapes;
	Ids m_selectedIds;
	SelectionChangeSignal m_selectionChangeSignal;
	AddShapeSignal m_addShapeSignal;
	RemoveShapeSignal m_removeShapeSignal;
	UpdateSignal m_updateSignal;
	ScopedConnection m_addShapeSignalConnection;
	ScopedConnection m_removeShapeSignalConnection;
	std::vector<ScopedConnection> m_onShapeClickConnections;
	std::vector<ScopedConnection> m_reframeShapeConnections;
};

inline bool operator==(Ids const& left, Ids const& right)
{
	bool result = left.size() == right.size();
	if (result)
	{
		for (size_t i = 0; i < left.size(); i++)
		{
			result &= left[i] == right[i];
		}
	}
	return result;
}
