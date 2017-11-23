#pragma once
#include "JSONnode.h"
#include "JSONvalue.h"

namespace Ablaze
{

	JSONnode* LoadJSONFile(const String& filename);
	JSONnode* LoadJSONSource(String source);

}