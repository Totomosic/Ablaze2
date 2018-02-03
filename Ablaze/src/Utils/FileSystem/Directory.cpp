#include "Directory.h"
#include "Filesystem.h"

namespace Ablaze
{

	Directory::Directory(const DirectoryPath& path) : Object(),
		m_Path(path)
	{

	}

	Directory Directory::Parent() const
	{
		return Directory(m_Path.Parent());
	}

	int Directory::FileCount() const
	{
		return Filesystem::EnumerateDirectories(m_Path).size();
	}

	int Directory::DirectoryCount() const
	{
		return Filesystem::EnumerateFiles(m_Path).size();
	}

	int Directory::ItemCount() const
	{
		return FileCount() + DirectoryCount();
	}

	bool Directory::IsEmpty() const
	{
		return ItemCount() == 0;
	}

	bool Directory::HasDirectory(const String& name) const
	{
		DirectoryPath path = m_Path + name;
	}

}