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

		friend DirectoryPath operator+(const DirectoryPath& left, const DirectoryPath& right);
		DirectoryPath& operator+=(const DirectoryPath& other);
		bool operator==(const DirectoryPath& other) const;
		bool operator!=(const DirectoryPath& other) const;

		String ToString() const override;
		friend std::ostream& operator<<(std::ostream& stream, const DirectoryPath& path);

	private:
		String ParseDirectory(const String& path);
		void CleanPath(String& path);

	};

}