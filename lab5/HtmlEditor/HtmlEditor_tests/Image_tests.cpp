#include "../../../external/catch2/catch.hpp"
#include "../HtmlEditor/CImage.h"

SCENARIO("Image tests")
{
	GIVEN("Image")
	{
		CImage image(100, 100, "./source/cactus.png");
	}
}