#include "windowsHelper.h"

BOOL CALLBACK _findWinCallback(HWND hwnd, LPARAM lParam)
{
	char winName[512];
	_callbackData* param = (_callbackData*)lParam;

	GetWindowTextA(hwnd, winName, sizeof(winName));
	if (strncmp(winName, param->str, strlen(param->str)) == 0)
	{
		param->windowHandle = hwnd;
		return FALSE;
	}
	return TRUE;
}

namespace winUtil {

	HWND getWindowHandleByPrefix(const char* str)
	{
		_callbackData data =
		{
			str,
			NULL
		};
		EnumWindows(_findWinCallback, (LPARAM)&data);
		return data.windowHandle;
	}

	wstring getWindowTitle(const HWND handle) {
		const int length = GetWindowTextLength(handle) + 1;
		wstring windowTitle = wstring(length, '\0');
		const int copiedLength = GetWindowTextW(handle, &windowTitle[0], length);

		windowTitle.resize(copiedLength);
		return windowTitle;
	}

	DWORD getProcessId(HWND handle)
	{
		DWORD pid;
		GetWindowThreadProcessId(handle, &pid);

		return pid;
	}

	wstring getExecutablePath(HWND handle) {
		const DWORD pid = getProcessId(handle);
		HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
		if (!process) return L"";

		const int maxPathLength = 1024;
		TCHAR filename[maxPathLength];
		K32GetModuleFileNameExW(process, NULL, filename, maxPathLength);
		CloseHandle(process);

		return filename;
	}
	void mouseClick() {
		INPUT Inputs[2] = { 0 };
		Inputs[0].type = INPUT_MOUSE;
		Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		Inputs[1].type = INPUT_MOUSE;
		Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

		SendInput(2, Inputs, sizeof(INPUT));
	}
	void mouseHold() {
		INPUT inputs[1] = { 0 };
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

		SendInput(1, inputs, sizeof(INPUT));
	}
	void mouseRelease() {
		INPUT inputs[1] = { 0 };
		inputs[0].type = INPUT_MOUSE;
		inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;

		SendInput(1, inputs, sizeof(INPUT));
	}
	void waitForKeyPress(unsigned int keyCode) {
		while (true) if (GetAsyncKeyState(keyCode)) return;
	}
}