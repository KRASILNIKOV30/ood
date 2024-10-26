#pragma once
#include <utility>
#include <sstream>
#include "./IParagraph.h"
#include "../edits/ReplaceTextEdit.h"
#include "../edits/EditSink.h"

class Paragraph final : public IParagraph, public std::enable_shared_from_this<IParagraph>
{
public:
	explicit Paragraph(std::string text, EditSink editSink)
		: m_text(std::move(text))
		, m_sink(std::move(editSink))
	{
	}

	[[nodiscard]] std::string GetText() const override
	{
		return m_text;
	}

	void SetText(const std::string& text) override
	{
		auto prevText = m_text;
		m_text = text;

		m_sink(std::make_shared<ReplaceTextEdit>(
			shared_from_this(),
			[&](std::string const& t) { m_text = t; },
			prevText));
	}

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream strm;
		strm << "Paragraph: " << m_text;
		return strm.str();
	}

private:
	std::string m_text;
	EditSink m_sink;
};