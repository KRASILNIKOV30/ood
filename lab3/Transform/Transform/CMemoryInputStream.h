#pragma once
#include "IDataStreams.h"
#include <vector>

class CMemoryInputStream final : public IInputDataStream
{
public:
	explicit CMemoryInputStream(std::vector<uint8_t> const& v);
	explicit CMemoryInputStream(std::vector<uint8_t>&& v);
	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::vector<uint8_t> m_memory;
	size_t m_pos = 0;
};

