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
	//Убрать утечки памяти (исправлено)
	char* buffer = new char[size];
	try
	{
		memcpy_s(buffer, size, srcData, size);

		for (int pos = 0; pos < size; pos++)
		{
			WriteByte(*(buffer + pos));
		}
	}
	catch (std::exception&)
	{
		delete[] buffer;
		throw std::ios_base::failure("Fail to write block");
	}
	delete[] buffer;
}
