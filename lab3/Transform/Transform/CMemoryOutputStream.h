#pragma once
#include <vector>
#include "IDataStreams.h"

class CMemoryOutputStream final : public IOutputDataStream
{
public:
	explicit CMemoryOutputStream(std::vector<uint8_t>& v);
	void WriteByte(uint8_t const data) override;
	void WriteBlock(const void* srcData, std::streamsize const size) override;

private:
	std::vector<uint8_t>& m_memory;
};

