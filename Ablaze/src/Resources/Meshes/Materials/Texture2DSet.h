#pragma once
#include "Common.h"
#include "Resources\Textures\__Textures__.h"
#include "Resources\Shaders\__Shaders__.h"

namespace Ablaze
{

	template<typename> class Resource;

	class AB_API Texture2DSet : public Object
	{
	private:
		std::vector<Resource<Texture2D>> m_Textures; // std::vector<std::pair<String, Resource<Texture2D>>> said that pair constructor with Resource<Texture2D> was deleted function
		std::unordered_map<int, String> m_Lookup;

	public:
		Texture2DSet();
		Texture2DSet(const String& samplerName, const Resource<Texture2D>& texture);

		const String& GetSampler(int index) const;
		const Resource<Texture2D>& GetTexture(int index) const;
		int GetTextureCount() const;

		void AddTexture(const String& samplerName, const Resource<Texture2D>& texture);
		void RemoveTexture(int index);
		void Clear();

		void BindAll(const Resource<Shader>& shader) const;

		String ToString() const override;

	};

}