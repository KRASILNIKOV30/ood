#pragma once
#include "IDataStreams.h"

class CInputStreamDecorator : public IInputDataStream
{
public:
	bool IsEOF() const override
	{
		return m_stream->IsEOF();
	}

	uint8_t ReadByte() override
	{
		return m_stream->ReadByte();
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize const size) override
	{
		return m_stream->ReadBlock(dstBuffer, size);
	}

protected:
	explicit CInputStreamDecorator(IInputPtr&& stream)
		: m_stream(std::move(stream))
	{
	}

public:
	IInputPtr m_stream;
};

class COutputStreamDecorator : public IOutputDataStream
{
public:
	void WriteByte(uint8_t const data) override
	{
		m_stream->WriteByte(data);
	}

	void WriteBlock(const void* srcData, std::streamsize const size) override
	{
		m_stream->WriteBlock(srcData, size);
	}

	bool Flush() override
	{
		return m_stream->Flush();
	}

protected:
	explicit COutputStreamDecorator(IOutputPtr&& stream)
		: m_stream(std::move(stream))
	{
	}

public:
	IOutputPtr m_stream;
};