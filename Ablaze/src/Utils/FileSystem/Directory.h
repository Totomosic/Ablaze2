#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"
#include "Logging.h"
#include "Directorypath.h"
#include "File.h"

namespace Ablaze
{

	class AB_API Directory : public Object
	{
	private:
		DirectoryPath m_Path;

	public:
		Directory(const DirectoryPath& path);

		Directory Parent() const;
		int FileCount() const;
		int DirectoryCount() const;
		int ItemCount() const;
		bool IsEmpty() const;

		bool HasDirectory(const String& name) const;
		bool HasFile(const String& name) const;

		Directory CreateDirectory(const String& name) const;
		File CreateFile(const String& name) const;

		std::vector<Directory> ListDirectories() const;
		std::vector<File> ListFiles() const;
		Directory GetDirectory(const String& name) const;
		File GetFile(const String& name) const;

		Directory operator[](const String& name) const;

		String ToString() const override;

	};

}