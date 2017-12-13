#pragma once
#include "Object.h"

namespace Ablaze
{

	class AB_API Console
	{
	private:

	public:
		Console() = delete;

		static String Readline();

		static void Write(const String& message);
		static void Write(const Object& object);
		static void Writeline(const String& message);
		static void Writeline(const Object& object);

		static void LogWarning(const String& warning);
		static void LogWarning(const String& warning, const String& file, int line);
		static void LogError(const String& error);
		static void LogError(const String& error, const String& file, int line);
		static void LogFatal(const String& fatal);
		static void LogFatal(const String& fatal, const String& file, int line);

	};

}