#pragma once
#include "Types.h"
#include "Object.h"

namespace Ablaze
{

#define AB_LOG_LEVEL_FATAL 0
#define AB_LOG_LEVEL_ERROR 1
#define AB_LOG_LEVEL_WARN 2
#define AB_LOG_LEVEL_INFO 3
#define AB_LOG_FILE "Ablaze.log"

	void SetupConsole(int level);
	String LevelToString(int level);
	void LogMessage(const String& message, int level);
	void ClearLogFile();

	template<typename T>
	String MessageToString(const T& message)
	{
		std::stringstream s;
		s << message;
		return s.str();
	}

#ifdef AB_DEBUG
#define AB_INFO(msg) LogMessage(MessageToString(msg), AB_LOG_LEVEL_INFO)
#define AB_WARN(msg) LogMessage(MessageToString(msg), AB_LOG_LEVEL_WARN)
#define AB_ERROR(msg) LogMessage(MessageToString(msg), AB_LOG_LEVEL_ERROR)
#define AB_FATAL(msg) LogMessage(MessageToString(msg), AB_LOG_LEVEL_FATAL)

#define AB_ASSERT(x, msg) if (!(x)) { AB_FATAL(msg); __debugbreak(); }
#else
#define AB_INFO(msg)
#define AB_WARN(msg)
#define AB_ERROR(msg)
#define AB_FATAL(msg)

#define AB_ASSERT(x, msg)
#endif

}