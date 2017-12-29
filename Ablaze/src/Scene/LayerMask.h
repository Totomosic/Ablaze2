#pragma once
#include "Scene.h"

namespace Ablaze
{

	struct AB_API LayerMask
	{
	private:
		std::vector<String> m_LayerNames;

	public:
		int mask;
		bool all;

	public:
		LayerMask();
		LayerMask(const String& layerName);
		LayerMask(const String& l0, const String& l1);
		LayerMask(const String& l0, const String& l1, const String& l2);

		void Select(const String& layerName);
		void Deselect(const String& layerName);
		void Clear();

		void Evaluate(const Scene& scene);
		void operator()(const Scene& scene);

	private:
		void AddLayer(int layerMask);

	};

}