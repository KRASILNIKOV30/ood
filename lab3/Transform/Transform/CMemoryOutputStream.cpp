#include "CMemoryOutputStream.h"

CMemoryOutputStream::CMemoryOutputStream(std::vector<uint8_t>& v)
	: m_memory(v)
{
}

void CMemoryOutputStream::WriteByte(uint8_t const data)
{
	try
	{
		m_memory.push_back(data);
	}
	catch (std::exception&)
	{
		throw std::ios_base::failure("Fail to write byte");
	}
}

void CMemoryOutputStream::WriteBlock(const void* srcData, std::streamsize const size)
{
	char* buffer;
	try
	{
		buffer = new char[size];
	}
	catch (std::exception&)
	{
		throw std::ios_base::failure("Fail to write block");
	}
	memcpy_s(buffer, size, srcData, size);

	for (int pos = 0; pos < size; pos++)
	{
		WriteByte(*buffer);
		buffer += 1;
	}
}
