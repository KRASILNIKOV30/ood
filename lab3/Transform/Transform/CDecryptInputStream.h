#pragma once
#include <map>

#include "CStreamDecorator.h"

class CDecryptInputStream final : public CInputStreamDecorator
{
public:
	explicit CDecryptInputStream(IInputPtr&& stream, int const key);
	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, const std::streamsize size) override;

private:
	void GenerateMap();

private:
	using Map = std::map<uint8_t, uint8_t>;
	const int MAP_SIZE = 256;
	int m_key;
	Map m_map;
};

