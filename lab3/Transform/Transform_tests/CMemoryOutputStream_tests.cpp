#include "../../../external/catch2/catch.hpp"
#include "../Transform/CMemoryOutputStream.h"
#include <vector>

SCENARIO("Memory output stream test")
{
	GIVEN("Memory output stream")
	{
		std::vector<uint8_t> memory;
		CMemoryOutputStream strm(memory);

		WHEN("Write one byte to file")
		{
			strm.WriteByte('A');

			THEN("Byte has been written")
			{
				CHECK(memory.size() == 1);
				CHECK(memory[0] == 'A');
			}
		}

		AND_WHEN("Write full data block to file")
		{
			strm.WriteBlock("Hello, world!", 14);

			THEN("Block has been fully written")
			{
				const std::vector<uint8_t> expected = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!', '\0' };
				REQUIRE(memory.size() == expected.size());
				for (int i = 0; i < memory.size(); i++)
				{
					CHECK(memory[i] == expected[i]);
				}
			}
		}

		AND_WHEN("Write not full data block to file")
		{
			strm.WriteBlock("Hello, world!", 5);

			THEN("Block has been fully written")
			{
				std::vector<uint8_t> expected = { 'H', 'e', 'l', 'l', 'o' };
				CHECK(memory.size() == expected.size());
				for (int i = 0; i < memory.size(); i++)
				{
					CHECK(memory[i] == expected[i]);
				}
			}
		}
	}
}