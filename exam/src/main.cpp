#include <iostream>
#include <memory>
#include <utility>

namespace exam
{
struct Point
{
	int x;
	int y;
};

struct Size
{
	int width;
	int height;
};

struct Frame
{
	Point position;
	Size size;
};

class IFrameObject
{
public:
	[[nodiscard]] virtual Frame GetFrame() const = 0;
	virtual ~IFrameObject() = default;
};
using IFrameObjectPtr = IFrameObject*;

class IDrawingStrategy
{
public:
	virtual void Draw(IFrameObjectPtr const& frameObject) = 0;
	virtual ~IDrawingStrategy() = default;
};
using IDrawingStrategyPtr = std::shared_ptr<IDrawingStrategy>;

class RectangleDrawingStrategy final : public IDrawingStrategy
{
public:
	void Draw(IFrameObjectPtr const& frameObject) override
	{
		const auto [position, size] = frameObject->GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		std::cout << "Draw rectangle at (" << x << ", " << y << ") with size (" << width << ", " << height << ")" << std::endl;
	}
};

class EllipseDrawingStrategy final : public IDrawingStrategy
{
public:
	void Draw(IFrameObjectPtr const& frameObject) override
	{
		const auto [position, size] = frameObject->GetFrame();
		const auto [x, y] = position;
		const auto [width, height] = size;

		std::cout << "Draw ellipse at (" << x << ", " << y << ") with size (" << width << ", " << height << ")" << std::endl;
	}
};

class IDrawable
{
public:
	virtual void Draw() = 0;
	virtual ~IDrawable() = default;
};

class Shape final
	: public IFrameObject
	, public IDrawable
{
public:
	Shape(Frame const& frame, IDrawingStrategyPtr strategy)
		: m_frame(frame)
		, m_drawingStrategy(std::move(strategy))
	{
	}

	void Draw() override
	{
		m_drawingStrategy->Draw(this);
	}

	[[nodiscard]] Frame GetFrame() const override
	{
		return m_frame;
	}

private:
	Frame m_frame;
	IDrawingStrategyPtr m_drawingStrategy;
};

} // namespace exam

using namespace exam;

int main()
{
	std::shared_ptr<IDrawingStrategy> rectangleDrawingStrategy = std::make_shared<RectangleDrawingStrategy>();
	std::shared_ptr<IDrawingStrategy> ellipseDrawingStrategy = std::make_shared<EllipseDrawingStrategy>();

	const std::shared_ptr<IDrawable> rectangle = std::make_shared<Shape>(Frame{ 10, 10, 100, 100 }, rectangleDrawingStrategy);
	const std::shared_ptr<IDrawable> ellipse = std::make_shared<Shape>(Frame{ 50, 60, 200, 300 }, ellipseDrawingStrategy);

	rectangle->Draw();
	ellipse->Draw();

	return 0;
}
