#pragma once
#include "Common.h"
#include "File.h"

namespace Ablaze
{

	class AB_API FileSystem
	{
	public:
		FileSystem() = delete;

		static bool FileExists(const String& filename);
		static uint64 SizeOf(const String& filename);
		static uint64 SizeOf(const File& file);

		static File Get(const String& filename);
		static File CreateNew(const String& filename);
		static File Open(const String& filename, OpenMode mode);
		static bool Close(const File& fileHandle);
		static void Clear(const File& fileHandle);
		static bool Delete(const File& fileHandle);
		static bool Rename(const File& fileHandle, const String& filename);

		static void Read(const File& file, int64 byteCount, void* buffer);
		static void* Read(const File& file, int64 byteCount);
		static void* Read(const File& file, int64* bytesRead);
		static String ReadText(const File& file);
		static void ReadText(const File& file, String* outText);

		static void Write(const File& file, int64 byteCount, byte* buffer);
		static void Write(const File& file, byte* buffer);
		static void WriteText(const File& file, const String& text);

		static void Copy(const File& file, const String& newPath);
		static void Copy(const File& srcFile, const File& dstFile);

		friend class File;

	private:
		static Handle OpenFileForReading(const String& filename);
		static Handle OpenFileForAppending(const String& filename);
		static Handle OpenFileForOverride(const String& filename);
		static Handle OpenInternal(const String& filename, OpenMode mode);
		static bool CloseInternal(Handle handle);
		static bool DeleteInternal(const String& filename);

	};

}