#include "DirectoryPath.h"
#include "Filesystem.h"
#include "Filepath.h"

namespace Ablaze
{

	DirectoryPath::DirectoryPath() : Object(),
		m_Path(), m_ParentPath()
	{
		
	}

	DirectoryPath::DirectoryPath(const String& path) : Object(),
		m_Path(path)
	{
		CleanPath(m_Path);
		m_ParentPath = ParseDirectory(m_Path);
	}

	DirectoryPath::DirectoryPath(const char* path) : DirectoryPath(String(path))
	{
	
	}

	const String& DirectoryPath::Path() const
	{
		return m_Path;
	}

	bool DirectoryPath::Exists() const
	{
		return Filesystem::DirectoryExists(*this);
	}

	bool DirectoryPath::HasParent() const
	{
		return Parent().Exists();
	}

	DirectoryPath DirectoryPath::Parent() const
	{
		return DirectoryPath(m_ParentPath);
	}

	String DirectoryPath::ToString() const
	{
		return m_Path;
	}

	std::ostream& operator<<(std::ostream& stream, const DirectoryPath& path)
	{
		stream << path.ToString();
		return stream;
	}

	String DirectoryPath::ParseDirectory(const String& path)
	{
		int index = path.find_last_of('/');
		if (index == path.length() - 1)
		{
			index = path.substr(0, path.length() - 2).find_last_of('/');
		}
		String parentPath = path.substr(0, index) + '/';
		return parentPath;
	}

	void DirectoryPath::CleanPath(String& path)
	{
		std::replace(path.begin(), path.end(), '\\', '/');
	}

}