#pragma once
#include "Types.h"
#include "Object.h"
#include "AblazeGL.h"
#include "Logging.h"
#include "Maths\__Maths__.h"
#include "Utils\structs\__structs__.h"
#include "Utils\Functions.h"

#define BIT(x) (1 << x)
#define METHOD_0(method) std::bind(&method, this)
#define METHOD_1(method) std::bind(&method, this, std::placeholders::_1)
#define METHOD_2(method) std::bind(&method, this, std::placeholders::_1, std::placeholders::_2)
#define METHOD_3(method) std::bind(&method, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define METHOD_4(method) std::bind(&method, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define METHOD_5(method) std::bind(&method, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
#define METHOD_6(method) std::bind(&method, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)