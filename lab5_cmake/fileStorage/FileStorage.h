#include "FileRef.h"
#include "FolderEntity.h"

#include <set>
#include <unordered_map>
#include <vector>

class FileStorage
{
public:
	explicit FileStorage(Path const& path)
		: m_storageFolder(FolderEntityPtr(std::make_shared<FolderEntity>(path)))
	{}

	FileRefPtr AddFile(Path const& path)
	{
		const Path name = std::tmpnam(nullptr);
		auto const ext = path.extension();
		auto const filePath = m_storageFolder->GetPath() / (name.filename() += ext);
		auto fileRefPtr = std::make_shared<FileRef>(std::make_shared<FileEntity>(filePath, path), m_storageFolder);
		m_allFileRefs.emplace(filePath, fileRefPtr);
		if (!exists(filePath))
		{
			copy_file(path, filePath);
		}
		return fileRefPtr;
	}

	static void Save(Path const& path, std::vector<Path> const& files)
	{
		for (auto const& file : files)
		{
			copy_file(file, path / file.filename() += file.extension());
		}
	}

private:
	FolderEntityPtr m_storageFolder;
	std::unordered_map<std::string, FileRefWeakPtr> m_allFileRefs;
	std::set<FileRefPtr> m_usedFileRefs;
};
