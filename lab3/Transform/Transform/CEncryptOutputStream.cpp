#include "CEncryptOutputStream.h"

#include <algorithm>
#include <random>
#include <vector>

CEncryptOutputStream::CEncryptOutputStream(IOutputPtr&& stream, int const key)
	: COutputStreamDecorator(std::move(stream))
	, m_key(key)
{
}

void CEncryptOutputStream::WriteByte(const uint8_t data)
{

}

void CEncryptOutputStream::WriteBlock(const void* srcData, const std::streamsize size)
{
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
