#include "LayerMask.h"

namespace Ablaze
{

	LayerMask::LayerMask()
		: mask(0), all(true)
	{
	
	}

	LayerMask::LayerMask(const String& layerName)
		: all(false)
	{
		Select(layerName);
	}

	LayerMask::LayerMask(const String& l0, const String& l1)
		: all(false)
	{
		Select(l0);
		Select(l1);
	}

	LayerMask::LayerMask(const String& l0, const String& l1, const String& l2)
		: all(false)
	{
		Select(l0);
		Select(l1);
		Select(l2);
	}

	void LayerMask::Select(const String& layerName)
	{
		m_LayerNames.push_back(layerName);
		all = false;
	}

	void LayerMask::Deselect(const String& layerName)
	{
		auto it = std::find(m_LayerNames.begin(), m_LayerNames.end(), layerName);
		if (it != m_LayerNames.end())
		{
			m_LayerNames.erase(it);
		}
	}

	void LayerMask::Clear()
	{
		m_LayerNames.clear();
	}

	void LayerMask::Evaluate(const Scene& scene)
	{
		mask = 0;
		for (String& s : m_LayerNames)
		{
			int layerMask = scene.GetMask(s);
			AddLayer(layerMask);
		}
	}

	void LayerMask::operator()(const Scene& scene)
	{
		Evaluate(scene);
	}

	void LayerMask::AddLayer(int layerMask)
	{
		mask |= layerMask;
	}

}