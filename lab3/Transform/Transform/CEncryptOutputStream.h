#pragma once
#include <map>

#include "CStreamDecorator.h"

class CEncryptOutputStream final : public COutputStreamDecorator
{
public:
	explicit CEncryptOutputStream(IOutputPtr&& stream, int const key);
	void WriteByte(const uint8_t data) override;
	void WriteBlock(const void* srcData, const std::streamsize size) override;
	bool Flush() override;

private:
	void GenerateMap();

private:
	using Map = std::map<uint8_t, uint8_t>;
	const int MAP_SIZE = 256;
	int m_key;
	Map m_map;
};

