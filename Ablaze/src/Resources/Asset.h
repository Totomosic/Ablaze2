#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API Asset : public Object
	{
	protected:
		String m_Filename;
		bool m_IsFromFile;

	public:
		Asset(const String& filename);
		Asset();
		virtual ~Asset();

		virtual const String& GetFilename() const;
		virtual bool IsFromFile() const;

		virtual void SetFilename(const String& filename);
		virtual void SetIsFromFile(bool isFromFile);

		virtual void Reload() = 0;

	};

}