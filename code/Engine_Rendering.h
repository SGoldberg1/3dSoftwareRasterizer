#ifndef ENGINE_RENDERING_H
#define ENGINE_RENDERING_H

#define ALPHA_CHANNEL(color) (((color) >> 24) & 0xff)
#define RED_CHANNEL(color) (((color) >> 16) & 0xff)
#define GREEN_CHANNEL(color) (((color) >> 8) & 0xff)
#define BLUE_CHANNEL(color) (((color) >> 0) & 0xff)

#define RENDER_MODE_WIRE 0x00000001
#define RENDER_MODE_SOLID 0x00000002
#define RENDER_MODE_SHADED 0x00000004
#define RENDER_MODE_LIGHT_RAY 0x00000008
#define RENDER_MODE_NORMALS 0x00000010

struct engine_camera
{
    v3 WorldPosition;
    v3 EulerRotation;
    
    v3 LocalForward;
    v3 LocalRight;
    v3 LocalUp;
    
    r32 NearClipping;
    r32 FarClipping;
    s32 ScreenLeft;//LEFT SIDE OF THE SCREEN SPACE
    s32 ScreenRight;//RIGHT SIDE OF SCREEN SPACE
    s32 ScreenTop;//TOP SIDE OF SCREEN SPACE
    s32 ScreenBottom;//BOTTOM SIDE OF SCREEN SPACE
    s32 ViewWidth;//THE WIDTH OF SCREEN SPACE
    s32 ViewHeight;//THE HEIGHT OF SCREEN SPACE
    s32 FieldOfView;
    m4x4 ViewMatrix;
    m4x4 ProjectionMatrix;
};

#pragma pack(push, 1)
struct bitmap_header
{
    s16 ID;
    s32 FileSize;
    s16 Reserved1;
    s16 Reserved2;
    s32 PixelOffset;
    s32 HeaderSize;
    s32 Width;
    s32 Height;
    s16 Planes;
    s16 BitsPerPixel;
    s32 Compression;
    s32 ImageSize;
    s32 PixelPerMeterX;
    s32 PixelPerMeterY;
    s32 ColorPalette;
    s32 ImportantColors;
    u32 RedMask;
    u32 GreenMask;
    u32 BlueMask;
};
#pragma pack(pop)

struct engine_bitmap
{
    s32 Width;
    s32 Height;
    u32* Pixels;
};

struct engine_buffer
{
    s32 Width;
    s32 Height;
    s32 BytesPerPixel;
    s32 Pitch;
    void* Memory;
};

enum render_type
{
    render_type_render_clear,
    render_type_render_rectangle,
    render_type_render_text,
    render_type_render_line2d,
    render_type_render_mesh,
    render_type_render_bitmap
};

struct render_header
{
    render_type Type;
};

struct render_clear
{
    v4 Color;
};

struct render_rectangle
{
    v2 Position;
    v2 Dimensions;
    v4 Color;
};

struct render_line2d
{
    v2 Points[2];
    v4 Color;
};

struct render_bitmap
{
    engine_bitmap Image;
    v2 Position;
    r32 Scale;
    v4 Color;
};

struct render_group
{
    engine_camera* Camera;
    m4x4 WorldMatrix;
    s32 RenderMode;
    s32 Count;
    s32 Used;
    s32 Size;
    void* Base;
};

#define MAX_VERTICES 65535
#define MAX_TRIANGLES MAX_VERTICES * 6
struct engine_mesh
{
    s32 TriangleCount;
    s32 VertexCount;
    s32 NormalCount;
    v3 Normals[MAX_VERTICES];
    s32 Triangles[MAX_TRIANGLES];
    v3 Vertices[MAX_VERTICES];
};

struct engine_light_source
{
    v3 WorldPosition;
    r32 Intensity;
    r32 Radius;
    v4 Color;
};

struct render_mesh
{
    s32 TriangleCount;
    s32 VertexCount;
    s32 NormalCount;
    v3* Normals;
    s32* Triangles;
    v3* Vertices;
    
    s32 LightSourceCount;
    engine_light_source* LightSource;
    
    s32 RenderMode;
    
    v3 WorldPosition;
    v3 WorldScale;
    v3 WorldRotation;
    
    v4 Color;
};

#endif