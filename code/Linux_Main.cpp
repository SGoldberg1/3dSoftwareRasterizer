#include <unistd.h>
#include <dlfcn.h>

#include <SDL2/SDL.h>

#include "Engine_Types.h"
#include "Engine_Math.h"
#include "Engine_Rendering.h"
#include "Engine_Platform.h"

#include "Engine_SoftwareRendering.cpp"

#include "Linux_Main.h"

global_variable b32 GlobalRunning = FALSE;



internal_function void
DEBUG_OutputConsole(char* format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
}

debug_platform_file
DEBUG_ReadFile(char* fileName)
{
    debug_platform_file result = {};
    FILE* file = fopen(fileName, "r");
    s32 bytesRead = 0;
    struct stat fileAttribute = {};
    
    if(file)
    {
        stat(fileName, &fileAttribute);
        result.FileSize = fileAttribute.st_size;
        
        if(result.FileSize > 0)
        {
            result.Contents = malloc(result.FileSize);
            
            if(result.Contents)
            {
                bytesRead = fread(result.Contents,
                                  result.FileSize,
                                  sizeof(s8),
                                  file);
                if(bytesRead)
                    result.IsValid = TRUE;
            }
        }
        
        fclose(file);
    }
    
    return(result);
}


internal_function r32
SDLGetSecondsElapsed(u64 start, u64 end)
{
    r32 result = ((r32)(end - start) / (r32)(SDL_GetPerformanceFrequency()));
    return(result);
}

internal_function inline void
LinuxResizeOffscreenBuffer(engine_buffer* buffer,
                           SDL_Texture** texture,
                           SDL_Renderer* renderer,
                           s32 width, s32 height)
{
    if(buffer->Memory)
        free(buffer->Memory);
    if(*texture)
        SDL_DestroyTexture(*texture);
    
    buffer->BytesPerPixel = 4;
    buffer->Pitch = (BYTES_PER_PIXEL_4 * width);
    buffer->Width = width;
    buffer->Height = height;
    
    buffer->Memory = malloc((width * height * BYTES_PER_PIXEL_4));
    *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                 SDL_TEXTUREACCESS_STREAMING,
                                 width, height);
}

internal_function inline void
LinuxProcessInput(engine_input_button_state* button,
                  b32 isDown, b32 wasDown)
{
    button->IsDown = isDown;
    button->WasDown = wasDown;
}

internal_function void
LinuxProcessMessages(engine_input_controller* keyBoard)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT:
            {
                if(event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    GlobalRunning = FALSE;
                }
            }break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                b32 isDown = (event.key.state == SDL_PRESSED);
                b32 wasDown = (event.key.state == SDL_RELEASED || event.key.repeat);
                
                if(wasDown != isDown)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_a:
                        {
                            LinuxProcessInput(&keyBoard->A, isDown, wasDown);
                        }break;
                        case SDLK_s:
                        {
                            LinuxProcessInput(&keyBoard->S, isDown, wasDown);
                        }break;
                        case SDLK_d:
                        {
                            LinuxProcessInput(&keyBoard->D, isDown, wasDown);
                        }break;
                        case SDLK_w:
                        {
                            LinuxProcessInput(&keyBoard->W, isDown, wasDown);
                        }break;
                        case SDLK_q:
                        {
                            LinuxProcessInput(&keyBoard->Q, isDown, wasDown);
                        }break;
                        case SDLK_e:
                        {
                            LinuxProcessInput(&keyBoard->E, isDown, wasDown);
                        }break;
                        case SDLK_1:
                        {
                            LinuxProcessInput(&keyBoard->Num1, isDown, wasDown);
                        }break;
                        case SDLK_2:
                        {
                            LinuxProcessInput(&keyBoard->Num2, isDown, wasDown);
                        }break;
                        case SDLK_3:
                        {
                            LinuxProcessInput(&keyBoard->Num3, isDown, wasDown);
                        }break;
                        case SDLK_4:
                        {
                            LinuxProcessInput(&keyBoard->Num4, isDown, wasDown);
                        }break;
                        case SDLK_5:
                        {
                            LinuxProcessInput(&keyBoard->Num5, isDown, wasDown);
                        }break;
                        case SDLK_DOWN:
                        {
                            LinuxProcessInput(&keyBoard->Down, isDown, wasDown);
                        }break;
                        case SDLK_UP:
                        {
                            LinuxProcessInput(&keyBoard->Up, isDown, wasDown);
                        }break;
                        case SDLK_LEFT:
                        {
                            LinuxProcessInput(&keyBoard->Left, isDown, wasDown);
                        }break;
                        case SDLK_RIGHT:
                        {
                            LinuxProcessInput(&keyBoard->Right, isDown, wasDown);
                        }break;
                        case SDLK_ESCAPE:
                        {
                            LinuxProcessInput(&keyBoard->Escape, isDown, wasDown);
                        }break;
                        default:
                        break;
                    }
                }
            }break;
            default:
            {
                
            }break;
        }
    }
}


void
LinuxCopyFile(char* fileIn, char* fileOut)
{
#define BUFFER_SIZE KILOBYTE(4)
    
    remove(fileOut);
    s32 inputFile = open(fileIn, O_RDONLY);
    s32 outputFile = open(fileOut, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ssize_t inByte = 0;
    ssize_t outByte = 0;
    s8 buffer[BUFFER_SIZE] = {};
    
    if(inputFile && outputFile)
    {
        while((inByte = read(inputFile, buffer, BUFFER_SIZE)) > 0)
        {
            outByte = write(outputFile, buffer, inByte);
        }
        
        close(inputFile);
        close(outputFile);
    }
}

s64
LinuxGetLastWriteTime(char* fileName)
{
    struct stat fileAttribute;
    stat(fileName, &fileAttribute);
    s64 result = fileAttribute.st_mtime;
    return(result);
}

linux_module
LinuxLoadModule(char* fileName)
{
    linux_module result = {};
    char* tempFileName = "./temp_file.so";
    
    LinuxCopyFile(fileName, tempFileName);
    
    result.Handle = dlopen(tempFileName, RTLD_LAZY);
    
    if(result.Handle)
    {
        result.LastWriteTime = LinuxGetLastWriteTime(fileName);
        result.Update = (engine_update*)dlsym(result.Handle,
                                              "EngineUpdate");
    }
    
    if(result.Update)
        result.IsValid = TRUE;
    else
    {
        result.Update = EngineUpdateStub;
    }
    
    return(result);
}

void
LinuxFreeModule(linux_module* module)
{
    if(module->Handle)
        dlclose(module->Handle);
    
    module->IsValid = FALSE;
    module->Update = EngineUpdateStub;
}

int
main(int argc, char** args)
{
    s32 resolutionX = 0;
    s32 resolutionY = 0;
    s32 monitorRefreshRate = 0;
    
    SDL_Texture* texture = 0;
    render_group worldRenderGroup = {};
    
    if(SDL_Init(SDL_INIT_VIDEO) == FALSE)
    {
        SDL_DisplayMode displayMode = {};
        
        // TODO(Stephen): STRUCTURE THIS BETTER!!!
        //NEED TO ENUMERATE DISPLAYS
        //NEED PROPER ERROR CHECKING
        if(SDL_GetCurrentDisplayMode(0, &displayMode) == FALSE)
        {
            resolutionX = displayMode.w / 2;
            resolutionY = displayMode.h / 2;
            monitorRefreshRate = displayMode.refresh_rate;
        }
        else
        {
            // TODO(Stephen): LOGGING FAILURE TO GET DISPLAY MODE
        }
        
        SDL_Window* window = SDL_CreateWindow(APPLICATION_NAME,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              resolutionX, resolutionY,
                                              0);
        if(window)
        {
            SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
            
            engine_buffer engineBuffer = {};
            LinuxResizeOffscreenBuffer(&engineBuffer, &texture, sdlRenderer, resolutionX, resolutionY);
            
            r32 targetSeconds = (1.0f / (r32)monitorRefreshRate);
            
            GlobalRunning = TRUE;
            linux_module engineModule = LinuxLoadModule(ENGINE_LIBRARY_NAME);
            
            engine_input engineInput = {};
            engine_input* newController = &engineInput;
            engine_input oldController = {};
            
            engine_time engineTime = {};
            engineTime.FixedTime = targetSeconds;
            
            engine_memory engineMemory = {};
            engineMemory.PermanentMemorySize = GIGABYTE(2);
            engineMemory.PermanentMemory = malloc(engineMemory.PermanentMemorySize);
            
            engine_debug engineDebug = {};
            engineDebug.OutputConsole = DEBUG_OutputConsole;
            engineDebug.ReadEntireFile = DEBUG_ReadFile;
            
            u64 counterLast = SDL_GetPerformanceCounter();
            r32 frameRate = 0;
            r32 deltaTime = 0;
            
            while(GlobalRunning)
            {
                //LIVE CODING
                u64 lastWriteTime = LinuxGetLastWriteTime(ENGINE_LIBRARY_NAME);
                if(lastWriteTime > engineModule.LastWriteTime)
                {
                    LinuxFreeModule(&engineModule);
                    engineModule = LinuxLoadModule(ENGINE_LIBRARY_NAME);
                }
                
                oldController = *newController;
                *newController = {};
                
                for(s32 i = 0; i < Array_Length(newController->KeyBoard.Buttons); ++i)
                {
                    newController->KeyBoard.Buttons[i].IsDown =
                        oldController.KeyBoard.Buttons[i].IsDown;
                }
                
                LinuxProcessMessages(&newController->KeyBoard);
                
                //UPDATE ENGINE
                engineModule.Update(&engineBuffer,
                                    &engineMemory,
                                    &engineInput,
                                    &engineTime,
                                    &engineDebug,
                                    &worldRenderGroup);
                
                r32 secondsElapsed = SDLGetSecondsElapsed(counterLast,
                                                          SDL_GetPerformanceCounter());
                if(secondsElapsed < targetSeconds)
                {
                    
#if 0// TODO(Stephen): NEED TO LOWER OS SLEEP GRANULARITY
                    u32 sleepMS = (u32)(1000.0f * (targetSeconds - secondsElapsed));
                    
                    if(sleepMS > 0)
                        SDL_Delay(sleepMS);
#endif
                    
                    while(secondsElapsed < targetSeconds)
                    {
                        secondsElapsed = SDLGetSecondsElapsed(counterLast,
                                                              SDL_GetPerformanceCounter());
                    }
                }
                
                u64 counterEnd = SDL_GetPerformanceCounter();
                engineTime.DeltaTime = secondsElapsed;
                engineTime.FrameRate = ((r32)SDL_GetPerformanceFrequency() /
                                        (r32)(counterEnd - counterLast));
                
                
                SDL_SoftwareRender(sdlRenderer, texture, &worldRenderGroup, &engineBuffer);
                counterLast = counterEnd;
            }
            
            LinuxFreeModule(&engineModule);
            free(engineMemory.PermanentMemory);
            SDL_DestroyWindow(window);
        }
        else
        {
            //TODO(stephen):logging
        }
        
        SDL_Quit();
    }
    
    return(0);
}
