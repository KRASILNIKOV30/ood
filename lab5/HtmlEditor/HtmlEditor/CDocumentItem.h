#pragma once
#include "IImage.h"
#include "IParagraph.h"

class CConstDocumentItem
{
public:
	explicit CConstDocumentItem(std::shared_ptr<const IImage>&& image)
		: m_image(std::move(image))
	{
	}

	explicit CConstDocumentItem(std::shared_ptr<const IParagraph>&& paragraph = nullptr)
		: m_paragraph(std::move(paragraph))
	{
	}

	std::shared_ptr<const IImage> GetImage() const
	{
		return m_image;
	}

	std::shared_ptr<const IParagraph> GetParagraph() const
	{
		return m_paragraph;
	}

	virtual std::string ToString() const
	{
		if (m_image != nullptr)
		{
			return m_image->ToString();
		}
		return m_paragraph->ToString();
	}

	void Remove()
	{
		m_removed = true;
	}

	void Restore()
	{
		m_removed = false;
	}

	bool IsRemoved() const
	{
		return m_removed;
	}

	bool operator==(CConstDocumentItem const& right) const
	{
		return m_image == right.GetImage() && m_paragraph == right.GetParagraph();
	}

	virtual ~CConstDocumentItem() = default;

private:
	std::shared_ptr<const IImage> m_image = nullptr;
	std::shared_ptr<const IParagraph> m_paragraph = nullptr;
	bool m_removed = false;
};

class CDocumentItem final : public CConstDocumentItem
{
public:
	explicit CDocumentItem(std::shared_ptr<IImage>&& image)
		: m_image(std::move(image))
	{
	}

	explicit CDocumentItem(std::shared_ptr<IParagraph>&& paragraph = nullptr)
		: m_paragraph(std::move(paragraph))
	{
	}

	void ToHtml(std::ostream& strm, std::filesystem::path imgPath) const
	{
		if (m_image)
		{
			auto& dest = imgPath;
			auto path = m_image->GetPath();
			auto filename = path.filename();
			dest.concat("/") += filename;
			copy_file(path, dest);
			std::filesystem::path imgSrc = "images/";
			imgSrc += filename;
			strm << "<img width=" << m_image->GetWidth() << " height=" << m_image->GetHeight();
			strm << " src=" << imgSrc << "/>" << std::endl;
		}
		if (m_paragraph)
		{
			strm << "<p>" << m_paragraph->GetText() << "</p>" << std::endl;
		}
	}

	std::shared_ptr<IImage> GetImage()
	{
		return m_image;
	}

	std::string ToString() const override
	{
		if (m_image != nullptr)
		{
			return m_image->ToString();
		}
		return m_paragraph->ToString();
	}

	std::shared_ptr<IParagraph> GetParagraph()
	{
		return m_paragraph;
	}

private:
	std::shared_ptr<IImage> m_image = nullptr;
	std::shared_ptr<IParagraph> m_paragraph = nullptr;
};