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
	std::string mEventLog;
	bool mEnableLog;

public:
	LogManager();
	~LogManager();

	void addLog(ELogType logType, std::string _log);
	void errorExit();
};

#endif