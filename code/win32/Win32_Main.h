#ifndef WIN32_MAIN_H
#define WIN32_MAIN_H

#include <Windows.h>
#include <timeapi.h>
#include "SGEngine.h"

#define KILOBYTES(size) ((size) * 1024)
#define MEGABYTES(size) (KILOBYTES(size) * 1024)
#define GIGABYTES(size) (MEGABYTES(size) * 1024)
#define TERABYTES(size) (GIGABYTES(size) * 1024)

#define BYTES_PER_PIXEL 4
#define BITS_PER_PIXEL 32
#define APPLICATION_NAME "SGEngine"

struct win32_offscreen_buffer
{
    int32 Width;
    int32 Height;
    int32 Pitch;
    int32 BytesPerPixel;
    void* Memory;
    BITMAPINFO Info;
};

LRESULT WINAPI
Win32WindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
void
Win32ResizeOffscreenBuffer(win32_offscreen_buffer* buffer, int32 width, int32 height);
void
Win32PaintOffScreenBuffer(HDC deviceContext, win32_offscreen_buffer* buffer, int32 windowWidth, int32 windowHeight);
internal_function inline LARGE_INTEGER
Win32GetClockCounter(void);
internal_function inline float32
Win32GetSecondsElapsed(LARGE_INTEGER startCounter, LARGE_INTEGER endCounter);
internal_function void
Win32BufferToEngineBuffer(win32_offscreen_buffer* win32Buffer, engine_buffer* engineBuffer);
internal_function void
Win32ProcessInput(input_button* button, bool32 isDown);
internal_function void
Win32ProcessMessageQueue(input_controller *controllerInput);
#endif