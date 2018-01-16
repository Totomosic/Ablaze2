#pragma once
#include "Utils\structs\__structs__.h"

namespace Ablaze
{

	class AB_API XMLnode : public Object
	{
	private:
		String m_Name;
		std::unordered_map<String, String> m_Attributes;
		String m_Data;
		std::vector<XMLnode*> m_Children;
		XMLnode* m_Parent;

	public:
		XMLnode();
		~XMLnode();

		const String& Name() const;
		const std::unordered_map<String, String>& Attributes() const;
		const String& GetAttribute(const String& name) const;
		String& GetAttribute(const String& name);
		const String& Data() const;
		const std::vector<XMLnode*>& Children() const;
		int ChildCount() const;
		XMLnode* Parent() const;

		const XMLnode& GetChild(const String& name, int index = 0) const;
		XMLnode& GetChild(const String& name, int index = 0);
		const XMLnode& GetChild(int index) const;
		XMLnode& GetChild(int index);
		const XMLnode& operator[](int index) const;
		XMLnode& operator[](int index);
		const XMLnode& operator[](const String& name) const;
		XMLnode& operator[](const String& name);

		bool HasChild(const String& name) const;
		bool HasAttribute(const String& name) const;

		void AddChild(XMLnode* child);
		void SetData(const String& data);
		void SetName(const String& name);
		void SetParent(XMLnode* parent);
		void AddAttribute(const String& attributeName, const String& attributeValue);

		String ToString() const override;

	};

}