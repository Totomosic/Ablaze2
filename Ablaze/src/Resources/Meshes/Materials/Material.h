#pragma once
#include "Common.h"
#include "Resources\Asset.h"
#include "RenderState.h"
#include "Texture2DSet.h"

namespace Ablaze
{

	template<typename> class Resource;

	class AB_API Material : public Asset
	{
	private:
		Color m_BaseColor;
		RenderState m_RenderState;
		Texture2DSet m_Textures;

	public:
		Material(const String& filename); // TODO: Create custom Material file
		Material(const Color& baseColor, const RenderState& renderState, const Texture2DSet& textures);
		Material(const Color& baseColor, const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const Color& baseColor, const RenderState& renderState);
		Material(const Color& baseColor, const Texture2DSet& textures);
		Material(const Color& baseColor, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const Color& baseColor);
		Material(const RenderState& renderState, const Texture2DSet& textures);
		Material(const RenderState& renderState, const String& samplerName, const Resource<Texture2D>& texture);
		Material(const RenderState& renderState);
		Material(const Texture2DSet& textures);
		Material(const String& samplerName, const Resource<Texture2D>& texture);
		Material();

		const Color& BaseColor() const;
		Color& BaseColor();
		const RenderState& RenderSettings() const;
		RenderState& RenderSettings();
		const Texture2DSet& Textures() const;
		Texture2DSet& Textures();

		void Reload() override;

		String ToString() const override;

	};

}