#pragma once
#include "Common.h"
#include "Scene\GameObject.h"
#include "Scene\ComponentSet.h"

namespace Ablaze
{

	class AB_API Component : public Object
	{
	private:
		static std::unordered_map<String, Component*> m_RegisteredComponents;

	protected:
		GameObject* m_GameObject;
		bool m_Enabled;

	public:
		Component();
		virtual ~Component();

		GameObject* Owner() const;
		const bool Enabled() const;
		bool& Enabled();

		void Enable();
		void Disable();

		virtual void Start();
		virtual void Update(double elapsedSeconds);

		virtual Component* Clone() const = 0;
		virtual void Serialize(JSONwriter& writer) const;
		virtual Component* Deserialize(JSONnode& node) const;

		friend class ComponentSet;

	public:
		template<typename T>
		static void Register()
		{
			m_RegisteredComponents[CleanJSONString(typeid(T).name())] = new T;
		}

	};

}