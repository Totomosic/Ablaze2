#include "SubModel.h"
#include "Utils\FileSystem\__FileSystem__.h"
#include "Shapes.h"
#include "Mesh.h"

namespace Ablaze
{

	SubModel::SubModel(IndexBuffer* indexBuffer, Material* material) : Object(),
		m_IndexBuffer(indexBuffer), m_Material(material)
	{
		if (m_Material != nullptr)
		{
			m_Material->Increment();
		}
	}

	SubModel::~SubModel()
	{
		if (m_Material != nullptr)
		{
			m_Material->Decrement();
		}
	}

	IndexBuffer* SubModel::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	Material* SubModel::GetMaterial() const
	{
		return m_Material;
	}

	bool SubModel::HasOwnMaterial() const
	{
		return m_Material != nullptr;
	}

	void SubModel::SetMaterial(Material* material)
	{
		m_Material->Decrement();
		m_Material = material;
		if (m_Material != nullptr)
		{
			m_Material->Increment();
		}
	}

	String SubModel::ToString() const
	{
		return "SubModel";
	}

}