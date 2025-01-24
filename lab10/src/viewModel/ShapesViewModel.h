#pragma once
#include "../appModel/IShapesAppModel.h"
#include "../repository/Repository.h"
#include "IShapesViewModel.h"

class ShapesViewModel final : public IShapesViewModel
{
public:
	ShapesViewModel(IShapesAppModelPtr const& shapesAppModel);
	void AddShape(const std::string& shapeType) override;
	void RemoveShape() override;
	void OnCanvasClick() override;

	[[nodiscard]] IShapeViewModelPtr GetShape(const std::string& id) const override;
	IShapeViewModelPtr GetShape(const std::string& id) override;
	[[nodiscard]] IShapeViewModelPtr GetShape(size_t position) const override;
	IShapeViewModelPtr GetShape(size_t position) override;
	void ForEach(std::function<bool(IShapeViewModelPtr)> callback) const override;
	[[nodiscard]] size_t GetSize() const override;
	[[nodiscard]] std::optional<std::string> GetSelectedShapeId() const override;

	void Undo() override;
	void Redo() override;
	[[nodiscard]] bool CanUndo() const override;
	[[nodiscard]] bool CanRedo() const override;

	ScopedConnection DoOnAddShape(const AddShapeSlot& slot) override;
	ScopedConnection DoOnRemoveShape(const RemoveShapeSlot& slot) override;
	ScopedConnection DoOnSelectionChange(const SelectionChangeSlot& slot) override;
	ScopedConnection DoOnUpdate(UpdateSlot const& slot) override;

	void ResizeSelected(const Frame& frame) override;
	void ApplyResizeSelected(const Frame& frame) override;

private:
	void DoAddShape(IShapeAppModelPtr const& shape, size_t position);
	void DoRemoveShape(std::string const& id);
	std::optional<IShapeViewModelPtr> GetSelectedShape() const;

private:
	IShapesAppModelPtr m_shapesAppModel;
	Repository<IShapeViewModel> m_shapes;
	SignallingValue<std::optional<std::string>> m_selectedId;
	AddShapeSignal m_addShapeSignal;
	RemoveShapeSignal m_removeShapeSignal;
	UpdateSignal m_updateSignal;
	ScopedConnection m_addShapeSignalConnection;
	ScopedConnection m_removeShapeSignalConnection;
	std::vector<ScopedConnection> m_onShapeClickConnections;
	std::vector<ScopedConnection> m_reframeShapeConnections;
};
