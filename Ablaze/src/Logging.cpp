#include "Logging.h"
#include "Utils\FileSystem\__FileSystem__.h"
#include <Windows.h>

namespace Ablaze
{

	void SetupConsole(int level)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		switch (level)
		{
		case (AB_LOG_LEVEL_FATAL):
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);
			break;
		case (AB_LOG_LEVEL_ERROR):
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case (AB_LOG_LEVEL_WARN):
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case (AB_LOG_LEVEL_INFO):
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			break;
		}
	}

	String LevelToString(int level)
	{
		switch (level)
		{
		case AB_LOG_LEVEL_FATAL:
			return "FATAL";
		case AB_LOG_LEVEL_ERROR:
			return "ERROR";
		case AB_LOG_LEVEL_WARN:
			return "WARN";
		case AB_LOG_LEVEL_INFO:
			return "INFO";
		}
	}

	void LogMessage(const String& message, int level)
	{
		SetupConsole(level);
		std::cout << "Ablaze:     " << message << std::endl;
		if (level <= AB_LOG_LEVEL_ERROR) // Only log errors or fatals
		{
			File f = Filesystem::OpenFile(AB_LOG_FILE, OpenFlags::Append);
			f.WriteText("[" + LevelToString(level) + "] " + message + "\n");
			f.Close();
		}
		SetupConsole(AB_LOG_LEVEL_INFO);
	}

	void ClearLogFile()
	{
		File f = Filesystem::OpenFile(AB_LOG_FILE, OpenFlags::Override);
		f.Close();
	}

}