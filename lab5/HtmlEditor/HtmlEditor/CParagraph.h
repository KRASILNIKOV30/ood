#pragma once
#include "./IParagraph.h"

class CParagraph final : public IParagraph
{
public:
	explicit CParagraph(std::string const& text)
		: m_text(text)
	{
	}

	std::string GetText() const override
	{
		return m_text;
	}

	void SetText(const std::string& text) override
	{
		m_text = text;
	}

	std::string ToString() const override
	{
		std::stringstream strm;
		strm << "Paragraph: " << m_text;
		return strm.str();
	}

private:
	std::string m_text;
};