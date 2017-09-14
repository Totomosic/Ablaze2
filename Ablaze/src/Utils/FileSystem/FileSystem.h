#pragma once
#include "Common.h"

namespace Ablaze
{

	enum class OpenMode
	{
		Read,
		WriteOverride,
		WriteAppend
	};

	class AB_API FileSystem
	{
	public:
		FileSystem() = delete;

		static bool FileExists(const String& filename);
		static int64 SizeOf(const String& filename);

		static Handle CreateNew(const String& filename);
		static Handle Open(const String& filename, OpenMode mode);
		static bool Close(Handle fileHandle);
		static void Clear(Handle fileHandle);
		static bool Delete(Handle fileHandle);
		static bool Rename(Handle fileHandle, const String& filename);

		static void Read(Handle fileHandle, int64 byteCount, byte* buffer);
		static byte* Read(Handle fileHandle, int64 byteCount);
		static byte* Read(Handle fileHandle, int64* bytesRead);
		static String ReadText(Handle fileHandle);
		static void ReadText(Handle fileHandle, String* outText);

		static void Write(Handle fileHandle, int64 byteCount, byte* buffer);
		static void Write(Handle fileHandle, byte* buffer);
		static void WriteText(Handle fileHandle, const String& text);

		static void Copy(Handle fileHandle, const String& newFilePath);
		static void Copy(Handle srcFileHandle, Handle dstFileHandle);

	};

}