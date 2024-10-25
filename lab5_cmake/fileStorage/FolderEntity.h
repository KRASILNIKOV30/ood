#pragma once
#include "Path.h"

class FolderEntity
{
public:
	explicit FolderEntity(Path path)
		: m_path(std::move(path))
	{
	}

	[[nodiscard]] Path GetPath() const noexcept
	{
		return m_path;
	}

	~FolderEntity()
	{
		if (is_empty(m_path))
		{
			fs::remove(m_path);
		}
	}

private:
	Path m_path;
};

using FolderEntityPtr = std::shared_ptr<FolderEntity>;