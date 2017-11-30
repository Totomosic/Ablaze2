#pragma once
#include "Systems.h"
#include "Resources\__Resources__.h"

namespace Ablaze
{
	
	class AB_API LightSystem : public System
	{
	private:
		std::vector<std::shared_ptr<Shader>> m_Shaders;

	public:
		void AddShader(const std::shared_ptr<Shader>& shader);
		void Execute() override;

	};

}