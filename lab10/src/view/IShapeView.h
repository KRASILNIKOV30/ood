#pragma once
#include <QWidget>

class IShapeView
{
public:
	[[nodiscard]] virtual std::string GetId() const = 0;
	void virtual Draw(QWidget* canvas) = 0;
	virtual Frame GetFrame() = 0;

	virtual ~IShapeView() = default;
};

using IShapeViewPtr = std::shared_ptr<IShapeView>;
