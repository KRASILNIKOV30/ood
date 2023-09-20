#pragma once
#include "../Shapes/Common.h"

struct MockCanvasFixture
{
	fakeit::Mock<ICanvas> mockCanvas;
	std::stringstream output = std::stringstream();

	MockCanvasFixture()
	{
		DefineMockCanvasBehavior(mockCanvas, output);
	}
};

