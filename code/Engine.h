
global_variable engine_debug* Debug;

struct engine_primitives
{
    engine_mesh Cube;
    engine_mesh Plane;
    engine_mesh Quad;
    engine_mesh Sphere;//BROKEN
    engine_mesh TruncatedPyramid;
    engine_mesh Axis;
};

struct engine_state
{
    memory_block WorldMemory;
    s32 RenderMode = 0;
    
    engine_camera Camera;
    
    engine_bitmap DebugTextBitmap;
    engine_bitmap TestBitmap;
    
    engine_light_source LightSource;
    
    engine_primitives* Primitives;
    
    engine_mesh Sphere;
    engine_mesh LoadedMesh;
    engine_mesh AirplaneMesh;
    engine_mesh Sun;
    engine_mesh Tank;
};
