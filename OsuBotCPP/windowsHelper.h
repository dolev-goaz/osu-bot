#pragma once
#ifndef INCLUDE_WINDOWS
#define INCLUDE_WINDOWS
#include <windows.h>
#endif

#include <psapi.h>
#include "stringHelper.h"

struct _callbackData
{
	const char* str;
	HWND windowHandle;
};

namespace winUtil {
	HWND getWindowHandleByPrefix(const char* nameHint);
	wstring getWindowTitle(const HWND handle);
	DWORD getProcessId(HWND handle);
	wstring getExecutablePath(HWND handle);
	void mouseClick();
	void mouseHold();
	void mouseRelease();
	void waitForKeyPress(unsigned int keyCode);
}