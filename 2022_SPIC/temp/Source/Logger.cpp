#include <windows.h>
#include <stdio.h>

#include "Logger.h"

// ƒƒOo—Í
void Logger::Print(const char* format, ...)
{
	char message[1024];
	va_list args;
	va_start(args, format);
	vsnprintf(message, sizeof(message), format, args);
	va_end(args);
	
	char log_message[128] = "LOG:";
	//SJIS
	::OutputDebugStringA(message);
	
	//UNICODE
	//::OutputDebugStringW(L"a");
	//•¶š‚É‚æ‚Á‚Ä©“®“I‚É”»•Ê‚·‚é
	//::OutputDebugString(L"a");
}
