#pragma once // Ensures this header file is included only once in a compilation unit

#include <Windows.h> // Includes the Windows API for GUI programming

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool SetupPixelFormatGL(HDC hdc);
bool LoadOpenGLFunctions();
void* GetOpenGLFunctionPointer(const char* name);

class Window
{
public:
	Window(); 
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	~Window();
	HWND getHWND() const { return m_hWnd; }

private:
	HINSTANCE m_hInstance; // Handle to the application instance
	HWND m_hWnd;           // Handle to the window
};


