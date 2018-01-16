#pragma once
#include "XMLnode.h"
#include "Utils\Filesystem\File.h"

namespace Ablaze
{

	class AB_API XMLwriter : public Object
	{
	private:
		Filepath m_Filepath;
		File m_OpenedFile;

		XMLnode* m_Current;

	public:
		XMLwriter(const Filepath& filepath);
		~XMLwriter();

		const Filepath& Path() const;

		void BeginNode(const String& name);
		void EndNode();

		void AddAttribute(const String& attribName, const String& value);
		void AddAttribute(const String& attribName, float value);
		void AddAttribute(const String& attribName, int value);
		void AddAttribute(const String& attribName, const Object& value);

		void AddData(const String& data);
		void AddData(float data);
		void AddData(int data);
		void AddData(const Object& data);

		String ToString() const override;

	private:
		void WriteNode(XMLnode* node, int depth);
		String AttributesToString(XMLnode* node);

	};

}