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

	class AB_API File : public Object
	{
	private:
		String m_Path;
		mutable Handle m_Handle;
		mutable OpenMode m_Mode;

	public:
		File(const String& filepath);
		File(Handle fileHandle);
		~File();

		const String& GetPath() const;
		Handle GetHandle() const;
		bool IsOpen() const;
		bool IsValid() const;
		OpenMode GetMode() const;
		uint64 GetSize() const;

		void Open(OpenMode mode = OpenMode::Read) const;
		void Close() const;
		void Delete() const;

		void SetPath(const String& path);

		String ToString() const override;

	};

}