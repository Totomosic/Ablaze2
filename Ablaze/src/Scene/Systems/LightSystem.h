#pragma once
#include "Systems.h"
#include "Resources\__Resources__.h"

namespace Ablaze
{
	
	class AB_API LightSystem : public System
	{
	private:
		std::vector<Shader*> m_Shaders;

	public:
		void AddShader(Shader* shader);
		void Execute() override;

	};

}