#include "CDecryptInputStream.h"

#include <random>

CDecryptInputStream::CDecryptInputStream(IInputPtr&& stream, int const key)
	: CInputStreamDecorator(std::move(stream))
	, m_key(key)
{
	GenerateMap();
}

bool CDecryptInputStream::IsEOF() const
{
	return CInputStreamDecorator::IsEOF();
}

uint8_t CDecryptInputStream::ReadByte()
{
	return m_map[CInputStreamDecorator::ReadByte()];
}

std::streamsize CDecryptInputStream::ReadBlock(void* dstBuffer, const std::streamsize size)
{
	char* bytes = new char[size];
	try
	{
		std::streamsize const readSize = CInputStreamDecorator::ReadBlock(bytes, size);
		for (int i = 0; i < readSize; i++)
		{
			memset(dstBuffer, m_map[*(bytes + i)], 1);
		}
		delete[] bytes;

		return readSize;
	}
	catch (std::ios_base::failure& e)
	{
		delete[] bytes;
		throw e;
	}
}

void CDecryptInputStream::GenerateMap()
{
	std::vector<uint8_t> v;
	v.reserve(MAP_SIZE);
	for (int i = 0; i < MAP_SIZE; i++)
	{
		v.push_back(static_cast<uint8_t>(i));
	}
	std::ranges::shuffle(v, std::mt19937(m_key));

	for (int i = 0; i < MAP_SIZE; i++)
	{
		m_map[v[i]] = static_cast<uint8_t>(i);
	}
}
