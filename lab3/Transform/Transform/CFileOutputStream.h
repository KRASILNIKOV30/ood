#pragma once
#include "IDataStreams.h"
#include <fstream>
#include <string>

class CFileOutputStream final : public IOutputDataStream
{
public:
	explicit CFileOutputStream(std::string const& filename);
	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize const size) override;
	void Close();

private:
	std::ofstream m_stream;
};

