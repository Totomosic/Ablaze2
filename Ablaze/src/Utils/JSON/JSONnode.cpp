#include "JSONnode.h"
#include "Logging.h"

namespace Ablaze
{

	JSONnode::JSONnode() : JSONnode({ "", "" })
	{
	
	}

	JSONnode::JSONnode(const JSONvalue& value) : Object(),
		m_Value(value), m_Parent(nullptr), m_Children()
	{
	
	}

	JSONnode::~JSONnode()
	{
		for (JSONnode* node : m_Children)
		{
			delete node;
		}
	}

	const JSONvalue& JSONnode::Value() const
	{
		return m_Value;
	}

	JSONvalue& JSONnode::Value()
	{
		return m_Value;
	}

	const std::vector<JSONnode*>& JSONnode::Children() const
	{
		return m_Children;
	}

	std::vector<JSONnode*>& JSONnode::Children()
	{
		return m_Children;
	}

	int JSONnode::ChildCount() const
	{
		return m_Children.size();
	}

	bool JSONnode::HasChildren() const
	{
		return ChildCount() != 0;
	}

	JSONnode* JSONnode::Parent() const
	{
		return m_Parent;
	}

	const String& JSONnode::Key() const
	{
		return m_Value.key;
	}

	String& JSONnode::Key()
	{
		return m_Value.key;
	}

	const String& JSONnode::Data() const
	{
		return m_Value.value;
	}

	String& JSONnode::Data()
	{
		return m_Value.value;
	}

	void JSONnode::AddChild(JSONnode* child)
	{
		m_Children.push_back(child);
		child->SetParent(this);
	}

	void JSONnode::SetParent(JSONnode* parent)
	{
		m_Parent = parent;
	}

	bool JSONnode::HasChild(const String& key) const
	{
		for (JSONnode* node : m_Children)
		{
			if (node->Key() == key)
			{
				return true;
			}
		}
		return false;
	}

	const JSONnode& JSONnode::GetChild(const String& key) const
	{
		for (JSONnode* node : m_Children)
		{
			if (node->Key() == key)
			{
				return *node;
			}
		}
		AB_ERROR("Unable to find value with key: " + key);
		return *(JSONnode*)nullptr;
	}

	JSONnode& JSONnode::GetChild(const String& key)
	{
		for (JSONnode* node : m_Children)
		{
			if (node->Key() == key)
			{
				return *node;
			}
		}
		AB_ERROR("Unable to find value with key: " + key);
		return *(JSONnode*)nullptr;
	}

	const JSONnode& JSONnode::operator[](const String& key) const
	{
		return GetChild(key);
	}

	JSONnode& JSONnode::operator[](const String& key)
	{
		return GetChild(key);
	}

	const JSONnode& JSONnode::operator[](int index) const
	{
		return *m_Children[index];
	}

	JSONnode& JSONnode::operator[](int index)
	{
		return *m_Children[index];
	}

	String JSONnode::ToString() const
	{
		return Data();
	}

}