#include <glad/glad.h>
#include <window.h>
#include <resource.h>
 
// Window procedure: Handles messages sent to the window
LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC ghdc;
	static HGLRC ghrc;
	RECT clientRect;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		ghdc = GetDC(hWnd);
		if (!SetupPixelFormatGL(ghdc)) {
			PostQuitMessage(0);
			return -1; 
		}
		ghrc = wglCreateContext(ghdc);
		if (!ghrc) {
			MessageBox(hWnd, L"Failed to create OpenGL context", L"Error", MB_OK);
			PostQuitMessage(0);
			return -1; 
		}
		if (!wglMakeCurrent(ghdc, ghrc)) {
			MessageBox(hWnd, L"Failed to make OpenGL context current", L"Error", MB_OK);
			wglDeleteContext(ghrc);
			PostQuitMessage(0);
			return -1; 
		}
		LoadOpenGLFunctions();
		GetClientRect(hWnd, &clientRect);
		int width = clientRect.right - clientRect.left;
		int height = clientRect.bottom - clientRect.top;
		glViewport(0, 0, width, height);
		break;
	}
	case WM_SIZE:
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);
		glViewport(0, 0, width, height);
		break;
	}
	case WM_DESTROY:
		if (ghrc) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(ghrc);
			ghrc = NULL;
		}
		if (ghdc) {
			ReleaseDC(hWnd, ghdc);
			ghdc = NULL;
		}
		PostQuitMessage(0);
		return 0; 
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


Window::Window()
	: m_hInstance(GetModuleHandle(nullptr)) // Get the instance handle of the application
{
	// Define a unique window class name
	const wchar_t* CLASS_NAME = L"Nicks Window Class";

	// window dimensions
	int width = 600;
	int height = 600;

	// Define the window class properties
	WNDCLASS wc = {};
	wc.lpszClassName = CLASS_NAME; // Set the class name
	wc.hInstance = m_hInstance;    // Set the instance handle
	wc.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCEW(IDI_MYICON)); // Load the icon from the resource
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Set the cursor
	wc.lpfnWndProc = WindowProc;   // Set the function to handle window messages

	// Register the window class
	RegisterClass(&wc);

	// Define the window style 
	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	// Create the window using the defined class and properties
	m_hWnd = CreateWindowExW(
		0,                  // Extended window styles (none in this case)
		CLASS_NAME,         // Name of the window class
		L"OpenGL Project",           // Window title
		WS_OVERLAPPEDWINDOW,              // Window style
		CW_USEDEFAULT,          // X position
		CW_USEDEFAULT,           // Y position
		width,  // Width
		height,  // Height
		NULL,               // Parent window (none)
		NULL,               // Menu (none)
		m_hInstance,        // Application instance handle
		NULL                // Additional application data (not used)
	);

	// Show the window on the screen
	ShowWindow(m_hWnd, SW_SHOW);
}

// Destructor for the Window class
Window::~Window()
{
	const wchar_t* CLASS_NAME = L"Nicks Window Class";
	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool SetupPixelFormatGL(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	if (pixelFormat == 0) {
		MessageBox(NULL, L"choose pixel format failed", L"error", MB_OK); //window handle, text, title, buttonw with okay
		return false;
	}

	if (!SetPixelFormat(hdc, pixelFormat, &pfd)) {
		MessageBox(NULL, L"set pixel format failed", L"error", MB_OK);
		return false;
	}

	return TRUE;
}

bool LoadOpenGLFunctions() {
	if (!gladLoadGLLoader((GLADloadproc)GetOpenGLFunctionPointer)) {
		MessageBox(NULL, L"Failed to initialize GLAD", L"Error", MB_OK);
		return false;
	}
	return true;
}

void* GetOpenGLFunctionPointer(const char* name) {
	void* p = (void*)wglGetProcAddress(name);
	if (p == NULL || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1)) {
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void*)GetProcAddress(module, name);
	}
	return p;
}


	

