#pragma once
#include "Common.h"
#include "Resources\Asset.h"
#include "Graphics\Buffers\__Buffers__.h"

namespace Ablaze
{

	class Model : public Asset
	{
	private:
		VertexArray* vertexArray;

	private:
		Model();
		~Model(); // Prevent stack objects and can only be deleted by ResourceManager

	public:

		void Reload() override;

		friend class ResourceManager;


	};

}