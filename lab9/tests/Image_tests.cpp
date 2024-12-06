#include <catch.hpp>
#include "../tiles/Image.h"

SCENARIO("image tests")
{
	WHEN("create image with default color (divides by size)")
	{
		const Image img({24, 16});

		THEN('image created')
		{
			bool result = true;
			for (int i = 0; i < 24; ++i)
			{
				for (int j = 0; j < 16; ++j)
				{
					result &= img.GetPixel({i, j}) == ' ';
				}
			}
			CHECK(result);
			CHECK(Tile::GetInstanceCount() == 1);
			CHECK(img.GetSize() == Size{24, 16});
		}

		WHEN("can get pixel not from image")
		{
			CHECK(img.GetPixel({-1, 0}) == ' ');
			CHECK(img.GetPixel({0, -1}) == ' ');
			CHECK(img.GetPixel({24, 0}) == ' ');
			CHECK(img.GetPixel({0, 16}) == ' ');
		}
	}

	WHEN("construct image with negative size")
	{
		CHECK_THROWS_AS(Image({-1, 10}), std::out_of_range);
		CHECK_THROWS_AS(Image({10, -1}), std::out_of_range);
	}

	WHEN("create image with custom color (not divides by size)")
	{
		const Image img({25, 23}, '.');

		THEN('image created')
		{
			bool result = true;
			for (int i = 0; i < 25; ++i)
			{
				for (int j = 0; j < 23; ++j)
				{
					result &= img.GetPixel({i, j}) == '.';
				}
			}
			CHECK(result);
			CHECK(Tile::GetInstanceCount() == 1);
			CHECK(img.GetSize() == Size{25, 23});
		}

		THEN("can get pixel not from image")
		{
			CHECK(img.GetPixel({-1, 0}) == ' ');
			CHECK(img.GetPixel({0, -1}) == ' ');
			CHECK(img.GetPixel({25, 0}) == ' ');
			CHECK(img.GetPixel({0, 23}) == ' ');
		}
	}

	GIVEN("an image")
	{
		Image img({32, 24}, '.');

		WHEN("set pixel")
		{
			img.SetPixel({13, 7}, 'x');
			img.SetPixel({13, 8}, 'x');

			THEN("image was changed")
			{
				bool result = true;
				for (int i = 0; i < 32; ++i)
				{
					for (int j = 0; j < 24; ++j)
					{
						if ((i == 13 && j == 7) || (i == 13 && j == 8))
						{
							result &= img.GetPixel({i, j}) == 'x';
						}
						else
						{
							result &= img.GetPixel({i, j}) == '.';
						}
					}
				}
				CHECK(result);
				CHECK(Tile::GetInstanceCount() == 3);
			}
		}

		WHEN("set non-existent pixels")
		{
			img.SetPixel({-1, 0}, 'x');
			img.SetPixel({0, -1}, 'x');
			img.SetPixel({32, 0}, 'x');
			img.SetPixel({0, 24}, 'x');

			THEN("image does not change")
			{
				CHECK(Tile::GetInstanceCount() == 1);
			}
		}
	}
}