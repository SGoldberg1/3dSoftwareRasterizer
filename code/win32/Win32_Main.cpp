#include "Win32_Main.h"

global_variable win32_offscreen_buffer GlobalWin32Buffer;
global_variable int64 GlobalWin32PerformanceFrequency;
global_variable bool32 GlobalIsRunning;
global_variable bool32 GlobalIsPaused;


struct win32_engine_code
{
    HMODULE EngineDll;
    engine_update* Update;
    bool32 IsValid;
    FILETIME LastLoadTime;
};

internal_function void
Win32FreeEngineCode(win32_engine_code* engineCode)
{
    FreeLibrary(engineCode->EngineDll);
    engineCode->Update = EngineUpdateStub;
}

internal_function inline FILETIME
Win32GetFileLastWrite(char* fileName)
{
    FILETIME result = {};
    WIN32_FILE_ATTRIBUTE_DATA fileAttributes = {};
    
    if(GetFileAttributesExA(fileName, GetFileExInfoStandard, &fileAttributes))
    {
        result = fileAttributes.ftLastAccessTime;
    }
    
    return(result);
}

internal_function win32_engine_code
Win32LoadEngineCode(char* fileName)
{
    win32_engine_code result = {};
    LPCTSTR fileCopy = "TEMP_SGEngine.dll";
    
    if(CopyFileA(fileName, fileCopy, FALSE))
    {
        result.EngineDll = LoadLibraryA(fileCopy);
        
        if(result.EngineDll)
        {
            result.Update = (engine_update*)GetProcAddress(result.EngineDll, "EngineUpdate");
            result.LastLoadTime = Win32GetFileLastWrite(fileName);
            result.IsValid = (result.Update != 0);
        }
    }
    
    
    return(result);
}

int WINAPI
WinMain(HINSTANCE instance, HINSTANCE depreciated, LPSTR commandLine, int showWindow)
{
    LARGE_INTEGER queryPerformanceFrequency;
    QueryPerformanceFrequency(&queryPerformanceFrequency);
    GlobalWin32PerformanceFrequency = queryPerformanceFrequency.QuadPart;
    
    bool32 isGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);
    
    WNDCLASS windowClass = {};
    windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = Win32WindowCallback;
    windowClass.hInstance = instance;
    windowClass.hIcon = LoadIcon(0, IDI_SHIELD);
    windowClass.hCursor = LoadCursor(0, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)0;
    windowClass.lpszClassName = APPLICATION_NAME;
    
    if(RegisterClassA(&windowClass))
    {
        HWND window = CreateWindowExA(0,
                                      APPLICATION_NAME,
                                      APPLICATION_NAME,
                                      WS_OVERLAPPEDWINDOW,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      0, 0, instance, 0);
        
        if(window)
        {
            //DEVICE INITIALIZATION
            HDC deviceContext = GetDC(window);
            int32 screenResolutionWidth = GetDeviceCaps(deviceContext, HORZRES);
            int32 screenResolutionHeight = GetDeviceCaps(deviceContext, VERTRES);
            int32 verticalRefreshRate = GetDeviceCaps(deviceContext, VREFRESH);
            
            int32 bufferWidth = screenResolutionWidth / 2;
            int32 bufferHeight = screenResolutionHeight / 2;
            Win32ResizeOffscreenBuffer(&GlobalWin32Buffer, 
                                       bufferWidth, 
                                       bufferHeight);
            MoveWindow(window, 
                       bufferWidth - (bufferWidth / 2), bufferHeight - (bufferHeight / 2),
                       bufferWidth + 16, bufferHeight + 39, TRUE);
            
            ShowWindow(window, showWindow);
            GlobalIsRunning = TRUE;
            
            //CLOCKING INITIALIZATION
            float32 gameRefreshRate = verticalRefreshRate / 2.0f;
            float32 actualFramesPerSecond = 0;
            float32 targetFramePerSecond = 1.0f / gameRefreshRate;
            LARGE_INTEGER counterLast = Win32GetClockCounter();
            
            //INPUT INITIALIZATION
            engine_buffer engineBuffer = {};
            engine_input engineInput = {};
            engineInput.DeltaTime = targetFramePerSecond;
            input_controller controllerInput[2] = {};
            input_controller* newControllerInput = &controllerInput[0];
            input_controller* zeroControllerInput = &controllerInput[1];
            
            //MEMORY INTIALIZATION
            engine_memory engineMemory = {};
            engineMemory.PermanentMemorySize = GIGABYTES((uint64)2);
            engineMemory.PermanentMemory = VirtualAlloc(0, 
                                                        engineMemory.PermanentMemorySize, 
                                                        MEM_COMMIT | MEM_RESERVE, 
                                                        PAGE_READWRITE);
            engineMemory.IsInitialized = (engineMemory.PermanentMemory != 0);
            
            //ENGINE CODE INITIALIZATION
            char* engineDllName = "SGEngine.dll";
            win32_engine_code engineCode = Win32LoadEngineCode(engineDllName);
            
            if(engineMemory.IsInitialized && engineCode.IsValid)
            {
                while(GlobalIsRunning)
                {
                    FILETIME currentEngineDllFileTime = Win32GetFileLastWrite(engineDllName);
                    
                    
                    
                    if(CompareFileTime(&currentEngineDllFileTime, &engineCode.LastLoadTime) != 0)
                    {
                        Win32FreeEngineCode(&engineCode);
                        engineCode = Win32LoadEngineCode(engineDllName);
                    }
                    
                    //INPUT
                    input_controller  oldControllerInput = *newControllerInput;
                    *newControllerInput = *zeroControllerInput;
                    
                    for(int i = 0; i < ArrayLength(zeroControllerInput->Buttons); ++i)
                    {
                        newControllerInput->Buttons[i].IsDown = oldControllerInput.Buttons[i].IsDown;
                    }
                    
                    Win32ProcessMessageQueue(newControllerInput);
                    engineInput.Controller = *newControllerInput;
                    
                    //UPDATE ENGINE
                    Win32BufferToEngineBuffer(&GlobalWin32Buffer, &engineBuffer);
                    if(engineCode.Update)
                        engineCode.Update(&engineBuffer, &engineInput, &engineMemory);
                    float32 currentSeconds = Win32GetSecondsElapsed(counterLast, Win32GetClockCounter());
                    
                    //FRAME CONSTRAINT
                    if(currentSeconds < targetFramePerSecond)
                    {
                        if(isGranular)//IF TIMER RESOLUTION IS GRANULAR
                        {
                            DWORD sleepMilliseconds = (DWORD)(1000.0f * 
                                                              (targetFramePerSecond - currentSeconds));
                            
                            if(sleepMilliseconds)
                                Sleep(sleepMilliseconds);
                        }
                        
                        while(currentSeconds < targetFramePerSecond)
                        {
                            currentSeconds = Win32GetSecondsElapsed(counterLast, Win32GetClockCounter());
                        }
                    }
                    
                    //CLOCK FRAME
                    LARGE_INTEGER counterEnd = Win32GetClockCounter();
                    int32 counterElapsed = (int32)(counterEnd.QuadPart - counterLast.QuadPart);
                    int32 milliseconds = (int32)(1000 * Win32GetSecondsElapsed(counterLast, counterEnd));
                    int32 framesPerSecond = (int32)(GlobalWin32PerformanceFrequency / counterElapsed);
                    counterLast = counterEnd;
                    
#if ENGINE_DEBUG
                    char debugPerformanceBuffer[256] = {0};
                    wsprintf(debugPerformanceBuffer, 
                             "M/S: %d  |  FPS: %d\n", 
                             milliseconds, framesPerSecond);
                    OutputDebugString(debugPerformanceBuffer);
#endif
                    //PAINT SCREEN
                    Win32PaintOffScreenBuffer(deviceContext, 
                                              &GlobalWin32Buffer, 
                                              GlobalWin32Buffer.Width, 
                                              GlobalWin32Buffer.Height);
                }
            }
            else
                ;//TODO: LOG ENGINE MEMORY FAILED TO INTIALIZE
            
            
        }
        else
            ;//TODO: LOG WINDOW CREATION FAILED
    }
    else
        ;//TODO: LOG WINDOW REGISTRATION  FAILED
    
    
    return(0);
}

LRESULT WINAPI
Win32WindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    
    switch(message)
    {
        case WM_SIZE:
        {
            int32 width = LOWORD(lParam);
            int32 height = HIWORD(lParam);
            char buffer[256];
            
            wsprintf(buffer,"%dx%d\n", width, height);
            OutputDebugString(buffer);
            
        }break;
        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYUP:
        case WM_KEYDOWN:
        {
            OutputDebugString("Wrongfully Handled\n");
        }break;
        
        case WM_QUIT:
        {
            DestroyWindow(window);
        }break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }break;
        default:
        {
            result = DefWindowProc(window, message, wParam, lParam);
        }break;
        
    }
    
    return(result);
}

void
Win32ResizeOffscreenBuffer(win32_offscreen_buffer* buffer, int32 width, int32 height)
{
    if(buffer->Memory)
        VirtualFree(buffer->Memory, 0, MEM_RELEASE);
    
    buffer->Width = width;
    buffer->Height = height;
    buffer->BytesPerPixel = BYTES_PER_PIXEL;
    buffer->Pitch = width * BYTES_PER_PIXEL;
    buffer->Memory = VirtualAlloc(0, width * height * BYTES_PER_PIXEL, MEM_COMMIT, PAGE_READWRITE);
    
    buffer->Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    buffer->Info.bmiHeader.biWidth = width;
    buffer->Info.bmiHeader.biHeight = -height;
    buffer->Info.bmiHeader.biPlanes = 1;//PER MICROSOFT DOCUMENTATION
    buffer->Info.bmiHeader.biBitCount = BITS_PER_PIXEL;
    buffer->Info.bmiHeader.biCompression = BI_RGB;
    buffer->Info.bmiHeader.biSizeImage = width * height;
}

void
Win32PaintOffScreenBuffer(HDC deviceContext, 
                          win32_offscreen_buffer* buffer, 
                          int32 windowWidth, int32 windowHeight)
{
    StretchDIBits(deviceContext,
                  0, 0, windowWidth, windowHeight,
                  0, 0, buffer->Width, buffer->Height,
                  buffer->Memory,
                  &buffer->Info,
                  DIB_RGB_COLORS,
                  SRCCOPY);
}

internal_function inline LARGE_INTEGER
Win32GetClockCounter(void)
{
    LARGE_INTEGER result;
    QueryPerformanceCounter(&result);
    return(result);
}

internal_function inline float32
Win32GetSecondsElapsed(LARGE_INTEGER startCounter, LARGE_INTEGER endCounter)
{
    return((endCounter.QuadPart - startCounter.QuadPart) / (float32)GlobalWin32PerformanceFrequency);
}


internal_function void
Win32BufferToEngineBuffer(win32_offscreen_buffer* win32Buffer, engine_buffer* engineBuffer)
{
    engineBuffer->Width = win32Buffer->Width;
    engineBuffer->Height = win32Buffer->Height;
    engineBuffer->Pitch = win32Buffer->Pitch;
    engineBuffer->BytesPerPixel = win32Buffer->BytesPerPixel;
    engineBuffer->Memory = win32Buffer->Memory;
}

internal_function void
Win32ProcessInput(input_button* button, bool32 isDown)
{
    button->IsDown = isDown;
    ++button->HalfTransitionCount;
}

internal_function void
Win32ProcessMessageQueue(input_controller *controllerInput)
{
    MSG message;
    
    while(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
    {
        switch(message.message)
        {
            case WM_QUIT:
            {
                GlobalIsRunning = FALSE;
            }break;
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYUP:
            case WM_KEYDOWN:
            {
                bool32 wasDown = ((message.lParam & (1 << 30)) != 0);
                bool32 isDown = ((message.lParam & (1 << 31)) == 0);
                bool32 isAlt = ((message.lParam & (1 << 29)) != 0);
                
                if(isDown != wasDown)
                {
                    switch(message.wParam)
                    {
                        case 'A':
                        {
                            Win32ProcessInput(&controllerInput->A, isDown);
                        }break;
                        case 'D':
                        {
                            Win32ProcessInput(&controllerInput->D, isDown);
                        }break;
                        case 'S':
                        {
                            Win32ProcessInput(&controllerInput->S, isDown);
                        }break;
                        case 'W':
                        {
                            Win32ProcessInput(&controllerInput->W, isDown);
                        }break;
                        case VK_ESCAPE:
                        {
                            Win32ProcessInput(&controllerInput->Escape, isDown);
                        }break;
                        case VK_F4:
                        {
                            if(isAlt)
                                PostQuitMessage(0);
                        }break;
                        default:
                        break;
                    }
                }
            }break;
            default:
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }break;
        }
    }
}
