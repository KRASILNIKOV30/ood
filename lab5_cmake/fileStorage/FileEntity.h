#pragma once
#include "Path.h"

class FileEntity
{
public:
	explicit FileEntity(Path path)
		: m_path(std::move(path))
	{
	}

	[[nodiscard]] Path GetPath() const noexcept
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
			fs::remove(m_path);
		}
	}

private:
	const Path m_path;
	bool m_keepAlive = false;
};