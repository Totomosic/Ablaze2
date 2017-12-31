#pragma once
#include "Common.h"
#include "Resources\Textures\Texture2D.h"
#include "Resources\Shaders\__Shaders__.h"

namespace Ablaze
{

	class AB_API TextureSet : public Object
	{
	private:
		std::vector<Texture*> m_Textures;
		std::unordered_map<int, String> m_Lookup;

	public:
		TextureSet();
		TextureSet(const String& sampler, Texture* texture);
		TextureSet(const TextureSet& other);
		TextureSet& operator=(const TextureSet& other);
		~TextureSet();

		const String& GetSampler(int index) const;
		Texture* GetTexture(int index) const;
		int TextureCount() const;

		void AddTexture(const String& sampler, Texture* texture);
		void RemoveTexture(int index);

		void BindAll(Shader* shader) const;

		bool operator==(const TextureSet& other) const;
		bool operator!=(const TextureSet& other) const;

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;

	};

}