#pragma once
#include "Common.h"
#include "Resources\Meshes\Materials\__Materials__.h"
#include "Resources\Meshes\Model.h"
#include "Component.h"

namespace Ablaze
{

	struct AB_API ModelSet
	{
	public:
		std::shared_ptr<Model> model;
		std::shared_ptr<MaterialBase> material;
		Maths::Matrix4d transform;

	};

	class AB_API Mesh : public Component
	{
	private:
		std::vector<ModelSet> m_Models;

	public:
		Mesh();
		Mesh(const std::shared_ptr<Model>& model, const std::shared_ptr<MaterialBase>& material, const Maths::Matrix4d& transform = Maths::Matrix4d::Identity());
		Mesh(const Mesh& other) = delete;
		~Mesh();

		const std::shared_ptr<Model>& GetModel(int index) const;
		std::shared_ptr<Model>& GetModel(int index);
		const std::shared_ptr<MaterialBase>& GetMaterial(int index) const;
		std::shared_ptr<MaterialBase>& GetMaterial(int index);
		const Maths::Matrix4d& GetTransform(int index) const;
		Maths::Matrix4d& GetTransform(int index);
		const ModelSet& GetModelSet(int index) const;
		ModelSet& GetModelSet(int index);
		int ModelCount() const;

		void AddModel(const std::shared_ptr<Model>& model, const std::shared_ptr<MaterialBase>& material, const Maths::Matrix4d& transform = Maths::Matrix4d::Identity());
		void SetMaterial(int index, const std::shared_ptr<MaterialBase>& material);

		String ToString() const override;
		Component* Clone() const override;
		void Serialize(JSONwriter& writer) const override;

	};

}