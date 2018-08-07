#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H
#include <string>

enum class ELogType
{
	E_ERROR,
	E_WARNING,
	E_EVENT
};

class LogManager
{
private:
	static std::string mEventLog;
	static bool mEnableLog;

public:
	LogManager();
	~LogManager();

	static void addLog(ELogType logType, std::string _log);
	static void errorExit();
};

#endif