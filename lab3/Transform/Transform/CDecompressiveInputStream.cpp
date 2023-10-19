#include "CDecompressiveInputStream.h"
#include "CFileInputStream.h"

CDecompressiveInputStream::CDecompressiveInputStream(IInputPtr&& stream)
	: CInputStreamDecorator(std::move(stream))
{
}

uint8_t CDecompressiveInputStream::ReadByte()
{
	if (!m_count && !NextBlock())
	{
		throw std::ios_base::failure("End of file has been reached");
	}
	m_count--;
	return m_currByte;
}

std::streamsize CDecompressiveInputStream::ReadBlock(void* dstBuffer, const std::streamsize size)
{
	char* bytes = new char[size];
	int bytesWereRead = 0;
	while (bytesWereRead < size)
	{
		if (!m_count && !NextBlock())
		{
			break;
		}
		memset(bytes + bytesWereRead, m_currByte, 1);
		bytesWereRead++;
		m_count--;
	}
	memcpy_s(dstBuffer, bytesWereRead, bytes, bytesWereRead);
	delete[] bytes;
	return bytesWereRead;
}

bool CDecompressiveInputStream::NextBlock()
{
	if (CInputStreamDecorator::IsEOF())
	{
		return false;
	}
	m_count = CInputStreamDecorator::ReadByte() - '0';
	m_currByte = CInputStreamDecorator::ReadByte();
	return true;
}
