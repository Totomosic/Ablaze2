#include "MaterialBase.h"
#include "Material.h"

namespace Ablaze
{

	MaterialBase::MaterialBase(const Color& color, const RenderState& renderSettings, const Resource<Shader>& shader) : Object(),
		m_BaseColor(color), m_RenderState(renderSettings), m_Shader(shader), m_Uniforms()
	{
	
	}

	MaterialBase::MaterialBase(const Color& color, const Resource<Shader>& shader, const RenderState& renderSettings) : MaterialBase(color, renderSettings, shader)
	{
	
	}

	const Color& MaterialBase::BaseColor() const
	{
		return m_BaseColor;
	}

	Color& MaterialBase::BaseColor()
	{
		return m_BaseColor;
	}

	const RenderState& MaterialBase::RenderSettings() const
	{
		return m_RenderState;
	}

	RenderState& MaterialBase::RenderSettings()
	{
		return m_RenderState;
	}

	const Resource<Shader>& MaterialBase::ActiveShader() const
	{
		return m_Shader;
	}

	Resource<Shader>& MaterialBase::ActiveShader()
	{
		return m_Shader;
	}

	const UniformManager& MaterialBase::Uniforms() const
	{
		return m_Uniforms;
	}

	UniformManager& MaterialBase::Uniforms()
	{
		return m_Uniforms;
	}

	void MaterialBase::Apply() const
	{
	
	}

	String MaterialBase::ToString() const
	{
		return "MaterialBase";
	}

	void MaterialBase::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteObject("Color", m_BaseColor);
		writer.WriteObject("RenderSettings", m_RenderState);
		writer.WriteObject("Shader", m_Shader);
		writer.EndObject();
	}

}