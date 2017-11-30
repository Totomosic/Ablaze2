#include "RenderState.h"
#include "Graphics\Rendering\Graphics.h"

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

	void RenderState::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("DepthTest", useDepthTest);
		writer.WriteAttribute("Blend", useBlend);
		writer.WriteAttribute("DepthFunction", (int)depthFunction);
		writer.WriteAttribute("BlendSrcFunction", (int)blendSrcFunction);
		writer.WriteAttribute("BlendDstFunction", (int)blendDstFunction);
		writer.EndObject();
	}

}