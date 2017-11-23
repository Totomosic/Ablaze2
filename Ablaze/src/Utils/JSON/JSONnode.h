#pragma once
#include "JSONvalue.h"

namespace Ablaze
{

	class AB_API JSONnode : public Object
	{
	private:
		JSONvalue m_Value;
		JSONnode* m_Parent;
		std::vector<JSONnode*> m_Children;

	public:
		JSONnode();
		JSONnode(const JSONvalue& value);
		~JSONnode();

		const JSONvalue& Value() const;
		JSONvalue& Value();
		const std::vector<JSONnode*>& Children() const;
		std::vector<JSONnode*>& Children();
		int ChildCount() const;
		bool HasChildren() const;
		JSONnode* Parent() const;

		const String& Key() const;
		String& Key();
		const String& Data() const;
		String& Data();

		void AddChild(JSONnode* child);
		void SetParent(JSONnode* parent);
		bool HasChild(const String& key) const;
		const JSONnode& GetChild(const String& key) const;
		JSONnode& GetChild(const String& key);

		const JSONnode& operator[](const String& key) const;
		JSONnode& operator[](const String& key);
		const JSONnode& operator[](int index) const;
		JSONnode& operator[](int index);

		String ToString() const override;

	};

}