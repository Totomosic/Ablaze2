#pragma once
#include "Common.h"

/*
	- MODEL SYSTEM (MeshRenderer component, Mesh, Model, IndexBuffer)
	- SHADERS (#include)
*/

namespace Ablaze
{

	class AB_API Asset : public Object
	{
	protected:
		int m_RefCount;

	public:
		Asset();
		Asset(const Asset& other) = delete;
		Asset(const Asset&& other) = delete;
		Asset& operator=(const Asset& other) = delete;
		virtual ~Asset();

		int GetRefCount() const;
		void Increment();
		void Decrement(bool deleteIfZero = true);

		virtual void Reload() = 0;
		virtual void Serialize(JSONwriter& writer) const;

		friend class ResourceManager;

	};

}