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
    m_stream.write(buffer, size);
}

void CFileOutputStream::Close()
{
    m_stream.close();
}