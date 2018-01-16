#pragma once
#include "XMLnode.h"

namespace Ablaze
{

	class Filepath;

	XMLnode* LoadXMLFile(const Filepath& file);
	XMLnode* LoadXMLSource(const String& src);

}