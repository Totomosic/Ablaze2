#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"
#include "Logging.h"

namespace Ablaze
{

	class Filepath;

	class AB_API DirectoryPath : public Object
	{
	private:
		String m_Path;
		String m_ParentPath;

	public:
		DirectoryPath();
		DirectoryPath(const String& path);
		DirectoryPath(const char* path);

		const String& Path() const;
		bool Exists() const;
		bool HasParent() const;
		DirectoryPath Parent() const;

		String ToString() const override;

	private:
		String ParseDirectory(const String& path);

	};

}