#include "CFileOutputStream.h"

CFileOutputStream::CFileOutputStream(std::string const& filename)
    : m_stream(std::ofstream(filename, std::ios::binary))
{
    if (!m_stream.is_open())
    {
        throw std::ios_base::failure("Failed to open file for reading");
    }
}

void CFileOutputStream::WriteByte(uint8_t const data)
{
    if (!(m_stream << data))
    {
        throw std::ios_base::failure("Fail to write data to file");
    }
}

void CFileOutputStream::WriteBlock(const void* srcData, std::streamsize const size)
{
    std::string str;
    memcpy_s(str.data(), size, srcData, size);
    m_stream.write(str.c_str(), size);
}

void CFileOutputStream::Close()
{
    m_stream.close();
}

CFileOutputStream::~CFileOutputStream()
{
    if (m_stream.is_open())
    {
        m_stream.close();
    }
}

void CFileOutputStream::Flush()
{
	m_stream.flush();
}
