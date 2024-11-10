#pragma once
#include "Path.h"

class FileEntity
{
public:
	explicit FileEntity(Path path, Path originalPath)
		: m_path(std::move(path))
		, m_originalPath(std::move(originalPath))
	{
	}

	[[nodiscard]] Path const& GetPath() const noexcept
	{
		return m_path;
	}

	[[nodiscard]] Path const& GetOriginalPath() const noexcept
	{
		return m_originalPath;
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
	const Path m_originalPath;
};

using FileEntityPtr = std::shared_ptr<FileEntity>;