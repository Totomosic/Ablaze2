#include "Filepath.h"
#include "Filesystem.h"

namespace Ablaze
{

	Filepath::Filepath() : Object(),
		m_Path(), m_Directory()
	{

	}

	Filepath::Filepath(const String& path) : Object(),
		m_Path(path)
	{
		CleanPath(m_Path);
		m_Directory = DirectoryPath(ParseFile(m_Path));
	}

	Filepath::Filepath(const char* path) : Filepath(String(path))
	{

	}

	const String& Filepath::Path() const
	{
		return m_Path;
	}

	bool Filepath::Exists() const
	{
		return Filesystem::FileExists(Path());
	}

	const DirectoryPath& Filepath::Directory() const
	{
		return m_Directory;
	}

	String Filepath::Filename() const
	{
		int index = m_Path.find_last_of('/');
		return m_Path.substr(index + 1, m_Path.length() - index - 1);
	}
	
	String Filepath::Extension() const
	{
		int index = m_Path.find_last_of('.');
		return m_Path.substr(index + 1, m_Path.length() - index - 1);
	}

	String Filepath::ToString() const
	{
		return Path();
	}

	std::ostream& operator<<(std::ostream& stream, const Filepath& path)
	{
		stream << path.ToString();
		return stream;
	}

	String Filepath::ParseFile(const String& path)
	{
		int index = m_Path.find_last_of('/');
		return m_Path.substr(0, index + 1);
	}

	void Filepath::CleanPath(String& path)
	{
		std::replace(path.begin(), path.end(), '\\', '/');
	}

}