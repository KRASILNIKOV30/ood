#pragma once
#include "Path.h"

class FileEntity
{
public:
	explicit FileEntity(Path path)
		: m_path(std::move(path))
	{
	}

	[[nodiscard]] Path const& GetPath() const noexcept
	{
		return m_path;
	}

	void KeepAlive() noexcept
	{
		m_keepAlive = true;
	}

	~FileEntity() noexcept
	{
		if (!m_keepAlive)
		{
			std::error_code ec;
			fs::remove(m_path, ec);
		}
	}

private:
	const Path m_path;
	bool m_keepAlive = false;
};

using FileEntityPtr = std::shared_ptr<FileEntity>;