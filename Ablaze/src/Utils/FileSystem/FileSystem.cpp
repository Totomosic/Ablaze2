#include "FileSystem.h"
#include <Windows.h>

namespace Ablaze
{

	bool FileSystem::FileExists(const String& filepath)
	{
		
	}

	int64 FileSystem::SizeOf(const String& filepath)
	{

	}

	Handle FileSystem::CreateNew(const String& filepath)
	{
	
	}

	Handle FileSystem::Open(const String& filepath, OpenMode mode)
	{
	
	}

	bool FileSystem::Close(Handle file)
	{
	
	}

	void FileSystem::Clear(Handle file)
	{
	
	}

	bool FileSystem::Delete(Handle file)
	{
	
	}

	bool FileSystem::Rename(Handle file, const String& newName)
	{
	
	}

	void FileSystem::Read(Handle file, int64 numBytes, byte* buffer)
	{
	
	}

	byte* FileSystem::Read(Handle file, int64 numBytes)
	{
	
	}

	byte* FileSystem::Read(Handle file, int64* bytesRead)
	{
	
	}

	String FileSystem::ReadText(Handle file)
	{
	
	}

	void FileSystem::ReadText(Handle file, String* outText)
	{
	
	}

	void FileSystem::Write(Handle file, int64 numBytes, byte* buffer)
	{
	
	}

	void FileSystem::Write(Handle file, byte* buffer)
	{
	
	}

	void FileSystem::WriteText(Handle file, const String& text)
	{
	
	}

	void FileSystem::Copy(Handle srcFile, Handle dstFile)
	{
	
	}

	void FileSystem::Copy(Handle srcFile, const String& dstFilePath)
	{
	
	}

}