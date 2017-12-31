#pragma once
#include "Common.h"
#include "Graphics\Rendering\GraphicsEnums.h"

namespace Ablaze
{

	struct AB_API RenderState
	{
	public:
		bool UseDepthTest;
		bool UseBlend;
		DepthFunction DepthFunc;
		BlendSrc BlendSrcFunc;
		BlendDst BlendDstFunc;

	public:
		RenderState(bool useDepthTest = true, bool useBlend = true, DepthFunction depthFunction = DepthFunction::Less, BlendSrc blendSrcFunction = BlendSrc::SrcAlpha, BlendDst blendDstFunction = BlendDst::OneMinusSrcAlpha);

		void Apply() const;
		void operator()() const;

		bool operator==(const RenderState& other) const;
		bool operator!=(const RenderState& other) const;

		void Serialize(JSONwriter& writer) const;

	};

}