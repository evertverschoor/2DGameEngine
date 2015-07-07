#include "Window.h"
#include "Windows.h"
#include "MouseState.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


Window::Window(LPCWSTR _name, HINSTANCE* _hInstance, PcInputReciever* _reciever)
{
	Name = _name;
	hInstance = _hInstance;
	WindowIsUp = false;
	PcReciever = _reciever;
}


Window::~Window()
{
	delete Settings;
	delete Name;
	delete hInstance;
	delete PcReciever;
}


int Window::Launch()
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = *hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"MainWindow";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	if (Settings->Fullscreen)
	{
		Handle = CreateWindowEx(NULL,
			L"MainWindow",
			Name,
			WS_EX_TOPMOST | WS_POPUP,
			0, 0,
			Settings->MonitorRes->Width, Settings->MonitorRes->Height,
			NULL,
			NULL,
			*hInstance,
			NULL);
	}
	else
	{
		Handle = CreateWindow(L"MainWindow", Name, WS_OVERLAPPEDWINDOW, 150, 150, Settings->ScreenRes->Width, Settings->ScreenRes->Height, NULL, NULL, *hInstance, NULL);
	}

	ShowWindow(Handle, 5);
	UpdateWindow(Handle);

	WindowIsUp = true;

	// Enter the message loop to send keyboard and mouse input to the Pc Input Reciever
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			switch (msg.message)
			{
				case WM_KEYDOWN : PcReciever->KeyPressed(msg.wParam); break;
				case WM_KEYUP : PcReciever->KeyReleased(msg.wParam); break;
				case WM_MOUSEMOVE: PcReciever->MouseMoved(msg.lParam); break;
				case WM_LBUTTONDOWN: PcReciever->MouseButtonPressed(MOUSE_LBUTTON); break;
				case WM_RBUTTONDOWN: PcReciever->MouseButtonPressed(MOUSE_RBUTTON); break;
				case WM_MBUTTONDOWN: PcReciever->MouseButtonPressed(MOUSE_MBUTTON); break;
				case WM_LBUTTONUP: PcReciever->MouseButtonReleased(MOUSE_LBUTTON); break;
				case WM_RBUTTONUP: PcReciever->MouseButtonReleased(MOUSE_RBUTTON); break;
				case WM_MBUTTONUP: PcReciever->MouseButtonReleased(MOUSE_MBUTTON); break;
				default:
					TranslateMessage(&msg);
					DispatchMessage(&msg);
			}
		}
	}

	UnregisterClass(L"MainWindow", wc.hInstance);

	WindowIsUp = false;

	return 1;
}


int Window::SetVideoSettings(VideoSettings* _settings)
{
	Settings = _settings;
	return 1;
}


bool Window::IsUp()
{
	return WindowIsUp;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		case WM_DESTROY: PostQuitMessage(0); return 0; break;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}