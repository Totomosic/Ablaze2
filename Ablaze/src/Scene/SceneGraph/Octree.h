#pragma once
#include "Common.h"
#include "SceneGraph.h"
#include "OctreeNode.h"

namespace Ablaze
{

	class AB_API Octree : public SceneGraph
	{
	private:
		OctreeNode* m_Root;
		int m_MaxObjectsPerNode;

	public:
		Octree();
		~Octree();

		OctreeNode* Root() const;

	};

}