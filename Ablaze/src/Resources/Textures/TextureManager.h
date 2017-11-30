#pragma once
#include "Texture2D.h"

namespace Ablaze
{

	class AB_API TextureManager : public Singleton<TextureManager>
	{
	private:
		int m_MaxBindPorts;
		const Texture** m_TextureArray;

	private:
		TextureManager();

	public:
		void Bind(const Texture* const texture);
		void Unbind(const Texture* const texture);

		friend class Texture;
		template<typename> friend class Singleton;

	private:
		void BindNewTexture(const Texture* const texture);
		void Initialise();
		int GetNextAvailableUnit();

		void Delete(int bindport);

	};

}