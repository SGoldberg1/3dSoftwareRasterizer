#ifndef ENGINEPLATFORM_H
#define ENGINEPLATFORM_H

#define ENGINE_UPDATE_PROC_STRING "EngineUpdate"

//////////////////////////////// DEBUG ////////////////////////////////

struct debug_platform_file
{
    void* Contents;
    u32 FileSize;
    b32 IsValid;
};

typedef void debug_platform_free_file_memory(void* memory);
typedef debug_platform_file debug_platform_read_entire_file(char* fileName);
typedef void debug_platform_write_entire_file(char* fileName, s32 memorySize, void* memory);
typedef void debug_platform_output_console(char* format, ...);

struct engine_debug
{
    debug_platform_write_entire_file* WriteEntireFile;
    debug_platform_read_entire_file* ReadEntireFile;
    debug_platform_free_file_memory* FreeMemory;
    debug_platform_output_console* OutputConsole;
};

struct engine_memory
{
    b32 IsInitialized;
    u64 PermanentMemorySize;
    void* PermanentMemory;
};

struct engine_input_button_state
{
    b32 IsDown;
    b32 WasDown;
};

#define ENGINE_BUTTON_COUNT 22
struct engine_input_controller
{
    union
    {
        engine_input_button_state Buttons[ENGINE_BUTTON_COUNT];
        struct
        {
            engine_input_button_state A;
            engine_input_button_state D;
            engine_input_button_state S;
            engine_input_button_state Q;
            engine_input_button_state E;
            engine_input_button_state W;
            engine_input_button_state Num0;
            engine_input_button_state Num1;
            engine_input_button_state Num2;
            engine_input_button_state Num3;
            engine_input_button_state Num4;
            engine_input_button_state Num5;
            engine_input_button_state Num6;
            engine_input_button_state Num7;
            engine_input_button_state Num8;
            engine_input_button_state Num9;
            engine_input_button_state Up;
            engine_input_button_state Down;
            engine_input_button_state Left;
            engine_input_button_state Right;
            engine_input_button_state Escape;
            engine_input_button_state Space;
        };
    };
};

struct engine_input_mouse
{
    s32 PostionX;
    s32 PostionY;
    s32 MouseScroll;
    
    union
    {
        engine_input_button_state Buttons[5];
        struct
        {
            engine_input_button_state Left;
            engine_input_button_state Right;
            engine_input_button_state Middle;
            engine_input_button_state Button3;
            engine_input_button_state Button4;
        };
    };
};

struct engine_input
{
    engine_input_mouse Mouse;
    engine_input_controller KeyBoard;
};

struct engine_time
{
    r32 DeltaTime;
    r32 FixedTime;
    r32 FrameRate;
};

//////////////////////////////// ENGINE ENTRYPOINT ////////////////////////////////

#define ENGINE_UPDATE(name) void name(engine_buffer* buffer, \
engine_memory* memory, \
engine_input* input, \
engine_time* time, \
engine_debug* debug, \
render_group* worldRenderGroup)

typedef ENGINE_UPDATE(engine_update);

ENGINE_UPDATE(EngineUpdateStub) { }

extern "C"
ENGINE_UPDATE(EngineUpdate);

#endif//END ENGINEPLATFORM_H