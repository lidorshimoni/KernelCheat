#include "cheat.hpp"

int main()
{
	LOG("Loading necessary modules...\n");
	LoadLibraryA("user32.dll");
	LoadLibraryA("win32u.dll");
	if (GetModuleHandleA("win32u.dll"))
	{
		LOG("Modules loaded\n");
		cheat::run();
	}
	else
	{
		LOG("Modules failed to load, quitting\n");
	}

	return 0;
}