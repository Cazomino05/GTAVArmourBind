// GTAVArmourBind.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#define VK_M 0x4D

void SendKey(int iKey, int iFlags )
{
	// get our hardware scan code
	unsigned int uiScanCode = MapVirtualKey((int)iKey, MAPVK_VK_TO_VSC);

	// setup our input structure to send our required key
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = uiScanCode;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;


	ip.ki.wVk = iKey;
	// set the flags (used for arrow keys)
	ip.ki.dwFlags = iFlags;
	// send key down
	SendInput(1, &ip, sizeof(INPUT));

	// wait 5ms
	Sleep(5);

	// send key up
	ip.ki.dwFlags = KEYEVENTF_KEYUP | iFlags;
	SendInput(1, &ip, sizeof(INPUT));

	// wait 5ms
	Sleep(5);
}

int _tmain(int argc, _TCHAR* argv[])
{
	CHAR string[20];
	while (true)
	{
		// Check for F1 press
		if (GetKeyState(VK_F1) & 0x8000)
		{
			// Check target window
			HWND wind = GetForegroundWindow();
			GetWindowTextA(wind, string, 20);
			if (strcmp(string, "Grand Theft Auto V") == 0)
			{
				// Arrow keys require KEYEVENTF_EXTENDEDKEY
				SendKey(VK_M, 0);
				SendKey(VK_DOWN, KEYEVENTF_EXTENDEDKEY);
				SendKey(VK_RETURN, 0);
				SendKey(VK_DOWN, KEYEVENTF_EXTENDEDKEY);
				SendKey(VK_DOWN, KEYEVENTF_EXTENDEDKEY);
				SendKey(VK_RETURN, 0);
				SendKey(VK_UP, KEYEVENTF_EXTENDEDKEY);
				SendKey(VK_UP, KEYEVENTF_EXTENDEDKEY);
				SendKey(VK_UP, KEYEVENTF_EXTENDEDKEY);
				SendKey(VK_RETURN, 0);
				// M key closes interaction menu
				SendKey(VK_M, 0);
			}
			Sleep(2000);
		}
	}
	Sleep(1);

	return 0;
}

