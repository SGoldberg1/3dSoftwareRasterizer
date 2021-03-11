
#include "Engine_Types.h"
#include "Engine_Math.h"
#include "Engine_Rendering.h"
#include "Engine_Platform.h"

#include "Engine_Memory.h"
#include "Engine_Data_Structures.cpp"
#include "Engine_Math.cpp"
#include "Engine_Algorithms.cpp"
#include "Engine_TextProcessing.cpp"
#include "Engine_Rendering.cpp"

#include "Engine.h"

//NOTE: BITMAPS CAN HAVE A NEGATIVE HEIGHT FOR TOP DOWN DRAWING
//MAY NEED TO FLIP PIXEL ORDER
internal_function inline engine_bitmap
DEBUG_LoadBMP(debug_platform_read_entire_file* reader,
              char* fileName)
{
    engine_bitmap result = {};
    debug_platform_file file = reader(fileName);
    
    ASSERT(file.IsValid);
    
    bitmap_header* bitmapHeader = (bitmap_header*)file.Contents;
    ASSERT(bitmapHeader->BitsPerPixel == 32);
    
    result.Width = bitmapHeader->Width;
    result.Height = bitmapHeader->Height;
    result.Pixels = (u32*)((s8*)bitmapHeader + bitmapHeader->PixelOffset);
    
    return(result);
}

internal_function inline engine_mesh*
InitializeMesh(memory_block* block,
               s32 vertexCount, s32 triangleCount)
{
    engine_mesh* result = Memory_PushStruct(block, engine_mesh);
    result->VertexCount = vertexCount;
    result->TriangleCount = triangleCount;
    return(result);
}

internal_function inline void
CalculateNormals(engine_mesh* result)
{
    result->NormalCount = 0;
    //COMPUTER NORMALS
    for(s32 i = 0; i < result->TriangleCount; i += 3)
    {
        v3 vertex0 = result->Vertices[result->Triangles[i + 0]];
        v3 vertex1 = result->Vertices[result->Triangles[i + 1]];
        v3 vertex2 = result->Vertices[result->Triangles[i + 2]];
        
        v3 line1 = vertex1 - vertex0;
        v3 line2 = vertex2 - vertex0;
        v3 normal = CrossProduct(line1, line2);
        result->Normals[result->NormalCount++] = Normalized(normal);
    }
}

void
DEBUG_LoadOBJ(engine_mesh* mesh, engine_debug* debug,
              char* fileName)
{
    debug_platform_file file = debug->ReadEntireFile(fileName);
    s8* currentByte = 0;
    r32 x = 0;
    r32 y = 0;
    r32 z = 0;
    s32 triangle0 = 0;
    s32 triangle1 = 1;
    s32 triangle2 = 2;
    
    s8 vertexBuffer[3][256] = {};
    s8 triangleBuffer[3][256] = {};
    
    if(file.IsValid)
    {
        currentByte = (s8*)file.Contents;
        
        //for(s32 i = 0; i < file.FileSize; ++i)
        while(*currentByte != 0)
        {
            if((*currentByte == 'v') &&
               (*(currentByte + 1) == ' '))//VERTEX
            {
                currentByte += 2;
                s32 index = 0;
                s32 coordIndex = 0;
                while(*currentByte != '\n')
                {
                    vertexBuffer[coordIndex][index++] = *currentByte++;
                    if(*currentByte == ' ')
                    {
                        ++currentByte;
                        ++coordIndex;
                        index = 0;
                    }
                }
                
                x = ConvertString_R32(vertexBuffer[0]);
                y = ConvertString_R32(vertexBuffer[1]);
                z = ConvertString_R32(vertexBuffer[2]);
                mesh->Vertices[mesh->VertexCount++] = { x, y, z };
            }
            if((*currentByte == 'f') &&
               (*(currentByte + 1) == ' '))
            {
                currentByte += 2;
                s32 index = 0;
                s32 coordIndex = 0;
                while(*currentByte != '\n' && *currentByte != 0)
                {
                    triangleBuffer[coordIndex][index++] = *currentByte++;
                    if(*currentByte == ' ')
                    {
                        ++currentByte;
                        ++coordIndex;
                        index = 0;
                    }
                }
                
                // -1 IS DUE TO OBJ FILES INDEXED AT 1 (NOT 0)
                triangle0 = ConvertString_S32(triangleBuffer[0]) - 1;
                triangle1 = ConvertString_S32(triangleBuffer[1]) - 1;
                triangle2 = ConvertString_S32(triangleBuffer[2]) - 1;
                
                mesh->Triangles[mesh->TriangleCount++] = triangle0;
                mesh->Triangles[mesh->TriangleCount++] = triangle1;
                mesh->Triangles[mesh->TriangleCount++] = triangle2;
                
                v3 vertex0 = mesh->Vertices[triangle0];
                v3 vertex1 = mesh->Vertices[triangle1];
                v3 vertex2 = mesh->Vertices[triangle2];
                
                v3 line1 = vertex1 - vertex0;
                v3 line2 = vertex2 - vertex0;
                v3 normal = CrossProduct(line1, line2);
                mesh->Normals[mesh->NormalCount++] = Normalized(normal);
            }
            
            for(s32 i = 0; i < 256; ++i)
            {
                triangleBuffer[0][i] = 0;
                triangleBuffer[1][i] = 0;
                triangleBuffer[2][i] = 0;
                
                vertexBuffer[0][i] = 0;
                vertexBuffer[1][i] = 0;
                vertexBuffer[2][i] = 0;
            }
            ++currentByte;
        }
    }
}

internal_function inline void
GenerateQuadMesh(engine_mesh* result)
{
    //VERTICIES
    result->VertexCount = 4;
    result->Vertices[0] = { -0.5f, -0.5f, 0.5f };//0 - BL
    result->Vertices[1] = { -0.5f,  0.5f, 0.5f };//1 - TL
    result->Vertices[2] = {  0.5f,  0.5f, 0.5f };//2 - TR
    result->Vertices[3] = {  0.5f, -0.5f, 0.5f };//3 - BR
    //TRIANGLES
    result->TriangleCount = 6;
    result->Triangles[0] = 0;//0
    result->Triangles[1] = 2;
    result->Triangles[2] = 1;
    
    result->Triangles[3] = 0;//1
    result->Triangles[4] = 3;
    result->Triangles[5] = 2;
    
    CalculateNormals(result);
}

internal_function inline void
GeneratePlaneMesh(engine_mesh* result,
                  s32 width, s32 depth)
{
    result->VertexCount = ( (width + 1) * (depth + 1));
    result->TriangleCount = (6 * width * depth);
    s32 index = 0;
    for(s32 z = 0; z <= depth; ++z)
    {
        for(s32 x = 0; x <= width; ++x)
        {
            result->Vertices[index] =
            {
                (r32)x,
                0,
                (r32)-z,
            };
            ++index;
        }
    }
    
    s32 vertIndex = 0;
    s32 triangleIndex = 0;
    
    for(s32 z = 0; z < depth; ++z)
    {
        for(s32 x = 0; x < width; ++x)
        {
            result->Triangles[triangleIndex + 0] = vertIndex;
            result->Triangles[triangleIndex + 1] = vertIndex + 1;
            result->Triangles[triangleIndex + 2] = vertIndex + width + 1;
            
            result->Triangles[triangleIndex + 3] = vertIndex + width + 1;
            result->Triangles[triangleIndex + 4] = vertIndex + 1;
            result->Triangles[triangleIndex + 5] = vertIndex + width + 2;
            
            result->Normals[result->NormalCount++] = V3_UP;
            result->Normals[result->NormalCount++] = V3_UP;
            
            vertIndex++;
            triangleIndex += 6;
        }
        ++vertIndex;
    }
}

//TODO(stephen):BROKEN!!! NOT ALL TRIANLGES ARE IMPLEMENTED
//WIREFRAME WORKS, FILLED RENDERING DOES NOT
internal_function inline void
GenerateSphereMesh(engine_mesh* result,
                   s32 ringCount, s32 pointCount)
{
    r32 deltaTheta = (PI / (r32)(ringCount));
    r32 deltaPhi = (2.0f * PI / (r32)pointCount);
    r32 theta = 0;
    r32 phi = 0;
    result->VertexCount = (pointCount * (ringCount - 1) + 2);//PLUS 2 FOR POLAR POINTS
    result->TriangleCount = ((pointCount *  ringCount * 6) +
                             (ringCount * 3));
    s32 index = 0;
    result->Vertices[index++] = {0, 0, 1};
    
    for (s32 ring = 0; ring < ringCount - 1; ++ring)
    {
        theta += deltaTheta;
        for (s32 point = 0; point < pointCount; ++point)
        {
            phi += deltaPhi;
            r32 x = Sin(theta) * Cos(phi);
            r32 y = Sin(theta) * Sin(phi);
            r32 z = Cos(theta);
            
            result->Vertices[index++] = {x, y, z};
        }
    }
    
    result->Vertices[index] = {0, 0, -1};
    s32 vertexIndex = 0;
    s32 triangleIndex = 0;
    s32 vertexCountOffset = 0;
    s32 triangleIndexOffset = 0;
    
    for(s32 i = 0; i < pointCount * 3; i += 3)
    {
        triangleIndex = i;
        result->Triangles[triangleIndex + 0] = 0;
        result->Triangles[triangleIndex + 1] = vertexIndex + 1;
        result->Triangles[triangleIndex + 2] = vertexIndex + 2;
        
        triangleIndexOffset = result->TriangleCount - triangleIndex;
        vertexCountOffset = result->VertexCount - vertexIndex;
        result->Triangles[triangleIndexOffset - 1] = result->VertexCount - 1;
        result->Triangles[triangleIndexOffset - 2] = vertexCountOffset - 3;
        result->Triangles[triangleIndexOffset - 3] = vertexCountOffset - 2;
        
        ++vertexIndex;
    }
    
    result->Triangles[triangleIndex + 2] = 1;
    result->Triangles[triangleIndexOffset - 2] = result->VertexCount - 2;
    triangleIndex += 3;
    
    for(s32 ring = 0; ring < ringCount - 2; ++ring)
    {
        s32 currentRingPoint = pointCount * ring + 1;
        s32 nextRingPoint = pointCount * (ring + 1) + 1;
        
        for(s32 point = 0; point < pointCount; ++point)
        {
            s32 point1 = point + 1;
            
            result->Triangles[triangleIndex + 0] = currentRingPoint + point1;
            result->Triangles[triangleIndex + 1] = currentRingPoint + point;
            result->Triangles[triangleIndex + 2] = nextRingPoint + point;
            
            result->Triangles[triangleIndex + 3] = currentRingPoint + point;
            result->Triangles[triangleIndex + 4] = nextRingPoint + point1;
            result->Triangles[triangleIndex + 5] = nextRingPoint + point;
            
            triangleIndex += 3;
        }
    }
    
    CalculateNormals(result);
}

internal_function inline void
GenerateCubeMesh(engine_mesh* result)
{
    //VERTICIES
    result->VertexCount = 8;
    result->Vertices[0] = { -0.5f, -0.5f, 0.5f };//0 - BL
    result->Vertices[1] = { -0.5f,  0.5f, 0.5f };//1 - TL
    result->Vertices[2] = {  0.5f,  0.5f, 0.5f };//2 - TR
    result->Vertices[3] = {  0.5f, -0.5f, 0.5f };//3 - BR
    result->Vertices[4] = { -0.5f, -0.5f, -0.5f };//4 - BL
    result->Vertices[5] = { -0.5f,  0.5f, -0.5f };//5 - TL
    result->Vertices[6] = {  0.5f,  0.5f, -0.5f };//6 - TR
    result->Vertices[7] = {  0.5f, -0.5f, -0.5f };//7  - BR
    
    //TRIANGLES
    result->TriangleCount = 36;
    result->Triangles[0] = 0;//0
    result->Triangles[1] = 2;
    result->Triangles[2] = 1;
    result->Triangles[3] = 0;//1
    result->Triangles[4] = 3;
    result->Triangles[5] = 2;
    result->Triangles[6] = 3;//2
    result->Triangles[7] = 6;
    result->Triangles[8] = 2;
    result->Triangles[9] = 3;//3
    result->Triangles[10] = 7;
    result->Triangles[11] = 6;
    result->Triangles[12] = 7;//4
    result->Triangles[13] = 5;
    result->Triangles[14] = 6;
    result->Triangles[15] = 7;//5
    result->Triangles[16] = 4;
    result->Triangles[17] = 5;
    result->Triangles[18] = 4;//6
    result->Triangles[19] = 1;
    result->Triangles[20] = 5;
    result->Triangles[21] = 4;//7
    result->Triangles[22] = 0;
    result->Triangles[23] = 1;
    result->Triangles[24] = 1;//8
    result->Triangles[25] = 6;
    result->Triangles[26] = 5;
    result->Triangles[27] = 1;//9
    result->Triangles[28] = 2;
    result->Triangles[29] = 6;
    result->Triangles[30] = 4;//10
    result->Triangles[31] = 3;
    result->Triangles[32] = 0;
    result->Triangles[33] = 4;//11
    result->Triangles[34] = 7;
    result->Triangles[35] = 3;
    
    CalculateNormals(result);
}

internal_function inline void
GenerateTruncatedPyramidMesh(engine_mesh* result)
{
    //VERTICIES
    result->VertexCount = 8;
    result->Vertices[0] = { -0.5f, -0.5f, 0.5f };//0 - FBL
    result->Vertices[1] = { -0.25f,  0.5f, 0.25f };//1 - FTL
    
    result->Vertices[2] = {  0.25f,  0.5f, 0.25f };//2 - FTR
    result->Vertices[3] = {  0.5f, -0.5f, 0.5f };//3 - FBR
    
    result->Vertices[4] = { -0.5f, -0.5f, -0.5f };//4 - BBL
    result->Vertices[5] = { -0.25f,  0.5f, -0.25f };//5 - BTL
    
    result->Vertices[6] = {  0.25f,  0.5f, -0.25f };//6 - BTR
    result->Vertices[7] = {  0.5f, -0.5f, -0.5f };//7  - BBR
    
    //TRIANGLES
    result->TriangleCount = 36;
    result->Triangles[0] = 0;//0
    result->Triangles[1] = 2;
    result->Triangles[2] = 1;
    result->Triangles[3] = 0;//1
    result->Triangles[4] = 3;
    result->Triangles[5] = 2;
    result->Triangles[6] = 3;//2
    result->Triangles[7] = 6;
    result->Triangles[8] = 2;
    result->Triangles[9] = 3;//3
    result->Triangles[10] = 7;
    result->Triangles[11] = 6;
    result->Triangles[12] = 7;//4
    result->Triangles[13] = 5;
    result->Triangles[14] = 6;
    result->Triangles[15] = 7;//5
    result->Triangles[16] = 4;
    result->Triangles[17] = 5;
    result->Triangles[18] = 4;//6
    result->Triangles[19] = 1;
    result->Triangles[20] = 5;
    result->Triangles[21] = 4;//7
    result->Triangles[22] = 0;
    result->Triangles[23] = 1;
    result->Triangles[24] = 1;//8
    result->Triangles[25] = 6;
    result->Triangles[26] = 5;
    result->Triangles[27] = 1;//9
    result->Triangles[28] = 2;
    result->Triangles[29] = 6;
    result->Triangles[30] = 4;//10
    result->Triangles[31] = 3;
    result->Triangles[32] = 0;
    result->Triangles[33] = 4;//11
    result->Triangles[34] = 7;
    result->Triangles[35] = 3;
    
    CalculateNormals(result);
}

//////////////////////////////// ENTRY POINT ////////////////////////////////

inline void
InitializeCamera(engine_camera* camera,
                 v3 worldPosition,
                 v3 eulerRotation,
                 r32 nearClipping,
                 r32 farClipping,
                 r32 fieldOfView,
                 s32 screenLeft,
                 s32 screenRight,
                 s32 screenTop,
                 s32 screenBottom)
{
    camera->WorldPosition = worldPosition;
    camera->EulerRotation = eulerRotation;
    
    camera->NearClipping = nearClipping;
    camera->FarClipping = farClipping;
    camera->FieldOfView = fieldOfView;
    camera->ScreenLeft = screenLeft;
    camera->ScreenRight = screenRight;
    camera->ScreenTop = screenTop;
    camera->ScreenBottom = screenBottom;
    
    camera->ViewWidth = (screenRight - screenLeft);
    camera->ViewHeight = (screenBottom - screenTop);
    
    //TODO:IMPLEMENT Z ROTATION
    camera->ViewMatrix = M4x4_FPSViewMatrix(worldPosition, eulerRotation.X, eulerRotation.Y);
    camera->LocalRight = Normalized({
                                        camera->ViewMatrix.E[0][0],
                                        camera->ViewMatrix.E[0][1],
                                        camera->ViewMatrix.E[0][2]
                                    });
    
    camera->LocalUp = Normalized(
                                 {
                                     camera->ViewMatrix.E[1][0],
                                     camera->ViewMatrix.E[1][1],
                                     camera->ViewMatrix.E[1][2]
                                 });
    
    camera->LocalForward = Normalized(
                                      {
                                          camera->ViewMatrix.E[2][0],
                                          camera->ViewMatrix.E[2][1],
                                          camera->ViewMatrix.E[2][2]
                                      });
    
    camera->ProjectionMatrix = M4x4_GetPerspectiveMatrix(screenLeft,
                                                         screenRight,
                                                         screenTop,
                                                         screenBottom,
                                                         fieldOfView,
                                                         nearClipping,
                                                         farClipping);
}

ENGINE_UPDATE(EngineUpdate)
{
    local_persist r32 elapsedTimer = 0;
    elapsedTimer += time->DeltaTime;
    engine_state* state = (engine_state*)memory->PermanentMemory;
    engine_input_controller* keyBoard = &input->KeyBoard;
    engine_input_mouse* mouse = &input->Mouse;
    
    v2 bufferCenter = { buffer->Width * 0.5f, buffer->Height * 0.5f };
    
    //INITIALIZE MEMORY
    if(memory->IsInitialized == FALSE)
    {
        Debug = debug;
        //PLAYER CAMERA
        InitializeCamera(&state->Camera,
                         V3_ZERO,
                         V3_ZERO,
                         0.1f, 1000.0f,
                         45.0f,
                         0, buffer->Width,
                         0, buffer->Height);
        
        //INITIALIZE MEMORY
        InitializeMemoryBlock(&state->WorldMemory,
                              (memory->PermanentMemorySize - sizeof(engine_state)),
                              ((u8*)memory->PermanentMemory + sizeof(engine_state)));
        
        InitializeRenderGroup(&state->WorldMemory,
                              worldRenderGroup,
                              KILOBYTE(1));
        
        //INITIALIZE PRIMITIVE GEOMETRY
        state->Primitives = Memory_PushStruct(&state->WorldMemory, engine_primitives);
        //GenerateSphereMesh(&state->Primitives->Sphere, 50, 50);//TODO(stephen):BROKEN!!!
        GenerateSphereMesh(&state->Sphere, 50, 50);
        GeneratePlaneMesh(&state->Primitives->Plane, 100, 100);
        GenerateCubeMesh(&state->Primitives->Cube);
        GenerateQuadMesh(&state->Primitives->Quad);
        GenerateTruncatedPyramidMesh(&state->Primitives->TruncatedPyramid);
        
        //LOAD DEBUG TEXT SHEET
        state->DebugTextBitmap = DEBUG_LoadBMP(debug->ReadEntireFile,
                                               "./testAssets/DEBUG_TEXT.bmp");
        
        state->TestBitmap = DEBUG_LoadBMP(debug->ReadEntireFile,
                                          "./testAssets/tile_stoneBlock00_64.bmp");
        
        //LOAD MESHES
        DEBUG_LoadOBJ(&state->Primitives->Sphere, debug, "./testAssets/sphere.obj");
        DEBUG_LoadOBJ(&state->Primitives->Axis, debug, "./testAssets/axis.obj");
        DEBUG_LoadOBJ(&state->LoadedMesh, debug, "./testAssets/house1.obj");
        DEBUG_LoadOBJ(&state->AirplaneMesh, debug, "./testAssets/airplane.obj");
        DEBUG_LoadOBJ(&state->Sun, debug, "./testAssets/lightSource.obj");
        DEBUG_LoadOBJ(&state->Tank, debug, "./testAssets/tank.obj");
        
        state->RenderMode = RENDER_MODE_WIRE;
        memory->IsInitialized = TRUE;
    }
    
    //PROCESS INPUT
    v3 cameraMovement = {};
    v3 cameraRotation = {};
    r32 cameraMovementSpeed = 16.0f;
    if(keyBoard->A.IsDown) { cameraMovement -= state->Camera.LocalRight; }
    if(keyBoard->D.IsDown) { cameraMovement += state->Camera.LocalRight; }
    if(keyBoard->S.IsDown) { cameraMovement += state->Camera.LocalForward; }
    if(keyBoard->W.IsDown) { cameraMovement -= state->Camera.LocalForward; }
    if(keyBoard->Q.IsDown) { cameraMovement += state->Camera.LocalUp; }
    if(keyBoard->E.IsDown) { cameraMovement -= state->Camera.LocalUp; }
    
    // HACK(Stephen): TEMP TOGGLE OF RENDER MODES
    if(keyBoard->Num1.WasDown) { state->RenderMode ^= RENDER_MODE_WIRE; }
    if(keyBoard->Num2.WasDown)
    {
        if(state->RenderMode & RENDER_MODE_SHADED)
            state->RenderMode ^= RENDER_MODE_SHADED;
        else
            state->RenderMode ^= RENDER_MODE_SOLID;
    }
    if(keyBoard->Num3.WasDown)
    {
        state->RenderMode |= RENDER_MODE_SOLID;
        state->RenderMode ^= RENDER_MODE_SHADED;
    }
    if(keyBoard->Num4.WasDown) { state->RenderMode ^= RENDER_MODE_NORMALS; }
    if(keyBoard->Num5.WasDown) { state->RenderMode ^= RENDER_MODE_LIGHT_RAY; }
    if(keyBoard->Num5.IsDown) { }
    if(keyBoard->Left.IsDown) { cameraRotation.Y = 1.0f; }
    if(keyBoard->Right.IsDown) { cameraRotation.Y = -1.0f; }
    if(keyBoard->Up.IsDown) { cameraRotation.X = 0.5f; }
    if(keyBoard->Down.IsDown) { cameraRotation.X = -0.5f; }
    if(keyBoard->Space.IsDown) { }
    if(keyBoard->Escape.IsDown) { }
    if(mouse->Left.IsDown) {}
    if(mouse->Right.IsDown) {}
    
    //CAMERA MOVEMENT
    Normalize(&cameraMovement);
    state->Camera.WorldPosition += (cameraMovement * cameraMovementSpeed * time->DeltaTime);
    state->Camera.EulerRotation += (cameraRotation * 1 * time->DeltaTime);
    
    //CAMERA MATRIX
    state->Camera.ViewMatrix = M4x4_FPSViewMatrix(state->Camera.WorldPosition,
                                                  state->Camera.EulerRotation.X,
                                                  state->Camera.EulerRotation.Y);
    
    //GET CAMERA BASIS
    state->Camera.LocalRight = Normalized(*(v3*)state->Camera.ViewMatrix.E[0]);
    state->Camera.LocalUp = Normalized(*(v3*)state->Camera.ViewMatrix.E[1]);
    state->Camera.LocalForward = Normalized(*(v3*)state->Camera.ViewMatrix.E[2]);
    
    state->LightSource.Color = {1.0f, 1.0f, 1.0f, 1.0f};
    state->LightSource.WorldPosition = {25, 10, -25};
    state->LightSource.WorldPosition.Z = -50;//(0.5f + 0.5f * Sin(elapsedTimer)) * -100.0f;
    state->LightSource.Intensity = 1.0f;
    
    //////////////////////////////// RENDERING
    
    worldRenderGroup->Camera = &state->Camera;
    worldRenderGroup->WorldMatrix = M4x4_Identity();
    worldRenderGroup->RenderMode = state->RenderMode;
    
    Render_ClearRenderGroup(worldRenderGroup);
    Render_PushClear(worldRenderGroup, {1, 0.1f, 0.1f, 0.2f});
    
    
    v3 meshPosition = { -10, -10, -10 };
    v4 meshColor = {1, 1, 1, 1};
    v3 meshScale = { 1, 1, 1 };
    v3 meshRotation = {};
    
#if 0
    //RENDER PLANE
    engine_mesh* plane = &state->Primitives->Plane;
    
    for(s32 i = 0; i < plane->VertexCount; ++i)
    {
        v3 vertex = plane->Vertices[i];
        r32 height = PerlinNoise3D(vertex.X + elapsedTimer,
                                   vertex.Y,
                                   vertex.Z + elapsedTimer,
                                   0.1f,
                                   2,
                                   0.5f,
                                   4);
        
        vertex.Y = height * 3;
        
        plane->Vertices[i] = vertex;
    }
    
    CalculateNormals(plane);
    
    Render_PushMesh(worldRenderGroup,
                    plane,
                    &state->LightSource,
                    state->RenderMode,
                    meshPosition,
                    meshScale,
                    meshRotation,
                    meshColor);
    
#else
    
    
    Render_PushMesh(worldRenderGroup,
                    &state->AirplaneMesh,
                    &state->LightSource,
                    state->RenderMode,
                    meshPosition,
                    meshScale,
                    meshRotation,
                    meshColor);
    
#endif
    
    
#if 0
    //RENDER BITMAP
    v2 bitmapPosition = bufferCenter;
    Render_PushBitmap(worldRenderGroup, state->DebugTextBitmap, bitmapPosition);
    
    //RENDER 2D LINE
    v2 linePoints[2] =
    {
        bufferCenter,
        { bufferCenter.X + (Cos(elapsedTimer) * 1000.0f),
            bufferCenter.Y + (Sin(elapsedTimer)  * 1000.0f)}
    };
    v4 lineColor = { 1, 1, 0, 1 };
    Render_PushLine2D(worldRenderGroup,
                      linePoints[0],
                      linePoints[1],
                      lineColor);
    
    //RENDER RECTANGLE
    v2 rectPosition = { 128, 128 };
    v2 rectDimentions = { 64, 64 };
    v4 rectColor = { 1, 0.7f, 0.3f, 0.3f };
    Render_PushRectangle(worldRenderGroup, rectPosition, rectDimentions, rectColor);
#endif
    
}