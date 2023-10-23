#include "CEncryptOutputStream.h"

#include <algorithm>
#include <random>
#include <vector>

CEncryptOutputStream::CEncryptOutputStream(IOutputPtr&& stream, int const key)
	: COutputStreamDecorator(std::move(stream))
	, m_key(key)
{
	GenerateMap();
}

void CEncryptOutputStream::WriteByte(const uint8_t data)
{
	COutputStreamDecorator::WriteByte(m_map[data]);
}

void CEncryptOutputStream::WriteBlock(const void* srcData, const std::streamsize size)
{
	char* buffer = new char[size];
	try
	{
		memcpy_s(buffer, size, srcData, size);

		for (int i = 0; i < size; i++)
		{
			WriteByte(*(buffer + i));
		}
	}
	catch (std::exception&)
	{
		delete[] buffer;
		throw std::ios_base::failure("Fail to write block");
	}
	delete[] buffer;
}

bool CEncryptOutputStream::Flush()
{
	return COutputStreamDecorator::Flush();
}

void CEncryptOutputStream::GenerateMap()
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
		m_map[static_cast<uint8_t>(i)] = v[i];
	}
}
