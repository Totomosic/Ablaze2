#include "RenderState.h"
#include "Graphics\Rendering\Graphics.h"

namespace Ablaze
{

	RenderState::RenderState(bool useDepthFunction, bool useBlend, DepthFunction depthFunction, BlendSrc blendSrcFunction, BlendDst blendDstFunction)
		: UseDepthTest(useDepthFunction), UseBlend(useBlend), DepthFunc(depthFunction), BlendSrcFunc(blendSrcFunction), BlendDstFunc(blendDstFunction)
	{
	
	}

	void RenderState::Apply() const
	{
		Graphics::SetDepth(UseDepthTest);
		Graphics::SetBlend(UseBlend);
		Graphics::SetDepthFunction(DepthFunc);
		Graphics::SetBlendSrcFunction(BlendSrcFunc);
		Graphics::SetBlendDstFunction(BlendDstFunc);
	}

	void RenderState::operator()() const
	{
		Apply();
	}

	void RenderState::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("DepthTest", UseDepthTest);
		writer.WriteAttribute("Blend", UseBlend);
		writer.WriteAttribute("DepthFunction", (int)DepthFunc);
		writer.WriteAttribute("BlendSrcFunction", (int)BlendSrcFunc);
		writer.WriteAttribute("BlendDstFunction", (int)BlendDstFunc);
		writer.EndObject();
	}

}