#include "Includes\global.h"

// better than using entire namespace.

using std::cout;
using std::endl;
using std::cin;

// Define ClickThread above, so we can call it in Main()

DWORD WINAPI ClickThread(LPVOID lParam);

int main()
{

	// Initialize Hook and create thread to intercept mouse and keyboard events.

	if (!initHook()) {
		cout << "Hook Initialization Failed..." << endl;
		cin.get();
		exit(1);
	}

	cout << "\n  Minimum CPS: ";
	cin >> minCps;
	cout << "  Maximum CPS: ";
	cin >> maxCps;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)& ClickThread, NULL, 0, 0);

	// I wouldn't actually do this as its pretty redundant when we have a working keyboard hook, I
	// was messing around with keyloggers around the time making this so, this can be utilized in other ways as well.

	while (true) {

		std::this_thread::sleep_for(std::chrono::milliseconds(550));

		if (GetKeyString(currentkey) == "P") {
			toggled = !toggled;
			if (!toggled) {
				cout << "\n\r  Clicker Toggled [OFF]" << endl;
			}
			else {
				cout << "\n\r  Clicker Toggled [ON]" << endl;
			}
		}

		//reset currentkey

		currentkey = 0x00;

	}

}

DWORD WINAPI ClickThread(LPVOID lParam) {

	int maxDelay = 1000 / (minCps + maxCps * 0.2);
	int minDelay = 1000 / (minCps + maxCps * 0.48);

	while (true) {

		std::this_thread::sleep_for(std::chrono::milliseconds(random(minDelay, maxDelay)));

		if (mousedown == 1 && toggled) {

			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, NULL, NULL);
			std::this_thread::sleep_for(std::chrono::milliseconds(random(7, 12)));
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, NULL, NULL);

		}

	}

	return 0;

}
