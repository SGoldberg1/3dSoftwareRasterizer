
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define APPLICATION_NAME "Engine"
#define ENGINE_LIBRARY_NAME "./engine.so"
#define BYTES_PER_PIXEL_4 4
#define BITS_PER_PIXEL_32 32

struct linux_module
{
    b32 IsValid;
    void* Handle;
    engine_update* Update;
    s64 LastWriteTime;
};