#pragma once
#include "JSONnode.h"
#include "JSONvalue.h"

namespace Ablaze
{

	class Filepath;

	JSONnode* LoadJSONFile(const Filepath& filename);
	JSONnode* LoadJSONSource(const String& src);

}