#pragma once
#include "Common.h"
#include "ModelInfo.h"
#include "Graphics\Buffers\__Buffers__.h"
#include "Materials\__Materials__.h"

namespace Ablaze
{

	class Mesh;

	class AB_API SubModel : public Object
	{
	private:
		IndexBuffer* m_IndexBuffer; // Vertex array of Mesh will own this IndexBuffer
		Material* m_Material;

	public:
		SubModel(IndexBuffer* indexBuffer, Material* material = nullptr);
		SubModel(const SubModel& other) = delete;
		SubModel(const SubModel&& other) = delete;
		SubModel& operator=(const SubModel& other) = delete;
		~SubModel();

	public:
		IndexBuffer* GetIndexBuffer() const;
		Material* GetMaterial() const;
		bool HasOwnMaterial() const;

		void SetMaterial(Material* material);

		String ToString() const override;

	};

}