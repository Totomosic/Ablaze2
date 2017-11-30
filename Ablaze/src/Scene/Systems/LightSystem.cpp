#include "LightSystem.h"

namespace Ablaze
{

	void LightSystem::AddShader(const std::shared_ptr<Shader>& shader)
	{
		m_Shaders.push_back(shader);
	}

	void LightSystem::Execute()
	{
		std::vector<GameObject*> lights = GameObject::GetAllWith<Transform, Light>();
		int lightCount = lights.size();
		for (std::shared_ptr<Shader>& shader : m_Shaders)
		{
			shader->Bind();
			shader->SetUniform("UsedLights", lightCount);
			int index = 0;
			for (GameObject* light : lights)
			{
				Light& lightComp = light->GetComponent<Light>();
				Transform& transform = light->transform();
				shader->SetUniform("Lights[" + std::to_string(index) + "].Position", transform.Position());
				shader->SetUniform("Lights[" + std::to_string(index) + "].Color", lightComp.LightColor());
				shader->SetUniform("Lights[" + std::to_string(index) + "].Ambient", lightComp.Ambient());
				index++;
			}
			shader->Unbind();
		}
	}

}