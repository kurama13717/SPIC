#include <windows.h>
#include <stdio.h>

#include "Logger.h"

// ログ出力
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
	//文字によって自動的に判別する
	//::OutputDebugString(L"a");
}
