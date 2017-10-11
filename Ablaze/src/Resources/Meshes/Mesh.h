#pragma once
#include "Common.h"
#include "Materials\__Materials__.h"
#include "Model.h"
#include "Resources\Resource.h"

namespace Ablaze
{

	class AB_API Mesh : public Object
	{
	private:
		std::vector<Resource<Model>> m_Models;
		std::vector<Material> m_Materials;

	public:
		Mesh();
		Mesh(const Resource<Model>& model, const Material& material);

		const Resource<Model>& GetModel(int index) const;
		Resource<Model>& GetModel(int index);
		const Material& GetMaterial(int index) const;
		Material& GetMaterial(int index);
		std::pair<const Resource<Model>&, const Material&> GetPair(int index) const;
		std::pair<Resource<Model>&, Material&> GetPair(int index);

		const std::vector<Resource<Model>>& GetAllModels() const;
		const std::vector<Material>& GetAllMaterials() const;

		void AddModel(const Resource<Model>& model, const Material& material);

		String ToString() const override;

	};

}