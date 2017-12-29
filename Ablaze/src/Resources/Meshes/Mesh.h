#pragma once
#include "Common.h"
#include "Materials\__Materials__.h"
#include "SubModel.h"
#include "Model.h"

namespace Ablaze
{

	class AB_API Mesh : public Asset
	{
	private:
		Model* m_Model;
		Material* m_DefaultMaterial;

	public:
		Mesh(Model* model, Material* defaultMaterial);
		~Mesh() override;

		void Reload() override;

		Model* GetModel() const;
		Material* GetDefaultMaterial() const;

		void SetModel(Model* model);
		void SetDefaultMaterial(Material* material);

		String ToString() const override;

	public:
		static Mesh* Rectangle(float width, float height, Material* material);
		static Mesh* Ellipse(float width, float height, Material* material);
		static Mesh* Cuboid(float width, float height, float depth, Material* material);
		static Mesh* Sphere(float radius, Material* material);
		static Mesh* Grid(float width, float depth, int xVerts, int zVerts, Material* material);

	};

}