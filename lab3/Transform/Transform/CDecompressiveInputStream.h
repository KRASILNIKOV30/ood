#pragma once
#include "CStreamDecorator.h"

class CDecompressiveInputStream final : public CInputStreamDecorator
{
public:
	explicit CDecompressiveInputStream(IInputPtr&& stream);
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, const std::streamsize size) override;

private:
	bool NextBlock();

private:
	uint8_t m_count = 0;
	uint8_t m_currByte = NULL;
};

