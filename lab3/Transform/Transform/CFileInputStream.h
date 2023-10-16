#pragma once
#include "IDataStreams.h"
#include <fstream>
#include <string>

class CFileInputStream final : public IInputDataStream
{
public:
	explicit CFileInputStream(std::string const& filename);
	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, const std::streamsize size) override;
	~CFileInputStream() override;

private:
	std::ifstream m_stream;
	std::streamsize m_length;
	std::streamsize m_pos = 0;
};

