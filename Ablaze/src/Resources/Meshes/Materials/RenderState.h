#pragma once
#include "Common.h"
#include "Graphics\Rendering\Graphics.h"

namespace Ablaze
{

	struct AB_API RenderState
	{
	public:
		bool useDepthTest;
		bool useBlend;
		DepthFunction depthFunction;
		BlendSrc blendSrcFunction;
		BlendDst blendDstFunction;

	public:
		RenderState(bool useDepthTest = true, bool useBlend = true, DepthFunction depthFunction = DepthFunction::Less, BlendSrc blendSrcFunction = BlendSrc::SrcAlpha, BlendDst blendDstFunction = BlendDst::OneMinusSrcAlpha);

		void Apply() const;
		void operator()() const;

		void Serialize(JSONwriter& writer) const;

	};

}