#include "Filesystem.h"

namespace Ablaze
{

	int Filesystem::FileSize(const String& filename)
	{
		return std::experimental::filesystem::file_size(filename);
	}

	bool Filesystem::FileExists(const String& filename)
	{
		return std::experimental::filesystem::exists(filename);
	}

	void Filesystem::Rename(const String& filename, const String& newFilename)
	{
		std::experimental::filesystem::rename(filename, newFilename);
	}

	void Filesystem::Rename(File& file, const String& newFilename)
	{
		file.Rename(newFilename);
	}

	File Filesystem::GetFile(const String& filename)
	{
		return File(filename);
	}

	File Filesystem::OpenFile(const String& filename, OpenFlags flags)
	{
		File f = GetFile(filename);
		f.Open(flags);
		return f;
	}

	File Filesystem::CreateNewFile(const String& filename)
	{
		File f = GetFile(filename);
		f.Clear();
		return f;
	}

	bool Filesystem::Delete(const String& filename)
	{
		return true;
	}

	bool Filesystem::Delete(const File& file)
	{
		return Delete(file.Filename());
	}

}