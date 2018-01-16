#include "XMLnode.h"

namespace Ablaze
{

	XMLnode::XMLnode() : Object()
	{

	}

	XMLnode::~XMLnode()
	{
		for (XMLnode* child : m_Children)
		{
			delete child;
		}
	}

	const String& XMLnode::Name() const
	{
		return m_Name;
	}

	const std::unordered_map<String, String>& XMLnode::Attributes() const
	{
		return m_Attributes;
	}

	const String& XMLnode::GetAttribute(const String& name) const
	{
		AB_ASSERT(HasAttribute(name), "No attribute with name " + name + " exists");
		return m_Attributes.at(name);
	}

	String& XMLnode::GetAttribute(const String& name)
	{
		AB_ASSERT(HasAttribute(name), "No attribute with name " + name + " exists");
		return m_Attributes.at(name);
	}

	const String& XMLnode::Data() const
	{
		return m_Data;
	}

	const std::vector<XMLnode*>& XMLnode::Children() const
	{
		return m_Children;
	}

	int XMLnode::ChildCount() const
	{
		return m_Children.size();
	}

	XMLnode* XMLnode::Parent() const
	{
		return m_Parent;
	}

	const XMLnode& XMLnode::GetChild(const String& name, int index) const
	{
		std::vector<XMLnode*> selected;
		for (XMLnode* child : m_Children)
		{
			if (child->Name() == name)
			{
				selected.push_back(child);
			}
		}
		AB_ASSERT(index < selected.size(), "Node with name " + Name() + " has no child with name " + name + " at index " + std::to_string(index));
		return *selected[index];
	}

	XMLnode& XMLnode::GetChild(const String& name, int index)
	{
		std::vector<XMLnode*> selected;
		for (XMLnode* child : m_Children)
		{
			if (child->Name() == name)
			{
				selected.push_back(child);
			}
		}
		AB_ASSERT(index < selected.size(), "Node with name " + Name() + " has no child with name " + name + " at index " + std::to_string(index));
		return *selected[index];
	}

	const XMLnode& XMLnode::GetChild(int index) const
	{
		AB_ASSERT(index < m_Children.size(), "Index out of range");
		return *m_Children[index];
	}

	XMLnode& XMLnode::GetChild(int index)
	{
		AB_ASSERT(index < m_Children.size(), "Index out of range");
		return *m_Children[index];
	}

	const XMLnode& XMLnode::operator[](int index) const
	{
		return GetChild(index);
	}

	XMLnode& XMLnode::operator[](int index)
	{
		return GetChild(index);
	}

	const XMLnode& XMLnode::operator[](const String& name) const
	{
		return GetChild(name);
	}

	XMLnode& XMLnode::operator[](const String& name)
	{
		return GetChild(name);
	}

	bool XMLnode::HasChild(const String& name) const
	{
		for (XMLnode* child : m_Children)
		{
			if (child->Name() == name)
			{
				return true;
			}
		}
		return false;
	}

	bool XMLnode::HasAttribute(const String& name) const
	{
		return m_Attributes.find(name) != m_Attributes.end();
	}

	void XMLnode::AddChild(XMLnode* child)
	{
		m_Children.push_back(child);
	}

	void XMLnode::SetName(const String& name)
	{
		m_Name = name;
	}

	void XMLnode::SetData(const String& data)
	{
		m_Data = data;
	}

	void XMLnode::SetParent(XMLnode* parent)
	{
		m_Parent = parent;
	}

	void XMLnode::AddAttribute(const String& attributeName, const String& attributeValue)
	{
		m_Attributes[attributeName] = attributeValue;
	}

	String XMLnode::ToString() const
	{
		return "XMLnode";
	}

}