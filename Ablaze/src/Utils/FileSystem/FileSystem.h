#pragma once
#include "Common.h"

namespace Ablaze
{

	enum class OpenMode
	{
		ReplaceExisting,
		AppendData
	};

	class AB_API FileSystem
	{
	public:
		FileSystem() = delete;

		static bool FileExists(const String& filename);
		static int64 SizeOf(const String& filename);

		static void* CreateNew(const String& filename);
		static void* Open(const String& filename, OpenMode mode = OpenMode::ReplaceExisting);
		static bool Close(void* fileHandle);
		static void Clear(void* fileHandle);
		static void Delete(void* fileHandle);
		static void Rename(void* fileHandle, const String& filename);

		static void Read(void* fileHandle, int64 byteCount, byte* buffer);
		static byte* Read(void* fileHandle, int64 byteCount);
		static byte* Read(void* fileHandle, int64* bytesRead);
		static String ReadText(void* fileHandle);
		static void ReadText(void* fileHandle, String* outText);

		static void Write(void* fileHandle, int64 byteCount, byte* buffer);
		static void Write(void* fileHandle, byte* buffer);
		static void WriteText(void* fileHandle, const String& text);

		static void Copy(void* fileHandle, const String& newFilePath);
		static void Copy(void* srcFileHandle, void* dstFileHandle);

	};

}