#include "Kernel.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdline, int iCmdShow)
{
	Kernel* k = new Kernel(&hInstance);
	k->Run();

	return 1;
}