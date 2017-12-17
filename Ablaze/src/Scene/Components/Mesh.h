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
		Model* model;
		MaterialBase* material;
		Maths::Matrix4d transform;

		bool deleteModel;
		bool deleteMaterial;

	};

	class AB_API Mesh : public Component
	{
	private:
		std::vector<ModelSet> m_Models;

	public:
		Mesh();
		Mesh(Model* model, MaterialBase* material, const Maths::Matrix4d& transform = Maths::Matrix4d::Identity(), bool canDeleteModel = false, bool canDeleteMaterial = false);
		Mesh(const Mesh& other) = delete;
		~Mesh();

		Model* const GetModel(int index) const;
		Model* GetModel(int index);
		MaterialBase* const GetMaterial(int index) const;
		MaterialBase* GetMaterial(int index);
		const Maths::Matrix4d& GetTransform(int index) const;
		Maths::Matrix4d& GetTransform(int index);
		const ModelSet& GetModelSet(int index) const;
		ModelSet& GetModelSet(int index);
		int ModelCount() const;

		void AddModel(Model* model, MaterialBase* material, const Maths::Matrix4d& transform = Maths::Matrix4d::Identity(), bool canDeleteModel = false, bool canDeleteMaterial = false);
		void SetModel(int index, Model* model);
		void SetMaterial(int index, MaterialBase* material);
		void RemoveModel(int index);

		String ToString() const override;
		Component* Clone() const override;
		void Serialize(JSONwriter& writer) const override;

	};

}