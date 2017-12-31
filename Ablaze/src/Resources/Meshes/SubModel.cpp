#include "SubModel.h"
#include "Utils\FileSystem\__FileSystem__.h"
#include "Shapes.h"
#include "Mesh.h"

namespace Ablaze
{

	SubModel::SubModel(IndexBuffer* indexBuffer, const Material& material) : Object(),
		m_IndexBuffer(indexBuffer), m_Material(material), m_HasOwnMaterial(true)
	{

	}

	SubModel::SubModel(IndexBuffer* indexBuffer) : SubModel(indexBuffer, Material())
	{
		m_HasOwnMaterial = false;
	}

	SubModel::~SubModel()
	{
	
	}

	IndexBuffer* SubModel::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	const Material& SubModel::GetMaterial() const
	{
		return m_Material;
	}

	Material& SubModel::GetMaterial()
	{
		return m_Material;
	}

	bool SubModel::HasOwnMaterial() const
	{
		return m_HasOwnMaterial;
	}

	void SubModel::SetMaterial(const Material& material)
	{
		m_Material = material;
		m_HasOwnMaterial = true;
	}

	String SubModel::ToString() const
	{
		return "SubModel";
	}

}