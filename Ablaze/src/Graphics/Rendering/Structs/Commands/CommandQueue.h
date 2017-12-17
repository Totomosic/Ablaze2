#pragma once
#include "Common.h"

namespace Ablaze
{

	class Renderer;
	class RenderCommand;

	class AB_API CommandQueue : public Object
	{
	private:
		std::deque<RenderCommand*> m_Commands;

	public:
		CommandQueue();
		~CommandQueue();

		void Enqueue(RenderCommand* command);
		void ExecuteNext(Renderer& renderer);
		void ExecuteAll(Renderer& renderer);

		void Clear();

		String ToString() const override;

	};

}