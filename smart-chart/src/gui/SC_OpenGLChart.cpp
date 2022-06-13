#include "SC_OpenGLChart.h"

gui::SC_OpenGLChart::SC_OpenGLChart()
    : m_OGLRenderContext(nullptr)
{
}

gui::SC_OpenGLChart::~SC_OpenGLChart()
{
}

bool gui::SC_OpenGLChart::OnPaint(HWND hWnd, WPARAM, LPARAM)
{
    PAINTSTRUCT paint;

    BeginPaint(hWnd, &paint);

    Render(paint.hdc);
    SwapBuffers(paint.hdc);

    EndPaint(hWnd, &paint);

    return false;
}

bool gui::SC_OpenGLChart::OnCreate(HWND hWnd, WPARAM, LPARAM)
{
    PIXELFORMATDESCRIPTOR ppx;

    ZeroMemory(&ppx, sizeof(PIXELFORMATDESCRIPTOR));

    ppx.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppx.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    ppx.cColorBits = 32;
    ppx.cDepthBits = 24;
    ppx.nVersion = 1;
    ppx.iPixelType = PFD_TYPE_RGBA;

    HDC dc = GetWindowDC(hWnd);

    int iPixelFormat = ChoosePixelFormat(dc, &ppx);

    if (!iPixelFormat)
        return false;

    if (!SetPixelFormat(dc, iPixelFormat, &ppx))
        return false;

    m_OGLRenderContext = wglCreateContext(dc);

    if (!m_OGLRenderContext)
        return false;

    wglMakeCurrent(dc, m_OGLRenderContext);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    return true;
}

bool gui::SC_OpenGLChart::OnSize(HWND hWnd, WPARAM, LPARAM)
{
    HDC hdc = GetWindowDC(hWnd);
    RECT clientarea;
    if (!GetClientRect(hWnd, &clientarea))
        return false;

    glViewport(0, 0, clientarea.right - clientarea.left, clientarea.bottom - clientarea.top);

    return false;
}

bool gui::SC_OpenGLChart::OnEraseBackground(HWND hWnd, WPARAM, LPARAM)
{
    return false;
}

void gui::SC_OpenGLChart::Render(HDC hdc)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);

    glVertex2f(-0.95f, -0.95f);
    glVertex2f(-0.95f, 0.95f);
    glVertex2f(0.95f, 0.95f);
    glVertex2f(0.95f, -0.95f);

    glEnd();

}
