#pragma once
#include "Common.h"
#include "Resources\Meshes\Materials\__Materials__.h"
#include "Resources\Meshes\Model.h"
#include "Resources\Resource.h"
#include "Component.h"

namespace Ablaze
{

	struct AB_API ModelSet
	{
	public:
		Resource<Model> model;
		Material material;
		Maths::Mat4 transform;

	};

	class AB_API Mesh : public Component
	{
	private:
		std::vector<ModelSet> m_Models;

	public:
		Mesh();
		Mesh(const Resource<Model>& model, const Material& material, const Maths::Mat4& transform = Maths::Mat4::Identity());

		const Resource<Model>& GetModel(int index) const;
		Resource<Model>& GetModel(int index);
		const Material& GetMaterial(int index) const;
		Material& GetMaterial(int index);
		const Maths::Mat4& GetTransform(int index) const;
		Maths::Mat4& GetTransform(int index);
		const ModelSet& GetModelSet(int index) const;
		int ModelCount() const;

		const std::vector<ModelSet>& GetModelSets() const;

		void AddModel(const Resource<Model>& model, const Material& material, const Maths::Mat4& transform = Maths::Mat4::Identity());

		String ToString() const override;
		Component* Clone() const override;

	};

}