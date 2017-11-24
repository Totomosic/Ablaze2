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

	RenderState RenderState::Deserialize(JSONnode& node)
	{
		RenderState r;
		if (node["DepthTest"].Data() == "true")
		{
			r.useDepthTest = true;
		}
		else
		{
			r.useDepthTest = false;
		}
		if (node["Blend"].Data() == "true")
		{
			r.useBlend = true;
		}
		else
		{
			r.useBlend = false;
		}
		r.depthFunction = (DepthFunction)stoi(node["DepthFunction"].Data());
		r.blendSrcFunction = (BlendSrc)stoi(node["BlendSrcFunction"].Data());
		r.blendDstFunction = (BlendDst)stoi(node["BlendDstFunction"].Data());
		return r;
	}

}