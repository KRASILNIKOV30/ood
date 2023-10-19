#pragma once
#include "CStreamDecorator.h"

class CCompressiveOutputStream final : public COutputStreamDecorator
{
public:
	explicit CCompressiveOutputStream(IOutputPtr&& stream);
	void WriteByte(const uint8_t data) override;
	void WriteBlock(const void* srcData, const std::streamsize size) override;
	void Flush();
	~CCompressiveOutputStream() override;

private:
	const uint8_t MAX_BLOCK_SIZE = 8;
	uint8_t m_currByte = NULL;
	uint8_t m_count = 0;
};

