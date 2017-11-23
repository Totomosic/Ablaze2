#pragma once
#include "File.h"

namespace Ablaze
{

	class AB_API Filesystem
	{
	public:
		Filesystem() = delete;

		static int FileSize(const String& filename);
		static bool FileExists(const String& filename);

		static void Rename(const String& filename, const String& newFilename);
		static void Rename(File& file, const String& newFilename);

		static File GetFile(const String& filename);
		static File OpenFile(const String& filename, OpenFlags flags = OpenFlags::Read);
		static File CreateNewFile(const String& filename);
		static void CreateNewDirectory(const String& directoryPath);

		static bool Delete(const String& filename);
		static bool Delete(const File& file);

	};

}