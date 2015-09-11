#include "Window.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


Window::Window(LPCWSTR _name, HINSTANCE* _hInstance, PcInputReciever* _reciever)
{
	name = _name;
	hInstance = _hInstance;
	windowIsUp = false;
	pcReciever = _reciever;
}


Window::~Window()
{
	delete settings;
	delete name;
	delete hInstance;
	delete pcReciever;
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

	if (settings->fullscreen)
	{
		handle = CreateWindowEx(NULL,
			L"MainWindow",
			name,
			WS_EX_TOPMOST | WS_POPUP,
			0, 0,
			settings->monitorRes->width, settings->monitorRes->height,
			NULL,
			NULL,
			*hInstance,
			NULL);
	}
	else
	{
		handle = CreateWindow(L"MainWindow", name, WS_OVERLAPPEDWINDOW, 150, 150, settings->screenRes->width, settings->screenRes->height, NULL, NULL, *hInstance, NULL);
	}

	ShowWindow(handle, 5);
	UpdateWindow(handle);

	windowIsUp = true;

	// Enter the message loop to send keyboard and mouse input to the Pc Input Reciever
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			switch (msg.message)
			{
				case WM_KEYDOWN : pcReciever->KeyPressed(msg.wParam); break;
				case WM_KEYUP : pcReciever->KeyReleased(msg.wParam); break;
				case WM_MOUSEMOVE: pcReciever->MouseMoved(msg.lParam); break;
				case WM_LBUTTONDOWN: pcReciever->MouseButtonPressed(MOUSE_LBUTTON); break;
				case WM_RBUTTONDOWN: pcReciever->MouseButtonPressed(MOUSE_RBUTTON); break;
				case WM_MBUTTONDOWN: pcReciever->MouseButtonPressed(MOUSE_MBUTTON); break;
				case WM_LBUTTONUP: pcReciever->MouseButtonReleased(MOUSE_LBUTTON); break;
				case WM_RBUTTONUP: pcReciever->MouseButtonReleased(MOUSE_RBUTTON); break;
				case WM_MBUTTONUP: pcReciever->MouseButtonReleased(MOUSE_MBUTTON); break;
				default:
					TranslateMessage(&msg);
					DispatchMessage(&msg);
			}
		}
	}

	UnregisterClass(L"MainWindow", wc.hInstance);

	windowIsUp = false;

	return 1;
}


int Window::SetVideoSettings(VideoSettings* _settings)
{
	settings = _settings;
	return 1;
}


bool Window::IsUp()
{
	return windowIsUp;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		case WM_DESTROY: PostQuitMessage(0); return 0; break;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}