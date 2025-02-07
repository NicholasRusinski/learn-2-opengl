#include <windows.h>
#include <window.h>
#include <renderer.h>
#include <glad/glad.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    MSG msg = {};
    Window window;
    HWND hwnd = window.getHWND();

    bool running = true;

    while (running) { // main loop

        // message loop
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);// sends message to winproc
        }

        glClearColor(0.5f, 0.6f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
      
        HDC hdc = GetDC(hwnd);
        SwapBuffers(hdc);  // this displays the next buffer content
        ReleaseDC(hwnd, hdc);

        Sleep(10);  // add a small delay to reduce CPU usageg
    }
    return 0;
}


