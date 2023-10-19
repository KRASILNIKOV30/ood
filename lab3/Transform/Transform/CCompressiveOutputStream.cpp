#include "CCompressiveOutputStream.h"

CCompressiveOutputStream::CCompressiveOutputStream(IOutputPtr&& stream)
	: COutputStreamDecorator(std::move(stream))
{
}

void CCompressiveOutputStream::WriteByte(const uint8_t data)
{
	if (m_count == MAX_BLOCK_SIZE || data != m_currByte)
	{
		Flush();
		m_count = 1;
		m_currByte = data;
	}
	else
	{
		m_count++;
	}
}

void CCompressiveOutputStream::WriteBlock(const void* srcData, const std::streamsize size)
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

	for (int i = 0; i < size; i++)
	{
		WriteByte(*(buffer + i));
	}
}

void CCompressiveOutputStream::Flush()
{
	if (m_count)
	{
		COutputStreamDecorator::WriteByte(m_count + '0');
		COutputStreamDecorator::WriteByte(m_currByte);
		m_count = 0;
		m_currByte = NULL;
	}
}

CCompressiveOutputStream::~CCompressiveOutputStream()
{
	Flush();
}
