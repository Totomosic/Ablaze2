#include "Filesystem.h"
#include <experimental\filesystem>

namespace Ablaze
{

	DirectoryPath Filesystem::s_WorkingDirectory = DirectoryPath();

	const DirectoryPath& Filesystem::WorkingDirectory()
	{
		return s_WorkingDirectory;
	}

	int Filesystem::FileSize(const Filepath& filename)
	{
		return std::experimental::filesystem::file_size(filename.Path());
	}

	bool Filesystem::FileExists(const Filepath& filename)
	{
		return std::experimental::filesystem::exists(filename.Path());
	}

	void Filesystem::Rename(const Filepath& filename, const Filepath& newFilename)
	{
		std::experimental::filesystem::rename(filename.Path(), newFilename.Path());
	}

	void Filesystem::Rename(File& file, const Filepath& newFilename)
	{
		file.Rename(newFilename);
	}

	File Filesystem::GetFile(const Filepath& filename)
	{
		return File(filename);
	}

	File Filesystem::OpenFile(const Filepath& filename, OpenFlags flags)
	{
		if (flags == OpenFlags::Read)
		{
			AB_ASSERT(FileExists(filename), "File: " + filename.Path() + " could not be found");
		}
		File f = GetFile(filename);
		f.Open(flags);
		return f;
	}

	File Filesystem::CreateNewFile(const Filepath& filename)
	{
		File f = GetFile(filename);
		f.Clear();
		return f;
	}

	void Filesystem::CreateNewDirectory(const DirectoryPath& directoryPath)
	{
		std::experimental::filesystem::create_directory(directoryPath.Path());
	}

	bool Filesystem::DirectoryExists(const DirectoryPath& path)
	{
		return std::experimental::filesystem::is_directory(path.Path());
	}

	bool Filesystem::Delete(const Filepath& filename)
	{
		int result = std::remove(filename.Path().c_str());
		return result == 0;
	}

	bool Filesystem::Delete(const File& file)
	{
		return Delete(file.Filename());
	}

	void Filesystem::Initialise()
	{
		char buff[FILENAME_MAX];
		AB_GET_CURRENT_DIRECTORY(buff, FILENAME_MAX);
		s_WorkingDirectory = DirectoryPath(String(buff) + '\\');
	}

}