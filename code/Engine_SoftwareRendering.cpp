
#include "Engine_Math.cpp"

internal_function void
DEBUG_RenderText_UNSAFE(engine_buffer* buffer,
                        engine_bitmap* debugTextSheet,
                        s32 characterWidth,
                        s32 characterHeight,
                        v2 position,
                        char* outText,
                        v3 color)
{
    char* currentLetter = outText;
    s32 characterLeft = 0;
    s32 characterTop = 0;
    s32 characterCount = 0;
    characterHeight += 1;
    
    s32 xMin = Round_R32ToS32(position.X);
    s32 yMin = Round_R32ToS32(position.Y);
    
    if(xMin < 0)
    {
        xMin = 0;
    }
    if(yMin < 0)
    {
        yMin = 0;
    }
    
    while(*currentLetter)
    {
        switch(*currentLetter)
        {
            case 'a':
            case 'A':
            {
                characterLeft = 0;
                characterTop = 0;
            }break;
            case 'B':
            case 'b':
            {
                characterLeft = characterWidth;
                characterTop = 0;
            }break;
            case 'C':
            case 'c':
            {
                characterLeft = characterWidth * 2;
                characterTop = 0;
            }break;
            case 'D':
            case 'd':
            {
                characterLeft = characterWidth * 3;
                characterTop = 0;
            }break;
            case 'E':
            case 'e':
            {
                characterLeft = characterWidth * 4;
                characterTop = 0;
            }break;
            case 'F':
            case 'f':
            {
                characterLeft = characterWidth * 5;
                characterTop = 0;
            }break;
            case 'G':
            case 'g':
            {
                characterLeft = characterWidth * 6;
                characterTop = 0;
            }break;
            case 'H':
            case 'h':
            {
                characterLeft = characterWidth * 7;
                characterTop = 0;
            }break;
            case 'I':
            case 'i':
            {
                characterLeft = characterWidth * 8;
                characterTop = 0;
            }break;
            case 'J':
            case 'j':
            {
                characterLeft = characterWidth * 9;
                characterTop = 0;
            }break;
            case 'K':
            case 'k':
            {
                characterLeft = characterWidth * 10;
                characterTop = 0;
            }break;
            case 'L':
            case 'l':
            {
                characterLeft = characterWidth * 11;
                characterTop = 0;
            }break;
            case 'M':
            case 'm':
            {
                characterLeft = characterWidth * 12;
                characterTop = 0;
            }break;
            case 'N':
            case 'n':
            {
                characterLeft = characterWidth * 13;
                characterTop = 0;
            }break;
            case 'O':
            case 'o':
            {
                characterLeft = characterWidth * 14;
                characterTop = 0;
            }break;
            case 'P':
            case 'p':
            {
                characterLeft = characterWidth * 15;
                characterTop = 0;
            }break;
            case 'Q':
            case 'q':
            {
                characterLeft = 0;
                characterTop = characterHeight;
            }break;
            case 'R':
            case 'r':
            {
                characterLeft = characterWidth;
                characterTop = characterHeight;
            }break;
            case 'S':
            case 's':
            {
                characterLeft = characterWidth * 2;
                characterTop = characterHeight;
            }break;
            case 'T':
            case 't':
            {
                characterLeft = characterWidth * 3;
                characterTop = characterHeight;
            }break;
            case 'U':
            case 'u':
            {
                characterLeft = characterWidth * 4;
                characterTop = characterHeight;
            }break;
            case 'V':
            case 'v':
            {
                characterLeft = characterWidth * 5;
                characterTop = characterHeight;
            }break;
            case 'W':
            case 'w':
            {
                characterLeft = characterWidth * 6;
                characterTop = characterHeight;
            }break;
            case 'X':
            case 'x':
            {
                characterLeft = characterWidth * 7;
                characterTop = characterHeight;
            }break;
            case 'Y':
            case 'y':
            {
                characterLeft = characterWidth * 8;
                characterTop = characterHeight;
            }break;
            case 'Z':
            case 'z':
            {
                characterLeft = characterWidth * 9;
                characterTop = characterHeight;
            }break;
            case '0':
            {
                characterLeft = characterWidth * 10;
                characterTop = characterHeight;
            }break;
            case '1':
            {
                characterLeft = characterWidth * 11;
                characterTop = characterHeight;
            }break;
            case '2':
            {
                characterLeft = characterWidth * 12;
                characterTop = characterHeight;
            }break;
            case '3':
            {
                characterLeft = characterWidth * 13;
                characterTop = characterHeight;
            }break;
            case '4':
            {
                characterLeft = characterWidth * 14;
                characterTop = characterHeight;
            }break;
            case '5':
            {
                characterLeft = characterWidth * 15;
                characterTop = characterHeight;
            }break;
            case '6':
            {
                characterLeft = 0;
                characterTop = characterHeight * 2;
            }break;
            case '7':
            {
                characterLeft = characterWidth;
                characterTop = characterHeight * 2;
            }break;
            case '8':
            {
                characterLeft = characterWidth * 2;
                characterTop = characterHeight * 2;
            }break;
            case '9':
            {
                characterLeft = characterWidth * 3;
                characterTop = characterHeight * 2;
            }break;
            case '.':
            {
                characterLeft = characterWidth * 4;
                characterTop = characterHeight * 2;
            }
            break;
            default:
            {
                characterLeft = 0;
                characterTop = debugTextSheet->Height / 2;
            }break;
        }
        
        u8* destinationRow = ((u8*)buffer->Memory +
                              (buffer->Pitch * yMin) +
                              (xMin * buffer->BytesPerPixel) +
                              (characterCount * characterWidth * 4));
        
        u32* sourceRow = ((debugTextSheet->Pixels +
                           (debugTextSheet->Width * debugTextSheet->Height - 1)) +
                          characterLeft -
                          (characterTop * debugTextSheet->Height));
        ++currentLetter;
        ++characterCount;
        
        //NOTE(stephen):GREATER <= MAY CAUSE PROBLEMS!!!
        for(s32 i = 0; i <= characterHeight; i++)
        {
            u32* source = sourceRow;
            u32* destination = (u32*)destinationRow;
            
            for(s32 j = 0; j < characterWidth; j++)
            {
                r32 sourceAlpha = (r32)(ALPHA_CHANNEL(*source) / 255.0f);
                r32 sourceRed = (r32)RED_CHANNEL(*source);
                r32 sourceGreen = (r32)GREEN_CHANNEL(*source);
                r32 sourceBlue = (r32)BLUE_CHANNEL(*source);
                
                r32 destinationRed = (r32)RED_CHANNEL(*destination);
                r32 destinationGreen = (r32)GREEN_CHANNEL(*destination);
                r32 destinationBlue = (r32)BLUE_CHANNEL(*destination);
                
                r32 red = Lerp(sourceAlpha, destinationRed, sourceRed);
                r32 green = Lerp(sourceAlpha, destinationGreen, sourceGreen);
                r32 blue = Lerp(sourceAlpha, destinationBlue, sourceBlue);
                
                *destination = ((Round_R32ToU32(red * color.R) << 16) |
                                (Round_R32ToU32(green * color.G) << 8) |
                                (Round_R32ToU32(blue * color.B) << 0));
                ++destination;
                ++source;
            }
            sourceRow -= debugTextSheet->Width;
            destinationRow += buffer->Pitch;
        }
    }//while(*currentLetter)
}

internal_function void
DrawBitmap(engine_buffer* buffer,
           engine_bitmap* bitmap,
           v2 position,
           v2 offset = V2_ZERO)
{
    position -= offset;
    local_persist r32 invert255 = (1.0f / 255);
    s32 xMin = Round_R32ToS32(position.X);
    s32 xMax = Round_R32ToS32(position.X + (r32)bitmap->Width);
    s32 yMin = Round_R32ToS32(position.Y);
    s32 yMax = Round_R32ToS32(position.Y + (r32)bitmap->Height);
    s32 bitmapOffsetX = 0;
    s32 bitmapOffsetY = 0;
    u32* sourceRow;
    u8* destinationRow;
    
    if(xMin < 0)
    {
        bitmapOffsetX = -xMin;
        xMin = 0;
    }
    if(yMin < 0)
    {
        bitmapOffsetY = -yMin;
        yMin = 0;
    }
    if(xMax > buffer->Width)
    {
        xMax = buffer->Width;
    }
    if(yMax > buffer->Height)
    {
        yMax = buffer->Height;
    }
    
    sourceRow = (bitmap->Pixels +
                 (bitmap->Width * (bitmap->Height - 1)));//TODO: DO WE NEED -1 HEIGHT??
    sourceRow += ((-bitmap->Width * bitmapOffsetY) + bitmapOffsetX);
    
    destinationRow = ((u8*)buffer->Memory +
                      (buffer->Pitch * yMin) +
                      (xMin * buffer->BytesPerPixel));
    
    for(s32 y = yMin; y < yMax; ++y)
    {
        u32* source = sourceRow;
        u32* destination = (u32*)destinationRow;
        for(s32 x = xMin; x < xMax; ++x)
        {
            
#if 1//ALPHA BLENDING
            r32 sourceAlpha = (r32)(ALPHA_CHANNEL(*source) * invert255);
            r32 sourceRed = (r32)RED_CHANNEL(*source);
            r32 sourceGreen = (r32)GREEN_CHANNEL(*source);
            r32 sourceBlue = (r32)BLUE_CHANNEL(*source);
            
            r32 destinationRed = (r32)RED_CHANNEL(*destination);
            r32 destinationGreen = (r32)GREEN_CHANNEL(*destination);
            r32 destinationBlue = (r32)BLUE_CHANNEL(*destination);
            
            r32 red = Lerp(sourceAlpha, destinationRed, sourceRed);
            r32 green = Lerp(sourceAlpha, destinationGreen, sourceGreen);
            r32 blue = Lerp(sourceAlpha, destinationBlue, sourceBlue);
            
            *destination = ((Round_R32ToU32(red) << 16) |
                            (Round_R32ToU32(green) << 8) |
                            (Round_R32ToU32(blue) << 0));
#else
            *destination = *source;
#endif
            
            ++destination;
            ++source;
        }
        
        sourceRow -= bitmap->Width;
        destinationRow += buffer->Pitch;
    }
}

// NOTE(Stephen): SIMD THIS!!! ROUTINE IS SLOW!!!!
//DRAWS ROTATED AND SCALED BITMAPS WITH UV MAPPING
internal_function void
DrawRectangleSlowly(engine_buffer* buffer,
                    engine_buffer* colorMap,// TODO(Stephen): CHANGE COLOR_MAP TYPE TO ENGINE_BITMAP
                    engine_buffer* normalMap,// TODO(Stephen): CHANGE NORMAL_MAP TYPE TO ENGINE_BITMAP
                    v2 orgin,
                    v2 axisX,
                    v2 axisY,
                    v4 color)
{
    u32* pixel = 0;
    u8* row = 0;
    r32 invertedLengthSquaredX = 1.0f / LengthSquared(axisX);
    r32 invertedLengthSquaredY = 1.0f / LengthSquared(axisY);
    s32 left = buffer->Width;
    s32 top = buffer->Height;
    s32 right = 0;
    s32 bottom = 0;
    v2 xAxis = orgin + axisX;
    v2 yAxis = orgin + axisY;
    v2 point = orgin + axisX + axisY;
    
    //SET BOUNDING BOX AROUND ROTATED BITMAP
    
    left = Floor_R32ToS32(Min_R32(left, orgin.X));
    left = Floor_R32ToS32(Min_R32(left, xAxis.X));
    left = Floor_R32ToS32(Min_R32(left, yAxis.X));
    left = Floor_R32ToS32(Min_R32(left, point.X));
    
    top = Floor_R32ToS32(Min_R32(top, orgin.Y));
    top = Floor_R32ToS32(Min_R32(top, xAxis.Y));
    top = Floor_R32ToS32(Min_R32(top, yAxis.Y));
    top = Floor_R32ToS32(Min_R32(top, point.Y));
    
    right = Ceiling_R32ToS32(Max_R32(right, orgin.X));
    right = Ceiling_R32ToS32(Max_R32(right, xAxis.X));
    right = Ceiling_R32ToS32(Max_R32(right, yAxis.X));
    right = Ceiling_R32ToS32(Max_R32(right, point.X));
    
    bottom = Ceiling_R32ToS32(Max_R32(bottom, orgin.Y));
    bottom = Ceiling_R32ToS32(Max_R32(bottom, xAxis.Y));
    bottom = Ceiling_R32ToS32(Max_R32(bottom, yAxis.Y));
    bottom = Ceiling_R32ToS32(Max_R32(bottom, point.Y));
    
    //BOUNDS CHECKING
    
    if(left < 0)
        left = 0;
    if(right > buffer->Width)
        right = buffer->Width;
    
    if(top < 0)
        top = 0;
    if(bottom > buffer->Height)
        bottom = buffer->Height;
    
    //LOCATE PIXEL TO DRAW TO
    
    row = ((u8*)buffer->Memory +
           (left * buffer->BytesPerPixel) +
           (top * buffer->Pitch));
    
    //PREMULTIPLY ALPHA COLOR
    color.R *= color.A;
    color.G *= color.A;
    color.B *= color.A;
    
    axisX *= invertedLengthSquaredX;
    axisY *= invertedLengthSquaredY;
    
    for(s32 y = top; y < bottom; ++y)
    {
        pixel = (u32*)row;
        
        v2 insidePoint;
        insidePoint.Y = y;
        
        for(s32 x = left; x < right; ++x)
        {
            insidePoint.X = x;
            v2 distance = (insidePoint - orgin);
            
            v2 uv =
            {
                DotProduct(distance, axisX),
                DotProduct(distance, axisY),
            };
            
            if(uv.X >= 0 && uv.Y >= 0 &&
               uv.X <= 1.0f && uv.Y <= 1.0f)
            {
                r32 texelRX = uv.X * (colorMap->Width - 1);
                r32 texelRY = uv.Y * (colorMap->Height - 1);
                
                s32 texelX = Truncate_R32ToS32(texelRX);
                s32 texelY = Truncate_R32ToS32(texelRY);
                
                u8* texelPtr = ((u8*)colorMap->Memory +
                                texelY * colorMap->Pitch +
                                texelX * colorMap->BytesPerPixel);
                
                u32 texelU32 = *((u32*)texelPtr);
                v4 texel = Unpack4x8_V4(texelU32) * INVERSE_255;
                
                if(texel.A > 0)
                {
                    u8* normalPtr = ((u8*)normalMap->Memory +
                                     texelY * normalMap->Pitch +
                                     texelX * normalMap->BytesPerPixel);
                    
                    u32 normalU32 = *((u32*)normalPtr);
                    v4 normal = Unpack4x8_V4(normalU32);
                    
                    r32 texelEnvMap = normal.Z;
                    r32 texelFarMap;
                    
                    texel = HadamardProduct(texel, color);
                    
                    v4 destination = Unpack4x8_V4(*pixel) * INVERSE_255;
                    
                    v4 blended = ((1.0f - texel.A) * destination) + texel;
                    
                    *pixel = Pack4x8_U32_255(blended);
                }
            }
            
            ++pixel;
        }//for(s32 x = left; x < right; ++x)
        
        row += buffer->Pitch;
        
    }//for(s32 y = top; y < bottom; ++y)
}

inline s32
CohenSutherLandCode(r32 x, r32 y,
                    r32 xMin, r32 xMax,
                    r32 yMin, r32 yMax)
{
#define COHEN_INSIDE 0x0000
#define COHEN_LEFT 0x0001
#define COHEN_RIGHT 0x0002
#define COHEN_BOTTOM 0x0004
#define COHEN_TOP 0x0008
    
    s32 result = COHEN_INSIDE;
    if(x < xMin)
        result = (result | COHEN_LEFT);
    else if(x > xMax)
        result = (result | COHEN_RIGHT);
    
    if(y < yMin)
        result = (result | COHEN_BOTTOM);
    else if(y > yMax)
        result = (result | COHEN_TOP);
    
    return(result);
}

// TODO(Stephen): NEED 3-DIMENSIONAL CLIPPING
//CURRENTLY ONLY 2-DIMENSIONS HANDLED
b32
CohenSutherlandLineClip(r32* x0, r32* y0,
                        r32* x1, r32* y1,
                        r32 xMin, r32 xMax,
                        r32 yMin, r32 yMax)
{
    b32 result = FALSE;
    s32 cohenCode0 = CohenSutherLandCode(*x0, *y0, xMin, xMax, yMin, yMax);
    s32 cohenCode1 = CohenSutherLandCode(*x1, *y1, xMin, xMax, yMin, yMax);
    r32 deltaX = 0;
    r32 deltaY = 0;
    s32 testCode = 0;
    
    //TODO: MAKE SURE THIS DOES NOT HINDER PERFORMANCE
    while(TRUE)
    {
        if(!(cohenCode0 | cohenCode1))
        {
            result = TRUE;
            break;
        }
        else if(cohenCode0 & cohenCode1)
        {
            break;
        }
        else
        {
            testCode = cohenCode0 ? cohenCode0 : cohenCode1;
            
            if(testCode & COHEN_TOP)
            {
                deltaX = *x0 + (*x1 - *x0) * (yMax - *y0) / (*y1 - *y0);
                deltaY = yMax;
            }
            else if(testCode & COHEN_BOTTOM)
            {
                deltaX = *x0 + (*x1 - *x0) * (yMin - *y0) / (*y1 - *y0);
                deltaY = yMin;
            }
            else if(testCode & COHEN_RIGHT)
            {
                deltaY = *y0 + (*y1 - *y0) * (xMax - *x0) / (*x1 - *x0);
                deltaX = xMax;
            }
            else if(testCode & COHEN_LEFT)
            {
                deltaY = *y0 + (*y1 - *y0) * (xMin - *x0) / (*x1 - *x0);
                deltaX = xMin;
            }
            
            if(testCode == cohenCode0)
            {
                *x0 = deltaX;
                *y0 = deltaY;
                cohenCode0 = CohenSutherLandCode(*x0, *y0, xMin, xMax, yMin, yMax);
            }
            else
            {
                *x1 = deltaX;
                *y1 = deltaY;
                cohenCode1 = CohenSutherLandCode(*x1, *y1, xMin, xMax, yMin, yMax);
            }
        }
    }
    
    return(result);
}

internal_function void
DrawRectangle(engine_buffer* buffer,
              v2 upperLeft,
              v2 lowerRight,
              v4 colorR32)
{
    u32* pixel = 0;
    u8* row = 0;
    s32 minX = Round_R32ToS32(upperLeft.X);
    s32 minY = Round_R32ToS32(upperLeft.Y);
    s32 maxX = Round_R32ToS32(lowerRight.X);
    s32 maxY = Round_R32ToS32(lowerRight.Y);
    
    r32 sourceRed = (r32)Round_R32ToU32(colorR32.R * 255.0f);
    r32 sourceGreen = (r32)Round_R32ToU32(colorR32.G * 255.0f);
    r32 sourceBlue = (r32)Round_R32ToU32(colorR32.B * 255.0f);
    
    if(minX < 0)
        minX = 0;
    if(maxX > buffer->Width)
        maxX = buffer->Width;
    if(minY < 0)
        minY = 0;
    if(maxY > buffer->Height)
        maxY = buffer->Height;
    
    row = ((u8*)buffer->Memory +
           (buffer->Pitch * minY) +
           (minX * buffer->BytesPerPixel));
    
    for(s32 y = minY; y < maxY; ++y)
    {
        pixel = (u32*)row;
        
        for(s32 x = minX; x < maxX; ++x)
        {
            //ALPHA BLENDING
            r32 destinationRed = (r32)RED_CHANNEL(*pixel);
            r32 destinationGreen = (r32)GREEN_CHANNEL(*pixel);
            r32 destinationBlue = (r32)BLUE_CHANNEL(*pixel);
            
            r32 r = Lerp(colorR32.A, destinationRed, sourceRed);
            r32 g = Lerp(colorR32.A, destinationGreen, sourceGreen);
            r32 b = Lerp(colorR32.A, destinationBlue, sourceBlue);
            
            *pixel++ = ((Round_R32ToU32(r) << 16) |
                        (Round_R32ToU32(g) << 8) |
                        (Round_R32ToU32(b)));
        }
        row += buffer->Pitch;
    }
}

internal_function inline void
DrawLine2D(engine_buffer* buffer,
           v2 point1,
           v2 point2,
           v4 colorR32)
{
    if(CohenSutherlandLineClip(&point1.X, &point1.Y,
                               &point2.X, &point2.Y,
                               0, buffer->Width,
                               0, buffer->Height))
    {
        
        u32* pixel = (u32*)buffer->Memory;
        s32 x0 = Truncate_R32ToS32(point1.X);
        s32 y0 = Truncate_R32ToS32(point1.Y);
        s32 x1 = Truncate_R32ToS32(point2.X);
        s32 y1 = Truncate_R32ToS32(point2.Y);
        u32 color = ((Round_R32ToU32(colorR32.A * 255.0f) << 24) |
                     (Round_R32ToU32(colorR32.R * 255.0f) << 16) |
                     (Round_R32ToU32(colorR32.G * 255.0f) << 8) |
                     (Round_R32ToU32(colorR32.B * 255.0f) << 0));
        
        r32 deltaX = (r32)(x1 - x0);
        r32 deltaY = (r32)(y1 - y0);
        s32 steps = 0;
        
        if(Abs_R32(deltaX) > Abs_R32(deltaY))
        {
            steps = (s32)Abs_R32(deltaX);
        }
        else
        {
            steps = (s32)Abs_R32(deltaY);
        }
        
        r32 xIncrement = (deltaX / (r32)steps);
        r32 yIncrement = (deltaY / (r32)steps);
        
        r32 x = (r32)x0;
        r32 y = (r32)y0;
        
        for(s32 i = 0; i <= steps; ++i)
        {
            s32 positionX = Truncate_R32ToS32(x);
            s32 positionY = Truncate_R32ToS32(y);
            
            ASSERT((IsClamped_S32(positionX, 0, buffer->Width) &&
                    IsClamped_S32(positionY, 0, buffer->Height)))
                
                
#if 0       // TODO(Stephen): ALPHA BLENDING DISABLED DUE TO PERFORMANCE HIT
            //NEED TO IMPLEMENT WITH SIMD
            u32 bufferPixel = pixel[positionY * buffer->Width + positionX];
            
            r32 bufferRed =   ((bufferPixel >> 16) & 0xFF);
            r32 bufferGreen = ((bufferPixel >> 8)  & 0xFF);
            r32 bufferBlue =  ((bufferPixel >> 0)  & 0xFF);
            
            u32 red = Round_R32ToU32(Lerp(colorR32.A, bufferRed, colorR32.R * 255.0f));
            u32 green = Round_R32ToU32(Lerp(colorR32.A, bufferGreen, colorR32.G * 255.0f));
            u32 blue = Round_R32ToU32(Lerp(colorR32.A, bufferBlue, colorR32.B * 255.0f));
            
            color = 0;
            color = ((red << 16) | (green << 8) | (blue << 0));
#endif
            
            pixel[positionY * buffer->Width + positionX] = color;
            
            x += xIncrement;
            y += yIncrement;
            
        }//for(s32 i = 0; i <= steps; ++i)
    }//if(CohenSutherlandLineClip)
}


void
DrawLine3D(engine_buffer* buffer,
           m4x4* worldMatrix,
           engine_camera* camera,
           v3* vertices,
           s32 verticesCount,
           v4 color)
{
    v2 viewOffset = { 1.0f, 1.0f };
    v2 screenOffset = { (r32)camera->ScreenLeft, (r32)camera->ScreenTop };
    
    r32 bufferCenterWidth = (camera->ViewWidth * 0.5f);
    r32 bufferCenterHeight = (camera->ViewHeight * 0.5f);
    
    for(s32 i = 0; i < (verticesCount - 1); ++i)
    {
        v3 vertex0 = vertices[i];
        v3 vertex1 = vertices[i + 1];
        
        vertex0 = M4x4_MultiplyV3(worldMatrix, vertex0);
        vertex1 = M4x4_MultiplyV3(worldMatrix, vertex1);
        
        //TODO(stephen):CHECK IF VIEWABLE -> NOT BEHIND ANOTHER OBJECT
        //if(TRUE) IS PLACEHOLDER
        if(TRUE)
        {
            vertex0 = M4x4_MultiplyV3(&camera->ViewMatrix, vertex0);
            vertex1 = M4x4_MultiplyV3(&camera->ViewMatrix, vertex1);
            
            v4 projected0 = M4x4_MultiplyV4(&camera->ProjectionMatrix, vertex0);
            v4 projected1 = M4x4_MultiplyV4(&camera->ProjectionMatrix, vertex1);
            
            projected0 *= (1.0f / projected0.W);
            projected1 *= (1.0f / projected1.W);
            
            if(CohenSutherlandLineClip(&projected0.X, &projected0.Y,
                                       &projected1.X, &projected1.Y,
                                       -1.0f, 1.0f,
                                       -1.0f, 1.0f) &&
               (IsClamped_R32(projected0.Z, -1.0f, 1.0f) &&// TODO(Stephen): NEED PROPER 3-DIMENTIONAL BOUNDS CHECKING
                IsClamped_R32(projected1.Z, -1.0f, 1.0f)))
            {
                vertex0 = { projected0.X, projected0.Y, projected0.Z };
                vertex1 = { projected1.X, projected1.Y, projected1.Z };
                
                v2 screen0 = { projected0.X, projected0.Y };
                v2 screen1 = { projected1.X, projected1.Y };
                
                screen0.Y *= -1.0f;
                screen1.Y *= -1.0f;
                
                screen0 += viewOffset;
                screen1 += viewOffset;
                
                screen0.X *= bufferCenterWidth;
                screen0.Y *= bufferCenterHeight;
                
                screen1.X *= bufferCenterWidth;
                screen1.Y *= bufferCenterHeight;
                
                screen0 += screenOffset;
                screen1 += screenOffset;
                
                DrawLine2D(buffer,
                           screen0,
                           screen1,
                           color);
            }
            
        }
    }
}

void
DrawLine3D(engine_buffer* buffer,
           m4x4* worldMatrix,
           engine_camera* camera,
           v3 vertex0,
           v3 vertex1,
           v4 color)
{
    v3 line[2] = {vertex0, vertex1};
    DrawLine3D(buffer,
               worldMatrix,
               camera,
               line,
               2,
               color);
}

inline void
FillTopFlatTriangle(engine_buffer* buffer,
                    v2 vert0, v2 vert1, v2 vert2,
                    v4 colorR32)
{
    r32 invslope1 = (vert2.X - vert0.X) / (vert2.Y - vert0.Y);
    r32 invslope2 = (vert2.X - vert1.X) / (vert2.Y - vert1.Y);
    
    r32 curX1 = vert2.X;
    r32 curX2 = vert2.X;
    
    for(s32 scanlineY = Truncate_R32ToS32(vert2.Y); scanlineY > Truncate_R32ToS32(vert0.Y); --scanlineY)
    {
        DrawLine2D(buffer,
                   { curX1, (r32)scanlineY },
                   { curX2, (r32)scanlineY },
                   colorR32);
        curX1 -= invslope1;
        curX2 -= invslope2;
    }
}

inline void
FillBottomFlatTriangle(engine_buffer* buffer,
                       v2 vert0, v2 vert1, v2 vert2,
                       v4 colorR32)
{
    r32 deltaY1 = (vert1.Y - vert0.Y);
    r32 deltaY2 = (vert2.Y - vert0.Y);
    
    if(deltaY1 < 1.0f)
        deltaY1 = 1.0f;
    if(deltaY2 < 1.0f)
        deltaY2 = 1.0f;
    
    r32 invslope1 = (vert1.X - vert0.X) / deltaY1;
    r32 invslope2 = (vert2.X - vert0.X) / deltaY2;
    
    r32 curX1 = vert0.X;
    r32 curX2 = vert0.X;
    
    for(s32 scanlineY = Truncate_R32ToS32(vert0.Y); scanlineY <= Truncate_R32ToS32(vert1.Y); ++scanlineY)
    {
        DrawLine2D(buffer,
                   { curX1, (r32)scanlineY },
                   { curX2, (r32)scanlineY },
                   colorR32);
        curX1 += invslope1;
        curX2 += invslope2;
    }
}

void
FillTriangle(engine_buffer* buffer,
             v2 vert0, v2 vert1, v2 vert2,
             v4 colorR32)
{
    vert0.X = Floor_R32(vert0.X);
    vert0.Y = Floor_R32(vert0.Y);
    
    vert1.X = Floor_R32(vert1.X);
    vert1.Y = Floor_R32(vert1.Y);
    
    vert2.X = Floor_R32(vert2.X);
    vert2.Y = Floor_R32(vert2.Y);
    
    //SORT -> vert0.Y < vert1.Y < vert2.Y
    if(vert0.Y > vert1.Y)
        Swap_V2(&vert0, &vert1);
    if(vert1.Y > vert2.Y)
        Swap_V2(&vert1, &vert2);
    if(vert0.Y > vert1.Y)
        Swap_V2(&vert0, &vert1);
    
    if(vert1.Y == vert2.Y)
    {
        FillBottomFlatTriangle(buffer, vert0, vert1, vert2, colorR32);
    }
    else if(vert0.Y == vert1.Y)
    {
        FillTopFlatTriangle(buffer, vert0, vert1, vert2, colorR32);
    }
    else
    {
        r32 x = Truncate_R32ToS32((vert0.X +
                                   ((vert1.Y - vert0.Y) / (vert2.Y - vert0.Y)) *
                                   (vert2.X - vert0.X)));
        
        v2 vert3 = { x, Floor_R32(vert1.Y) };
        
        FillBottomFlatTriangle(buffer, vert0, vert1, vert3, colorR32);
        FillTopFlatTriangle(buffer, vert1, vert3, vert2, colorR32);
    }
}




internal_function inline s32
RenderMesh(engine_buffer* buffer,
           m4x4* worldMatrix,
           engine_camera* camera,
           render_mesh* mesh,
           s32 renderMode)
{
    s32 trianglesRendered = 0;
    v2 viewOffset = { 1.0f, 1.0f };
    v2 screenOffset = { (r32)camera->ScreenLeft, (r32)camera->ScreenTop };
    
    r32 bufferCenterWidth = (camera->ViewWidth * 0.5f);
    r32 bufferCenterHeight = (camera->ViewHeight * 0.5f);
    
    m4x4 meshScale = M4x4_Scale(mesh->WorldScale);
    m4x4 meshRotation = M4x4_RotationXYZ(mesh->WorldRotation);
    m4x4 meshTransformation = M4x4_MultiplyM4x4(&meshRotation, &meshScale);
    M4x4_Translate(&meshTransformation, mesh->WorldPosition);
    meshTransformation = M4x4_MultiplyM4x4(worldMatrix, &meshTransformation);
    
    m4x4 viewTransformation = M4x4_MultiplyM4x4(&camera->ViewMatrix, &meshTransformation);
    s32 normalIndex = 0;
    
    for(s32 i = 0; i < mesh->TriangleCount; i += 3)
    {
        v3 vertex0 = mesh->Vertices[mesh->Triangles[i + 0]];
        v3 vertex1 = mesh->Vertices[mesh->Triangles[i + 1]];
        v3 vertex2 = mesh->Vertices[mesh->Triangles[i + 2]];
        v3 worldVertex0 = M4x4_MultiplyV3(&meshTransformation, vertex0);
        
        // TODO(Stephen): MOVE TO DEBUG SYSTEMS
        //THIS COMPUTES FACE NORMALS FOR VIEW IN CAMERA
        v3 meshNormal = mesh->Normals[normalIndex++];
        meshNormal = M4x4_MultiplyV3(&meshRotation, meshNormal);
        Normalize(&meshNormal);
        
        vertex0 = M4x4_MultiplyV3(&viewTransformation, vertex0);
        vertex1 = M4x4_MultiplyV3(&viewTransformation, vertex1);
        vertex2 = M4x4_MultiplyV3(&viewTransformation, vertex2);
        
        //VIEW SPACE NORMAL
        v3 line1 = vertex1 - vertex0;
        v3 line2 = vertex2 - vertex0;
        v3 normal = CrossProduct(line1, line2);
        Normalize(&normal);
        v3 cameraRay = Normalized(vertex0 - V3_FORWARD);
        
        if(DotProduct(normal, cameraRay) < 0.0f)
        {
            //TRANSFORM TO UNIT CUBE
            v4 projected0 = M4x4_MultiplyV4(&camera->ProjectionMatrix, vertex0);
            v4 projected1 = M4x4_MultiplyV4(&camera->ProjectionMatrix, vertex1);
            v4 projected2 = M4x4_MultiplyV4(&camera->ProjectionMatrix, vertex2);
            
            //CLIP TO UNIT CUBE
            if(IsClamped_R32(projected0.X, -projected0.W, projected0.W) && //X
               IsClamped_R32(projected1.X, -projected1.W, projected1.W) &&
               IsClamped_R32(projected2.X, -projected2.W, projected2.W) &&
               
               IsClamped_R32(projected0.Y, -projected0.W, projected0.W) && //Y
               IsClamped_R32(projected1.Y, -projected1.W, projected1.W) &&
               IsClamped_R32(projected2.Y, -projected2.W, projected2.W) &&
               
               IsClamped_R32(projected0.Z, -projected0.W, projected0.W) && //Z
               IsClamped_R32(projected1.Z, -projected1.W, projected1.W) &&
               IsClamped_R32(projected2.Z, -projected2.W, projected2.W))
            {
                ++trianglesRendered;
                
                v2 screen0 =
                {
                    projected0.X / projected0.W,
                    projected0.Y / projected0.W,
                };
                
                v2 screen1 =
                {
                    projected1.X / projected1.W,
                    projected1.Y / projected1.W,
                };
                
                v2 screen2 =
                {
                    projected2.X / projected2.W,
                    projected2.Y / projected2.W,
                };
                
                //NOTE(stephen):CLIPPING SPACE +Y IS UP
                //SCREEN SPACE +Y IS DOWN
                screen0.Y *= -1.0f;
                screen1.Y *= -1.0f;
                screen2.Y *= -1.0f;
                
                screen0 += viewOffset;
                screen1 += viewOffset;
                screen2 += viewOffset;
                
                screen0.X *= bufferCenterWidth;
                screen0.Y *= bufferCenterHeight;
                
                screen1.X *= bufferCenterWidth;
                screen1.Y *= bufferCenterHeight;
                
                screen2.X *= bufferCenterWidth;
                screen2.Y *= bufferCenterHeight;
                
                screen0 += screenOffset;
                screen1 += screenOffset;
                screen2 += screenOffset;
                
                v4 colorChange = mesh->Color;
                r32 alpha = colorChange.A;
                
                if(renderMode & RENDER_MODE_SOLID)
                {
                    if(renderMode & RENDER_MODE_SHADED)
                    {
                        
                        //for(s32 i = 0; i < mesh->LightSourceCount; ++i)
                        if(mesh->LightSource)
                        {
                            v3 lightRay = worldVertex0 - mesh->LightSource->WorldPosition;
                            r32 lightDot = DotProduct(meshNormal, Normalized(lightRay));
                            
                            if(lightDot > 0.0f)
                            {
                                colorChange *= 0.0f;
                            }
                            else
                            {
                                colorChange *= -lightDot * mesh->LightSource->Intensity;
                            }
                            
                            colorChange.A = alpha;
                        }
                    }
                    
                    FillTriangle(buffer,
                                 screen0,
                                 screen1,
                                 screen2,
                                 colorChange);
                    
                    colorChange = InvertedColor(mesh->Color);
                }
                
                if(renderMode & RENDER_MODE_WIRE)
                {
                    DrawLine2D(buffer, screen0, screen1,
                               colorChange);
                    DrawLine2D(buffer, screen0, screen2,
                               colorChange);
                    DrawLine2D(buffer, screen1, screen2,
                               colorChange);
                }
                
                if(renderMode & RENDER_MODE_NORMALS)
                {
                    DrawLine3D(buffer,
                               worldMatrix,
                               camera,
                               worldVertex0,
                               worldVertex0 + meshNormal,
                               {0.0f, 0.5f, 0.1f});
                }
            }
        }
    }
    
    
    if((renderMode & RENDER_MODE_LIGHT_RAY) &&
       mesh->LightSource)
    {
        DrawLine3D(buffer,
                   worldMatrix,
                   camera,
                   mesh->LightSource->WorldPosition,
                   mesh->WorldPosition,
                   mesh->LightSource->Color);
    }
    
    
    return(trianglesRendered);
}

void
SDL_SoftwareRender(SDL_Renderer* renderer,
                   SDL_Texture* texture,
                   render_group* group,
                   engine_buffer* buffer)
{
    v4 c = { 1, 0.3f, 0.3f, 0.4f };
    
    for(s32 i = 0; i < group->Used; i += sizeof(render_header))
    {
        render_header* header = (render_header*)((u8*)group->Base + i);
        void* data = (header + 1);
        
        switch(header->Type)
        {
            case render_type_render_clear:
            {
                render_clear* clear = (render_clear*)data;
                i += sizeof(render_clear);
                
                u32 color = (((u32)(clear->Color.A * 255.0f) << 24) |
                             ((u32)(clear->Color.R * 255.0f) << 16) |
                             ((u32)(clear->Color.G * 255.0f) <<  8) |
                             ((u32)(clear->Color.B * 255.0f) <<  0));
                
                //CLEAR OFFSCREEN BUFFER
                u32* pixel = (u32*)buffer->Memory;
                for(s32 i = 0; i < buffer->Width * buffer->Height; i++)
                {
                    *pixel++ = color;
                }
                
            }break;
            case render_type_render_rectangle:
            {
                render_rectangle* rectangle = (render_rectangle*)data;
                i += sizeof(render_rectangle);
                
                DrawRectangle(buffer,
                              rectangle->Position,
                              rectangle->Position + rectangle->Dimensions,
                              rectangle->Color);
            }break;
            case render_type_render_mesh:
            {
                render_mesh* mesh = (render_mesh*)data;
                i += sizeof(render_mesh);
                
                RenderMesh(buffer,
                           &group->WorldMatrix,
                           group->Camera,
                           mesh,
                           group->RenderMode);
                
            }break;
            case render_type_render_bitmap:
            {
                render_bitmap* bitmap = (render_bitmap*)data;
                i += sizeof(render_bitmap);
                
                DrawBitmap(buffer,
                           &bitmap->Image,
                           bitmap->Position,
                           {bitmap->Image.Width * 0.5f, bitmap->Image.Height * 0.5f});
                
            }break;
            case render_type_render_line2d:
            {
                render_line2d* line = (render_line2d*)data;
                i += sizeof(render_line2d);
                
                DrawLine2D(buffer,
                           line->Points[0],
                           line->Points[1],
                           line->Color);
            }break;
            DefaultEmptyCase;
        }
    }
    
    SDL_UpdateTexture(texture, 0, buffer->Memory, buffer->Pitch);
    SDL_RenderCopy(renderer, texture, 0, 0);
    SDL_RenderPresent(renderer);
}