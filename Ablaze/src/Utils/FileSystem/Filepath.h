#pragma once
#include "DirectoryPath.h"

namespace Ablaze
{

	class AB_API Filepath : public Object
	{
	private:
		String m_Path;
		DirectoryPath m_Directory;

	public:
		Filepath();
		Filepath(const String& path);
		Filepath(const char* path);

		const String& Path() const;
		bool Exists() const;
		const DirectoryPath& Directory() const;
		String Filename() const;
		String Extension() const;

		String ToString() const override;

	private:
		String ParseFile(const String& path);

	};

}