#include "LogManager.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <Windows.h>
#include "psapi.h"
#pragma comment(lib, "user32.lib")

std::string LogManager::mEventLog;
bool LogManager::mEnableLog;

LogManager::LogManager()
{
	this->mEventLog = "";
	this->mEnableLog = true;
}


LogManager::~LogManager()
{
	if (this->mEnableLog) 
	{
		std::time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);
		// generate log name
		std::string filename = "Output-" + 
			std::to_string(now.tm_year + 1900) + "-" 
			+ std::to_string(now.tm_mon + 1) + "-" 
			+ std::to_string(now.tm_mday) + ".log";
		
		std::ofstream outputFile;
		outputFile.open(filename);

		std::ostringstream ostream;

		MEMORYSTATUSEX memInfo;
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);

		//Physical memory
		ostream << memInfo.ullTotalPhys/1024/1024;
		std::string totalPhysMem = ostream.str();

		ostream.str("");
		ostream.clear();

		//Used Memory
		std::stringstream stream;
		PROCESS_MEMORY_COUNTERS_EX pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		stream << pmc.WorkingSetSize/1024/1024;
		std::string physMemUsedByEngine = stream.str();

		float memUsage = 100*
			(pmc.WorkingSetSize / 1024 / 1024)
			/ (memInfo.ullTotalPhys / 1024 / 1024);

		stream.str("");
		stream.clear();

		outputFile << std::to_string(now.tm_year + 1900) + "-" + std::to_string(now.tm_mon + 1) + "-" + std::to_string(now.tm_mday) << "\n";
		outputFile << "Total Memory: " << totalPhysMem << "MB\n";
		outputFile << "Used Memory:	 " << physMemUsedByEngine << "MB\n";
		outputFile << "Memory Usage: " << memUsage << "%\n";
		outputFile << "---------------------------------------------\n";
		outputFile << this->mEventLog << "\n";
		outputFile << "---------------------------------------------\n";
		outputFile << "Hope 2 Log Ended.\n";
		outputFile.close();
	}
}

void LogManager::addLog(ELogType logType, std::string _log)
{
	std::time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);
	mEventLog += "[" + std::to_string(now.tm_hour + 1) + ":"
		+ std::to_string(now.tm_min + 1) + ":"
		+ std::to_string(now.tm_sec + 1) + "]";

	switch (logType)
	{
	case ELogType::E_ERROR:
		mEventLog += "ERROR: ";
		break;
	case ELogType::E_WARNING:
		mEventLog += "WARNING: ";
		break;
	case ELogType::E_EVENT:
		mEventLog += "Log: ";
		break;
	default:
		mEventLog += "Unknown: ";
		break;
	}


	mEventLog += (_log + '\n');
}

void LogManager::errorExit()
{
	if (MessageBox(
		NULL,
		"Some thing went wrong, a log has been generated.",
		"Ooooooooooooooooops error!",
		MB_OK
	) == IDOK)
	{
		if (mEnableLog)
		{
			std::time_t t = time(0);
			struct tm now;
			localtime_s(&now, &t);
			// generate log name
			std::string filename = "Output-" +
				std::to_string(now.tm_year + 1900) + "-"
				+ std::to_string(now.tm_mon + 1) + "-"
				+ std::to_string(now.tm_mday) + ".log";

			std::ofstream outputFile;
			outputFile.open(filename);

			std::ostringstream ostream;

			MEMORYSTATUSEX memInfo;
			memInfo.dwLength = sizeof(MEMORYSTATUSEX);
			GlobalMemoryStatusEx(&memInfo);

			//Physical memory
			ostream << memInfo.ullTotalPhys / 1024 / 1024;
			std::string totalPhysMem = ostream.str();

			ostream.str("");
			ostream.clear();

			//Used Memory
			std::stringstream stream;
			PROCESS_MEMORY_COUNTERS_EX pmc;
			GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
			stream << pmc.WorkingSetSize / 1024 / 1024;
			std::string physMemUsedByEngine = stream.str();

			float memUsage = 100 *
				(pmc.WorkingSetSize / 1024 / 1024)
				/ (memInfo.ullTotalPhys / 1024 / 1024);

			stream.str("");
			stream.clear();

			outputFile << std::to_string(now.tm_year + 1900) + "-" + std::to_string(now.tm_mon + 1) + "-" + std::to_string(now.tm_mday) << "\n";
			outputFile << "Total Memory: " << totalPhysMem << "MB\n";
			outputFile << "Used Memory:	 " << physMemUsedByEngine << "MB\n";
			outputFile << "Memory Usage: " << memUsage << "%\n";
			outputFile << "---------------------------------------------\n";
			outputFile << mEventLog << "\n";
			outputFile << "---------------------------------------------\n";
			outputFile << "Hope 2 Log Ended.\n";
			outputFile.close();
		}
	}



	exit(-1);
}
