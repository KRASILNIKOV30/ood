#include "../../../external/catch2/catch.hpp"
#include "../Transform/CDecryptInputStream.h"
#include "../Transform/CEncryptOutputStream.h"
#include "../Transform/CMemoryInputStream.h"
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

	bool operator==(std::vector<uint8_t> const& left, std::vector<uint8_t> const& right)
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

SCENARIO("Encrytion streams tests")
{
	GIVEN("Encrytion input streams with different keys")
	{
		constexpr int key1 = 3;
		constexpr int key2 = 100500;
		std::vector<uint8_t> input1;
		std::vector<uint8_t> input2;
		IOutputPtr outStrm1 = std::make_unique<CMemoryOutputStream>(input1);
		IOutputPtr outStrm2 = std::make_unique<CMemoryOutputStream>(input2);
		CEncryptOutputStream encryptStrm1(std::move(outStrm1), key1);
		CEncryptOutputStream encryptStrm2(std::move(outStrm2), key2);

		WHEN("Write messages with encryption streams")
		{
			encryptStrm1.WriteBlock("Hello", 5);
			encryptStrm2.WriteBlock("Hello", 5);

			THEN("The messages were encrypted")
			{
				CHECK_FALSE(input1 == "Hello");
				CHECK_FALSE(input2 == "Hello");

				AND_THEN("The messages were encrypted")
				{
					CHECK_FALSE(input1 == input2);
				}

				GIVEN("Decryption streams")
				{
					IInputPtr inStrm1 = std::make_unique<CMemoryInputStream>(input1);
					IInputPtr inStrm2 = std::make_unique<CMemoryInputStream>(input2);
					CDecryptInputStream decryptStrm1(std::move(inStrm1), key1);
					CDecryptInputStream decryptStrm2(std::move(inStrm2), key2);
					char* restoredMsg1 = new char[5];
					char* restoredMsg2 = new char[5];

					WHEN("Read message with decryption stream")
					{
						decryptStrm1.ReadBlock(restoredMsg2, 5);
						decryptStrm2.ReadBlock(restoredMsg1, 5);

						THEN("Message was decrypted")
						{
							CHECK(strncmp(restoredMsg1, "Hello", 5) == 0);
							CHECK(strncmp(restoredMsg2, "Hello", 5) == 0);
							delete[] restoredMsg1;
							delete[] restoredMsg2;
						}
					}
				}

				GIVEN("Decryption streams with incorrect keys")
				{
					IInputPtr inStrm1 = std::make_unique<CMemoryInputStream>(input1);
					IInputPtr inStrm2 = std::make_unique<CMemoryInputStream>(input2);
					CDecryptInputStream decryptStrm1(std::move(inStrm1), key2);
					CDecryptInputStream decryptStrm2(std::move(inStrm2), key1);
					char* restoredMsg1 = new char[5];
					char* restoredMsg2 = new char[5];

					WHEN("Read message with decryption stream")
					{
						decryptStrm1.ReadBlock(restoredMsg2, 5);
						decryptStrm2.ReadBlock(restoredMsg1, 5);

						THEN("Message was not decrypted")
						{
							CHECK_FALSE(strncmp(restoredMsg1, "Hello", 5) == 0);
							CHECK_FALSE(strncmp(restoredMsg2, "Hello", 5) == 0);
							delete[] restoredMsg1;
							delete[] restoredMsg2;
						}
					}
				}
			}
		}
	}
}