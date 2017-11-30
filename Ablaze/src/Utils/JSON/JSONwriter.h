#pragma once
#include "JSONloader.h"
#include "Utils\Filesystem\File.h"

namespace Ablaze
{

	class AB_API JSONwriter : public Object
	{
	private:
		File m_File;
		String m_Filename;

	public:
		JSONwriter(const String& jsonFile);
		~JSONwriter();

		const String& Filename() const;

		template<typename T>
		void WriteAttribute(const String& attributeTag, const T& value)
		{
			WriteAttribute(attributeTag);
			m_File << "\"" << value << "\"";
			WriteComma();
		}

		template<>
		void WriteAttribute(const String& attributeTag, const int& value)
		{
			WriteAttribute(attributeTag);
			m_File << value;
			WriteComma();
		}

		template<>
		void WriteAttribute(const String& attributeTag, const float& value)
		{
			WriteAttribute(attributeTag);
			m_File << value;
			WriteComma();
		}

		template<>
		void WriteAttribute(const String& attributeTag, const bool& value)
		{
			WriteAttribute(attributeTag);
			if (value)
			{
				m_File << "true";
			}
			else
			{
				m_File << "false";
			}
			WriteComma();
		}

		template<typename T>
		void WriteElement(const T& value)
		{
			m_File << '\"' << value << '\"';
			WriteComma();
		}

		template<>
		void WriteElement(const int& value)
		{
			m_File << value;
			WriteComma();
		}

		template<>
		void WriteElement(const float& value)
		{
			m_File << value;
			WriteComma();
		}

		template<>
		void WriteElement(const bool& value)
		{
			if (value)
			{
				m_File << "true";
			}
			else
			{
				m_File << "false";
			}
			WriteComma();
		}

		template<typename T>
		void WriteObject(const String& attributeName, const T& object)
		{
			WriteAttribute(attributeName);
			//object.Serialize(*this);
		}

		template<typename T>
		void WriteObject(const T& object)
		{
			//object.Serialize(*this);
		}

		void BeginObject(const String& attributeTag);
		void BeginObject();
		void EndObject();
		void BeginArray(const String& attributeTag);
		void EndArray();

		String ToString() const override;

	private:
		void WriteAttribute(const String& attributeTag);
		void WriteComma();
		void RemoveTrailingComma();

	};

}