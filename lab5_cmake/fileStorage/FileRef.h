#pragma once
#include <utility>
#include "FileEntity.h"
#include "FolderEntity.h"

class FileRef
{
public:
	explicit FileRef(FileEntityPtr file, FolderEntityPtr folder)
		: m_file(std::move(file))
		, m_folder(std::move(folder))
	{
	}

	[[nodiscard]] Path const& GetPath() const
	{
		return m_file->GetPath();
	}

	[[nodiscard]] Path const& GetOriginalPath() const
	{
		return m_file->GetOriginalPath();
	}

	void KeepAlive() noexcept
	{
		m_file->KeepAlive();
	}

private:
	FileEntityPtr m_file;
	FolderEntityPtr m_folder;
};

using FileRefPtr = std::shared_ptr<FileRef>;
using FileRefWeakPtr = std::weak_ptr<FileRef>;
