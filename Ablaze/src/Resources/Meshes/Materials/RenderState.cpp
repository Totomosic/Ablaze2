#include "RenderState.h"

namespace Ablaze
{

	RenderState::RenderState(bool useDepthFunction, bool useBlend, DepthFunction depthFunction, BlendSrc blendSrcFunction, BlendDst blendDstFunction)
		: useDepthTest(useDepthFunction), useBlend(useBlend), depthFunction(depthFunction), blendSrcFunction(blendSrcFunction), blendDstFunction(blendDstFunction)
	{
	
	}

	void RenderState::Apply() const
	{
		Graphics::SetDepth(useDepthTest);
		Graphics::SetBlend(useBlend);
		Graphics::SetDepthFunction(depthFunction);
		Graphics::SetBlendSrcFunction(blendSrcFunction);
		Graphics::SetBlendDstFunction(blendDstFunction);
	}

	void RenderState::operator()() const
	{
		Apply();
	}

}