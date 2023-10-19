#include "CFileInputStream.h"

CFileInputStream::CFileInputStream(std::string const& filename)
	: m_stream(std::ifstream(filename, std::ios::binary))
{
    if (!m_stream.is_open())
    {
        throw std::ios_base::failure("Failed to open file for reading");
    }
    m_stream.seekg(0, std::ifstream::end);
    m_length = m_stream.tellg();
    m_stream.seekg(0, std::ifstream::beg);
}

bool CFileInputStream::IsEOF() const
{
    if (!m_stream.good())
    {
        throw std::ios_base::failure("Error has occurred");
    }
    return m_length == m_pos;
}

uint8_t CFileInputStream::ReadByte()
{
    if (IsEOF())
    {
        throw std::ios_base::failure("End of file has been reached");
    }
    m_pos++;
    return static_cast<uint8_t>(m_stream.get());
}

std::streamsize CFileInputStream::ReadBlock(void* dstBuffer, const std::streamsize size)
{
    const auto start = m_pos;
    char* bytes = new char[size];
    try
    {
        while (!IsEOF() && m_pos - start < size)
        {
            char* dst = bytes + m_pos - start;
            memset(dst, ReadByte(), 1);
        }
        memcpy_s(dstBuffer, m_pos - start, bytes, m_pos - start);
        return m_pos - start;
    }
    catch (std::exception& e)
    {
        delete[] bytes;
        throw e;
    }

    delete[] bytes;
}

CFileInputStream::~CFileInputStream()
{
    m_stream.close();
}
