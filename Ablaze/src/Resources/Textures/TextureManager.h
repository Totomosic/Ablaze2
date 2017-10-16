#pragma once
#include "Texture2D.h"

namespace Ablaze
{

	class AB_API TextureManager : public Object
	{
	public:
		static TextureManager& Instance();

	private:
		int m_MaxBindPorts;
		const Texture** m_TextureArray;

	private:
		TextureManager();

	public:
		void Bind(const Texture* const texture);
		void Unbind(const Texture* const texture);

		String ToString() const override;

	private:
		void BindNewTexture(const Texture* const texture);
		void Initialise();
		int GetNextAvailableUnit();

	};

}