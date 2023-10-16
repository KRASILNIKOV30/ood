#include "CMemoryInputStream.h"

CMemoryInputStream::CMemoryInputStream(std::vector<uint8_t> const& v)
	: m_memory(v)
{
}

CMemoryInputStream::CMemoryInputStream(std::vector<uint8_t>&& v)
	: m_memory(std::move(v))
{
}

bool CMemoryInputStream::IsEOF() const
{
	return m_pos == m_memory.size();
}

uint8_t CMemoryInputStream::ReadByte()
{
    if (IsEOF())
    {
        throw std::ios_base::failure("End of file has been reached");
    }

	return m_memory[m_pos++];
}

std::streamsize CMemoryInputStream::ReadBlock(void* dstBuffer, const std::streamsize size)
{
    const auto start = m_pos;
    char* bytes = new char[size];
    while (!IsEOF() && m_pos - start < size)
    {
        char* dst = bytes + m_pos - start;
        memset(dst, ReadByte(), 1);
    }
    memcpy_s(dstBuffer, m_pos - start, bytes, m_pos - start);
    return m_pos - start;
}
