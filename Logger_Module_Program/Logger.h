#pragma once

#include <stdio.h>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iostream>

// using namespace std;



enum LogPriority
{
	InfoPriority, DebugPriority, ErrorPriority, WarnPriority, CriticalPriority
};

// void sleepThread()
// {
//     this_thread::sleep_for(chrono::seconds(1));
// }

class Logger
{
private:
	static LogPriority priority;
	static std::mutex log_mutex;
	static const char* filepath;
	static FILE* file;

public:
	static void SetPriority(LogPriority new_priority)
	{
		priority = new_priority;
	}

	static void EnableFileOutput()
	{
		filepath = "log.txt";
		enable_file_output();
	}

	static void EnableFileOutput(const char* new_filepath)
	{
		filepath = new_filepath;
		enable_file_output();
	}

	static void CloseFileOutput()
	{
		free_file();
	}

	template<typename... Args>
	static void Trace(const char* message, Args... args)
	{
		log("[Trace] ", ErrorPriority, message, args...);
	}

	template<typename... Args>
	static void Debug(const char* message, Args... args)
	{
		log("[Debug] ", DebugPriority, message, args...);
		//log("[Error]\t", ErrorPriority, message, args...);
	}

	template<typename... Args>
	static void Info(const char* message, Args... args)
	{
		log("[Info] ", InfoPriority, message, args...);
		//log("[Debug]\t", DebugPriority, message, args...);
		//log("[Error]\t", ErrorPriority, message, args...);	
    }

	template<typename... Args>
	static void Warn(const char* message, Args... args)
	{
		log("[Warn] ", WarnPriority, message, args...);
	}

	template<typename... Args>
	static void Error(const char* message, Args... args)
	{
		log("[Error] ", ErrorPriority, message, args...);
	}

	template<typename... Args>
	static void Critical(const char* message, Args... args)
	{
		log("[Critical] ", CriticalPriority, message, args...);
	}

private:
	template<typename... Args>
	static void log(const char* message_priority_str, LogPriority message_priority, const char* message, Args... args)
	{
		if (priority <= message_priority)
		{	
			// thread thread1(sleepThread); 
    		// thread::id t1_id = thread1.get_id();


			std::time_t current_time = std::time(0);
			std::tm* timestamp = std::localtime(&current_time);
			char buffer[80];
			strftime(buffer, 80, "%c", timestamp);

			
			printf("%s ", buffer);
			printf(message_priority_str);
			// printf(t1_id);
			// thread1.join();
			//printf(message, args...);
			//printf("\n");

			if (file)
			{
				//int size;
				//file.seekg(0, ios::end);
				//int flie_size = file.tellg();
				fprintf(file, "%s ", buffer);
				fprintf(file, message_priority_str);
				fprintf(file, message, args...);
				fprintf(file, "\n");
				//fprintf(file, "Current Size: %d", flie_size);
				//file.seekp(size);
			}
		}
	}

	static void enable_file_output()
	{
		if (file != 0)
		{
			fclose(file);
		}

		file = fopen(filepath, "a");

		if (file == 0)
		{
			printf("Logger: Failed to open file at %s", filepath);
		}
	}

	static void free_file()
	{
		fclose(file);
		file = 0;
	}
};

LogPriority Logger::priority = InfoPriority;
std::mutex Logger::log_mutex;
const char* Logger::filepath = 0;
FILE* Logger::file = 0;