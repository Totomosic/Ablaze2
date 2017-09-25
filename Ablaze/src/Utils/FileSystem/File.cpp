#include "File.h"
#include "FileSystem.h"

namespace Ablaze
{

	File::File(const String& filepath) : Object(),
		m_Path(filepath), m_Handle(nullptr)
	{
	
	}

	File::File(Handle handle) : Object(),
		m_Path(""), m_Handle(handle)
	{

	}

	File::~File()
	{

	}

	const String& File::GetPath() const
	{
		return m_Path;
	}

	Handle File::GetHandle() const
	{
		return m_Handle;
	}

	bool File::IsOpen() const
	{
		return m_Handle != nullptr;
	}

	bool File::IsValid() const
	{
		return IsOpen();
	}

	OpenMode File::GetMode() const
	{
		return m_Mode;
	}

	uint64 File::GetSize() const
	{
		return FileSystem::SizeOf(*this);
	}

	void File::Open(OpenMode mode) const
	{
		if (!IsOpen())
		{
			m_Handle = FileSystem::OpenInternal(m_Path, mode);
			m_Mode = mode;

			if (m_Handle == INVALID_HANDLE_VALUE)
			{
				AB_ERROR("File failed to open: " + m_Path);
				AB_ERROR("Error: " + std::to_string(GetLastError()));
			}
		}
		else
		{
			AB_WARN("File is already open: " + m_Path);
		}
	}

	void File::Close() const
	{
		if (IsOpen())
		{
			if (!FileSystem::CloseInternal(m_Handle))
			{
				AB_ERROR("File failed to close: " + m_Path);
				AB_ERROR("Error: " + std::to_string(GetLastError()));
			}
			m_Handle = nullptr;
		}
	}

	void File::Delete() const
	{
		FileSystem::DeleteInternal(m_Path);
	}

	void File::SetPath(const String& path)
	{
		m_Path = path;
	}

	String File::ToString() const
	{
		return m_Path;
	}

}