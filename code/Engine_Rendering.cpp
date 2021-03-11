
inline void
InitializeRenderGroup(memory_block* block,
                      render_group* group,
                      s32 size)
{
    group->Used = 0;
    group->Count = 0;
    group->Size = size;
    group->Base = (u8*)Memory_PushSize(block, size);
}

inline void
Render_ClearRenderGroup(render_group* group)
{
    group->Count = 0;
    group->Used = 0;
}

#define Render_PushElement(group, type) (type*)render_push_element(group, sizeof(type), render_type_##type)

void*
render_push_element(render_group* group,
                    s32 size,
                    render_type type)
{
    ASSERT((group->Used + size + sizeof(render_header)) < group->Size);
    render_header* result = (render_header*)((u8*)group->Base + group->Used);
    result->Type = type;
    group->Used += (size + sizeof(render_header));
    ++group->Count;
    ++result;
    return(result);
}

void
Render_PushClear(render_group* group,
                 v4 color)
{
    render_clear* clear = Render_PushElement(group, render_clear);
    clear->Color = color;
}

void
Render_PushBitmap(render_group* group,
                  engine_bitmap image,
                  v2 position,
                  r32 scale = 1,
                  v4 color = {1, 1, 1, 1})
{
    render_bitmap* bitmap = Render_PushElement(group, render_bitmap);
    bitmap->Image = image;
    bitmap->Position = position;
    bitmap->Scale = scale;
    bitmap->Color = color;
}

void
Render_PushLine2D(render_group* group,
                  v2 point1,
                  v2 point2,
                  v4 color = {1, 1, 1, 1})
{
    render_line2d* line = Render_PushElement(group, render_line2d);
    line->Points[0] = point1;
    line->Points[1] = point2;
    line->Color = color;
}

void
Render_PushRectangle(render_group* group,
                     v2 position,
                     v2 dimensions,
                     v4 color)
{
    render_rectangle* rectangle = Render_PushElement(group, render_rectangle);
    rectangle->Position = position;
    rectangle->Dimensions = dimensions;
    rectangle->Color = color;
}

void
Render_PushMesh(render_group* group,
                engine_mesh* engineMesh,
                engine_light_source* lightSource,
                s32 renderMode,
                v3 worldPosition,
                v3 worldScale,
                v3 worldRotation,
                v4 color)
{
    render_mesh* mesh = Render_PushElement(group, render_mesh);
    mesh->TriangleCount = engineMesh->TriangleCount;
    mesh->VertexCount = engineMesh->VertexCount;
    mesh->NormalCount = engineMesh->NormalCount;
    mesh->Normals = engineMesh->Normals;
    mesh->Triangles = engineMesh->Triangles;
    mesh->Vertices = engineMesh->Vertices;
    mesh->LightSourceCount = 1;
    mesh->LightSource = lightSource;
    mesh->RenderMode = renderMode;
    mesh->Color = color;
    
    mesh->WorldPosition = worldPosition;
    mesh->WorldScale = worldScale;
    mesh->WorldRotation = worldRotation;
}