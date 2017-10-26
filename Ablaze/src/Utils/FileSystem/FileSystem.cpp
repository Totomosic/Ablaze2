#include "FileSystem.h"
#include <Windows.h>

namespace Ablaze
{

	void CALLBACK FileIOCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
	{
	}

	bool FileSystem::FileExists(const String& filepath)
	{
		DWORD result = GetFileAttributes(filepath.c_str());
		return !(result == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND);
	}

	uint64 FileSystem::SizeOf(const String& filepath)
	{
		return SizeOf(Get(filepath));
	}

	uint64 FileSystem::SizeOf(const File& file)
	{
		OpenMode mode = OpenMode::Read;
		bool wasOpen = false;
		if (file.IsOpen())
		{
			mode = file.GetMode();
			file.Close();
			file.Open(OpenMode::Read);
			wasOpen = true;
		}
		else
		{
			file.Open(OpenMode::Read);
		}

		LARGE_INTEGER size = { 0 };
		if (!GetFileSizeEx(file.GetHandle(), &size))
		{
			AB_ERROR("Could not determine size of file: " + file.GetPath());
		}

		file.Close();
		if (wasOpen)
		{
			file.Open(mode);
		}
		return size.QuadPart;
	}

	File FileSystem::Get(const String& filepath)
	{
		File file(filepath);
		return file;
	}

	File FileSystem::CreateNew(const String& filepath)
	{
		if (FileExists(filepath))
		{
			Delete(filepath);
		}
		File f = Get(filepath);
		return f;
	}

	File FileSystem::Open(const String& filepath, OpenMode mode)
	{
		File file = Get(filepath);
		file.Open(mode);
		return file;
	}

	bool FileSystem::Close(const File& file)
	{
		file.Close();
		return true;
	}

	void FileSystem::Clear(File& file)
	{
		OpenMode mode = file.GetMode();
		Delete(file);
		file = CreateNew(file.GetPath());
		file.Open(mode);
	}

	bool FileSystem::Delete(const File& file)
	{
		file.Delete();
		return true;
	}

	bool FileSystem::Delete(const String& filename)
	{
		DeleteInternal(filename);
		return true;
	}

	bool FileSystem::Rename(const File& file, const String& newName)
	{
		return true;
	}

	void FileSystem::Read(const File& file, int64 numBytes, void* buffer)
	{
		OVERLAPPED ol = { 0 };
		ReadFileEx(file.GetHandle(), buffer, numBytes, &ol, FileIOCompletionRoutine);
	}

	void* FileSystem::Read(const File& file, int64 numBytes)
	{
		void* buffer = new byte[numBytes];
		Read(file, numBytes, buffer);
		return buffer;
	}

	void* FileSystem::Read(const File& file, int64* bytesRead)
	{
		int64 size = SizeOf(file);
		*bytesRead = size;
		return Read(file, size);
	}

	String FileSystem::ReadText(const File& file)
	{
		int64 size = SizeOf(file);
		String result(size, 0);
		Read(file, size, &result[0]);
		result.erase(std::remove(result.begin(), result.end(), '/r'), result.end());
		return result;
	}

	void FileSystem::ReadText(const File& file, String* outText)
	{
		*outText = ReadText(file);
	}

	void FileSystem::Write(const File& file, int64 numBytes, byte* buffer)
	{
		DWORD written;
		bool result = ::WriteFile(file.GetHandle(), buffer, numBytes, &written, nullptr);
	}

	void FileSystem::Write(const File& file, byte* buffer)
	{
		Write(file, SizeOf(file), buffer);
	}

	void FileSystem::WriteText(const File& file, const String& text)
	{
		Write(file, text.length(), (byte*)&text[0]);
	}

	void FileSystem::Copy(const File& srcFile, const File& dstFile)
	{
	
	}

	void FileSystem::Copy(const File& srcFile, const String& dstPath)
	{
	
	}

	Handle FileSystem::OpenFileForReading(const String& filename)
	{
		return CreateFile(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, nullptr);
	}

	Handle FileSystem::OpenFileForAppending(const String& filename)
	{
		if (FileExists(filename))
		{
			return CreateFile(filename.c_str(), FILE_APPEND_DATA, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		}
		else
		{
			return CreateFile(filename.c_str(), FILE_APPEND_DATA, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		}
		return nullptr;
	}

	Handle FileSystem::OpenFileForOverride(const String& filename)
	{
		if (FileExists(filename))
		{
			return CreateFile(filename.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		}
		else
		{
			return CreateFile(filename.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		}
		return nullptr;
	}

	Handle FileSystem::OpenInternal(const String& filename, OpenMode mode)
	{
		switch (mode)
		{
		case OpenMode::Read:
			return OpenFileForReading(filename);
		case OpenMode::WriteAppend:
			return OpenFileForAppending(filename);
		case OpenMode::WriteOverride:
			return OpenFileForOverride(filename);
		}
	}

	bool FileSystem::CloseInternal(Handle handle)
	{
		return CloseHandle(handle);
	}

	bool FileSystem::DeleteInternal(const String& filename)
	{
		return DeleteFile(filename.c_str());
	}

}