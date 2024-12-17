#pragma once
#include "../repository/Repository.h"
#include "IShapes.h"

class Shapes final : public IShapes
{
public:
	[[nodiscard]] size_t GetSize() const override;
	void AddShape(IShapePtr&& shape, std::optional<size_t> position = std::nullopt) override;
	size_t RemoveShape(std::string const& id) override;
	[[nodiscard]] const IShape* GetShape(std::string const& id) const override;
	[[nodiscard]] IShape* GetShape(const std::string& id) override;
	void ForEach(std::function<bool(const IShape*)> callback) const override;

	ScopedConnection DoOnAddShape(const AddShapeSlot& slot) override;
	ScopedConnection DoOnRemoveShape(const RemoveShapeSlot& slot) override;

private:
	Repository<IShape> m_shapes;
	AddShapeSignal m_addShapeSignal;
	RemoveShapeSignal m_removeShapeSignal;
};