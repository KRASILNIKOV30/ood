#define CATCH_CONFIG_MAIN
#include "../tiles/Tile.h"
#include <catch.hpp>

SCENARIO("tiles tests")
{
	GIVEN("tiles default constructing")
	{
		Tile tile;

		THEN("can get count of instancies")
		{
			{
				Tile secondTile;
				CHECK(Tile::GetInstanceCount() == 2);
			}
			CHECK(Tile::GetInstanceCount() == 1);
		}

		THEN("tile consists of spaces")
		{
			for (int i = 0; i < Tile::SIZE; ++i)
			{
				for (int j = 0; j < Tile::SIZE; ++j)
				{
					CHECK(tile.GetPixel({i, j}) == ' ');
				}
			}
			CHECK(Tile::GetInstanceCount() == 1);
		}

		WHEN("change tile")
		{
			tile.SetPixel({3, 5}, 'x');

			THEN("tile is changed")
			{
				for (int i = 0; i < Tile::SIZE; ++i)
				{
					for (int j = 0; j < Tile::SIZE; ++j)
					{
						if (i == 3 && j == 5)
						{
							CHECK(tile.GetPixel({i, j}) == 'x');
						}
						else
						{
							CHECK(tile.GetPixel({i, j}) == ' ');
						}
					}
				}
			}
		}

		WHEN("copy changed tile")
		{
			tile.SetPixel({3, 5}, 'x');
			Tile copy(tile);

			THEN("tile was copied")
			{
				for (int i = 0; i < Tile::SIZE; ++i)
				{
					for (int j = 0; j < Tile::SIZE; ++j)
					{
						if (i == 3 && j == 5)
						{
							CHECK(copy.GetPixel({i, j}) == 'x');
						}
						else
						{
							CHECK(copy.GetPixel({i, j}) == ' ');
						}
					}
				}
			}

			AND_WHEN("change copy")
			{
				copy.SetPixel({7, 7}, 'x');

				THEN("origin tile was not changed")
				{
					for (int i = 0; i < Tile::SIZE; ++i)
					{
						for (int j = 0; j < Tile::SIZE; ++j)
						{
							if (i == 3 && j == 5)
							{
								CHECK(tile.GetPixel({i, j}) == 'x');
							}
							else
							{
								CHECK(tile.GetPixel({i, j}) == ' ');
							}
						}
					}
				}
			}
		}
	}
}

SCENARIO("negative tests")
{
	GIVEN("tiles with x")
	{
		Tile tile('x');

		THEN("can get non-existent pixel")
		{
			CHECK(tile.GetPixel({0, 8}) == ' ');
			CHECK(tile.GetPixel({8, 0}) == ' ');
			CHECK(tile.GetPixel({0, -1}) == ' ');
			CHECK(tile.GetPixel({-1, 0}) == ' ');
		}

		WHEN("set non-existent pixel")
		{
			tile.SetPixel({0, 8}, '#');
			tile.SetPixel({8, 0}, '#');
			tile.SetPixel({0, -1}, '#');
			tile.SetPixel({-1, 0}, '#');

			THEN("tile does not changed")
			{
				for (int i = 0; i < Tile::SIZE; ++i)
				{
					for (int j = 0; j < Tile::SIZE; ++j)
					{
						CHECK(tile.GetPixel({i, j}) == 'x');
					}
				}
			}
		}
	}
}