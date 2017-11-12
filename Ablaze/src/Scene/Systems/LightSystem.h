#pragma once
#include "Systems.h"
#include "Resources\__Resources__.h"

namespace Ablaze
{
	
	class AB_API LightSystem : public System
	{
	private:
		std::vector<Resource<Shader>> m_Shaders;

	public:
		void AddShader(const Resource<Shader>& shader);
		void Execute() override;

	};

}