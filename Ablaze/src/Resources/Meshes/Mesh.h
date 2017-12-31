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
		Material m_DefaultMaterial;

	public:
		Mesh(Model* model, const Material& defaultMaterial);
		Mesh(Model* model);
		~Mesh() override;

		void Reload() override;

		Model* GetModel() const;
		const Material& GetMaterial() const;
		Material& GetMaterial();

		void SetModel(Model* model);
		void SetMaterial(const Material& material);

		String ToString() const override;

	public:
		static Mesh* Rectangle(float width, float height, const Material& material);
		static Mesh* Ellipse(float width, float height, const Material& material);
		static Mesh* Cuboid(float width, float height, float depth, const Material& material);
		static Mesh* Sphere(float radius, const Material& material);
		static Mesh* Grid(float width, float depth, int xVerts, int zVerts, const Material& material);

	};

}