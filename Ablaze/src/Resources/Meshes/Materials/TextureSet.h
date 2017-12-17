#pragma once
#include "Common.h"
#include "Resources\Textures\Texture2D.h"
#include "Resources\Shaders\__Shaders__.h"

namespace Ablaze
{

	template<typename T>
	class AB_API TextureSet : public Object
	{
	private:
		std::vector<T*> m_Textures;
		std::unordered_map<int, String> m_Lookup;

	public:
		TextureSet() : Object(),
			m_Textures(), m_Lookup()
		{
			
		}

		TextureSet(const String& sampler, T* texture) : TextureSet()
		{
			AddTexture(sampler, texture);
		}

	public:
		const String& GetSampler(int index) const
		{
			return m_Lookup[index];
		}

		T* GetTexture(int index) const
		{
			return m_Textures[index];
		}

		int TextureCount() const
		{
			return m_Textures.size();
		}

		void AddTexture(const String& sampler, T* texture)
		{
			int index = m_Textures.size();
			m_Textures.push_back(texture);
			m_Lookup[index] = sampler;
		}

		void RemoveTexture(int index)
		{
			m_Textures.erase(m_Textures.begin() + index);
		}

		void BindAll(Shader* shader) const
		{
			for (int i = 0; i < TextureCount(); i++)
			{
				shader->SetTexture(m_Lookup.at(i), m_Textures[i]);
			}
		}

		String ToString() const override
		{
			return "TextureSet";
		}

		void Serialize(JSONwriter& writer) const
		{
			writer.BeginObject();
			writer.BeginArray("Textures");
			int index = 0;
			for (const std::shared_ptr<T>& resource : m_Textures)
			{
				writer.BeginObject();
				writer.WriteAttribute("Sampler", m_Lookup.at(index));
				writer.WriteObject("Texture", resource);
				writer.EndObject();
				index++;
			}
			writer.EndArray();
			writer.EndObject();
		}

	};

}