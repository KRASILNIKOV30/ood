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
	//Использовать приведение (Исправлено)
	int bytesWereRead = 0;
	uint8_t* dst = static_cast<uint8_t*>(dstBuffer);
	while (bytesWereRead < size)
	{
		if (!m_count && !NextBlock())
		{
			break;
		}
		*(dst++) = m_currByte;
		//memset(static_cast<char*>(dstBuffer) + bytesWereRead, m_currByte, 1);
		bytesWereRead++;
		m_count--;
	}
	return bytesWereRead;
}

bool CDecompressiveInputStream::NextBlock()
{
	if (CInputStreamDecorator::IsEOF())
	{
		return false;
	}
	//Не прибавлять символ ноль (Исправлено)
	m_count = CInputStreamDecorator::ReadByte();
	m_currByte = CInputStreamDecorator::ReadByte();
	return true;
}
