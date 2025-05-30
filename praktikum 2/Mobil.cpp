#include <windows.h>
#include <GL/gl.h>
#include <cmath>

HDC hdc;
HGLRC hglrc;

void drawCircle(float cx, float cy, float r, float red, float green, float blue) {
    const int segments = 40;
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * 3.1415926f * i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawCar() {
    glColor3f(1.0f, 0.4f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, 0.0f);
        glVertex2f(0.4f, 0.0f);
        glVertex2f(0.4f, 0.2f);
        glVertex2f(0.3f, 0.25f);
        glVertex2f(-0.3f, 0.25f);
        glVertex2f(-0.4f, 0.2f);
    glEnd();

    glColor3f(0.9f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.25f, 0.25f);
        glVertex2f(0.25f, 0.25f);
        glVertex2f(0.15f, 0.4f);
        glVertex2f(-0.15f, 0.4f);
    glEnd();

    drawCircle(-0.25f, -0.05f, 0.07f, 0.0f, 0.0f, 0.0f);
    drawCircle(0.25f, -0.05f, 0.07f, 0.0f, 0.0f, 0.0f);

    drawCircle(0.42f, 0.1f, 0.03f, 1.0f, 1.0f, 0.2f);
    drawCircle(-0.42f, 0.1f, 0.03f, 1.0f, 0.0f, 0.0f);
}

void renderScene() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    drawCar();

    SwapBuffers(hdc);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            hdc = GetDC(hwnd);
            PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR),
                1,
                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                PFD_TYPE_RGBA,
                32, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0,
                24, 8, 0,
                PFD_MAIN_PLANE,
                0, 0, 0, 0
            };
            int format = ChoosePixelFormat(hdc, &pfd);
            SetPixelFormat(hdc, format, &pfd);
            hglrc = wglCreateContext(hdc);
            wglMakeCurrent(hdc, hglrc);
            break;
        }
        case WM_CLOSE:
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hglrc);
            ReleaseDC(hwnd, hdc);
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASS wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Mobil2DApp";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, "Mobil 2D Pink dengan Roda & Lampu", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        renderScene();
        Sleep(16);
    }

    return 0;
}

