#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <android/log.h>

class Logger
{
public:
	//Output the string to the appropriate log file on the platform
	static void Log(char* string, ...);
};
