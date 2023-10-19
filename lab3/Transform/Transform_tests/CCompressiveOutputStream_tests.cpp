#include "../../../external/catch2/catch.hpp"
#include "../Transform/CCompressiveOutputStream.h"
#include "../Transform/CMemoryOutputStream.h"
#include "../Transform/IDataStreams.h"

namespace
{
	bool operator==(std::vector<uint8_t> const& left, std::string const& right)
	{
		if (left.size() != right.size())
		{
			return false;
		}

		for (size_t i = 0; i < left.size(); i++)
		{
			if (left[i] != right[i])
			{
				return false;
			}
		}

		return true;
	}
}

SCENARIO("Compressive output stream tests")
{
	GIVEN("Compressive output stream")
	{
		std::vector<uint8_t> v;
		IOutputPtr strm = std::make_unique<CMemoryOutputStream>(v);
		CCompressiveOutputStream compStrm(std::move(strm));

		WHEN("Write single byte")
		{
			compStrm.WriteByte('A');
			compStrm.Flush();

			THEN("Byte was compressed")
			{
				CHECK(v == "1A");
			}
		}

		WHEN("Write data by bytes")
		{
			compStrm.WriteByte('A');
			compStrm.WriteByte('A');
			compStrm.WriteByte('A');
			compStrm.WriteByte('B');
			compStrm.WriteByte('B');
			compStrm.Flush();

			THEN("Byte was compressed")
			{
				CHECK(v == "3A2B");
			}
		}

		WHEN("Write data block")
		{
			compStrm.WriteBlock("AAABBC", 6);
			compStrm.Flush();

			THEN("Byte was compressed")
			{
				CHECK(v == "3A2B1C");
			}
		}

		WHEN("Write data block greater than 8 bytes")
		{
			compStrm.WriteBlock("AAAAAAAAAA", 10);
			compStrm.Flush();

			THEN("Bytes was compressed in two blocks")
			{
				CHECK(v == "8A2A");
			}
		}

		WHEN("Write data block, then write data by bytes and then write block again")
		{
			compStrm.WriteBlock("AAA", 3);
			compStrm.WriteByte('A');
			compStrm.WriteByte('A');
			compStrm.WriteBlock("AAA", 3);
			compStrm.Flush();

			THEN("Bytes was compressed")
			{
				CHECK(v == "8A");
			}
		}
	}
}