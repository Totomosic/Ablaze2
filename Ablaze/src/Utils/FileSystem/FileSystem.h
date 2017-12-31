#pragma once
#include "DirectoryPath.h"
#include "File.h"
#include "Filepath.h"

#define AB_GET_CURRENT_DIRECTORY _getcwd

namespace Ablaze
{

	class AB_API Filesystem
	{
	private:
		static DirectoryPath s_WorkingDirectory; // Includes trailing backslash

	public:
		Filesystem() = delete;

		static const DirectoryPath& WorkingDirectory();

		static int FileSize(const Filepath& filename);
		static bool FileExists(const Filepath& filename);

		static void Rename(const Filepath& filename, const Filepath& newFilename);
		static void Rename(File& file, const Filepath& newFilename);

		static File GetFile(const Filepath& filename);
		static File OpenFile(const Filepath& filename, OpenFlags flags = OpenFlags::Read);
		static File CreateNewFile(const Filepath& filename);
		static void CreateNewDirectory(const DirectoryPath& directoryPath);
		static bool DirectoryExists(const DirectoryPath& path);

		static bool Delete(const Filepath& filename);
		static bool Delete(const File& file);

		friend class Engine;

	private:
		static void Initialise();

	};

}