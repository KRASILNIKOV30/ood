#pragma once
#include "../appModel/IShapesAppModel.h"
#include "../repository/Repository.h"
#include "IShapesViewModel.h"

class ShapesViewModel final : IShapesViewModel
{
public:
	ShapesViewModel(IShapesAppModelPtr shapesAppModel);
	void AddShape(const std::string& shapeType) override;
	void RemoveShape() override;
	void OnCanvasClick() override;

	[[nodiscard]] IShapeViewModelPtr GetShape(const std::string& id) const override;
	IShapeViewModelPtr GetShape(const std::string& id) override;
	[[nodiscard]] IShapeViewModelPtr GetShape(size_t position) const override;
	IShapeViewModelPtr GetShape(size_t position) override;
	void ForEach(std::function<bool(IShapeViewModelPtr)> callback) const override;
	[[nodiscard]] size_t GetSize() const override;

	void Undo() override;
	void Redo() override;
	[[nodiscard]] bool CanUndo() const override;
	[[nodiscard]] bool CanRedo() const override;

	ScopedConnection DoOnAddShape(const AddShapeSlot& slot) override;
	ScopedConnection DoOnRemoveShape(const RemoveShapeSlot& slot) override;
	ScopedConnection DoOnSelectionChange(const SelectionChangeSlot& slot) override;

private:
	void DoAddShape(IShapeAppModelPtr const& shape, size_t position);
	void DoRemoveShape(std::string const& id);

private:
	IShapesAppModelPtr m_shapesAppModel;
	Repository<IShapeViewModel> m_shapes;
	SignallingValue<std::optional<std::string>> m_selectedId;
	AddShapeSignal m_addShapeSignal;
	RemoveShapeSignal m_removeShapeSignal;
	ScopedConnection m_addShapeSignalConnection;
	ScopedConnection m_removeShapeSignalConnection;
	std::vector<ScopedConnection> m_onShapeClickConnections;
};
