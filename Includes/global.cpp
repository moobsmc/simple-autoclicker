#include "global.h"

// Clicker
int minCps = 1;
int maxCps = 1;
bool toggled = false;

// mouse & keyboard
int mousedown = 0;
unsigned int currentkey;

// global hook values
HHOOK mHook;
HHOOK kHook;

// random
int random(int min, int max) //range : [min, max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

// vk key to string, theres a better way to do this lol. But i'm lazy

std::string GetKeyString(int Input) {
	switch (Input) {
		case(0x21): return("PG UP");
		case(0x22): return("PG DOWN");
		case(0x08): return("BACKSPACE");
		case(0x09): return("TAB");
		case(0x0D): return("ENTER");
		case(0x1B): return("ESC");
		case(0x23): return("END");
		case(0x24): return("HOME");
		case(0x2D): return("INSERT");
		case(0x77): return("F8");
		case(0x10): return("SHIFT");
		case(0x11): return("CTRL");
		case(0x12): return("ALT");
		case(0x20): return("SPACE");
		case(0x25): return("LEFT-ARROW");
		case(0x26): return("UP-ARROW");
		case(0x27): return("RIGHT-ARROW");
		case(0x28): return("DOWN-ARROW");
		case(0x30): return("0");
		case(0x31): return("1");
		case(0x32): return("2");
		case(0x33): return("3");
		case(0x34): return("4");
		case(0x35): return("5");
		case(0x36): return("6");
		case(0x37): return("7");
		case(0x38): return("8");
		case(0x39): return("9");
		case(0x41): return("A");
		case(0x42): return("B");
		case(0x43): return("C");
		case(0x44): return("D");
		case(0x45): return("E");
		case(0x46): return("F");
		case(0x47): return("G");
		case(0x48): return("H");
		case(0x49): return("I");
		case(0x4A): return("J");
		case(0X4B): return("K");
		case(0X4C): return("L");
		case(0X4D): return("M");
		case(0X4E): return("N");
		case(0X4F): return("O");
		case(0x50): return("P");
		case(0x51): return("Q");
		case(0x52): return("R");
		case(0x53): return("S");
		case(0x54): return("T");
		case(0x55): return("U");
		case(0x56): return("V");
		case(0x57): return("W");
		case(0x58): return("X");
		case(0x59): return("Y");
		case(0x5A): return("Z");
		default: return("NONE");
	}
}

// partly skidded, don't crucify me please

LRESULT CALLBACK MouseCallBack(int nCode, WPARAM wParam, LPARAM lParam)
{
	PMSLLHOOKSTRUCT pMouse = (PMSLLHOOKSTRUCT)lParam;
	if (NULL != pMouse)
	{
		if (WM_MOUSEMOVE != wParam)
		{

			if (0 == pMouse->flags)
			{
				switch (wParam)
				{

				case WM_LBUTTONDOWN:
					mousedown = 1;
					break;

				case WM_LBUTTONUP:
					mousedown = 0;
					break;

				}
			}
		}
	}
	return CallNextHookEx(mHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardCallBack(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;

	if (WM_KEYUP)
	{
		currentkey = key->vkCode;
	}

	return CallNextHookEx(kHook, nCode, wParam, lParam);

}

DWORD WINAPI HookThread(LPVOID lParam)
{
	mHook = SetWindowsHookEx(WH_MOUSE_LL, &MouseCallBack, NULL, NULL);
	kHook = SetWindowsHookEx(WH_KEYBOARD_LL, &KeyboardCallBack, NULL, NULL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(mHook);
	UnhookWindowsHookEx(kHook);
	return 0;

}

int initHook() {
	if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&HookThread, NULL, 0, 0) == NULL) {
		return NULL;
	}
	else {
		return 1;
	}
}