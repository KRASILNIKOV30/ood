#include "../../../external/catch2/catch.hpp"
#include "../HtmlEditor/CImage.h"

SCENARIO("Image tests")
{
	GIVEN("Image")
	{
		CImage image(100, 100, "./source/cactus.png");

		THEN("Can get image size")
		{
			CHECK(image.GetWidth() == 100);
			CHECK(image.GetHeight() == 100);
		}

		WHEN("Resize image")
		{
			image.Resize(200, 300);

			THEN("Images size has changed")
			{
				CHECK(image.GetWidth() == 200);
				CHECK(image.GetHeight() == 300);
			}
		}
	}
}