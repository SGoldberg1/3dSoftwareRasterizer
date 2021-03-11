
// TODO(Stephen): REMOVE ONCE SIMD AND MATHEMATICAL COMPUTATIONS IMPLEMENTED
#include <math.h>

inline v4
InvertedColor(v4 color)
{
    v4 result =
    {
        color.A,
        (1.0f - color.R),
        (1.0f - color.G),
        (1.0f - color.B)
    };
    return(result);
}

global_variable s32 RANDOM_SEED = 0;
inline s32
Random_S32(s32 min, s32 max)
{
    local_persist s32 modulus = 9371683;
    local_persist s32 increment = 21412213;
    local_persist s32 lastNumber = 7;
    s32 result = 0;
    
    lastNumber = (lastNumber * RANDOM_SEED + increment);
    lastNumber = (lastNumber % modulus);
    lastNumber = (lastNumber & (0x7FFFFFFF));//FORCE POSITIVE NUMBERS
    result = ((lastNumber % (max - min)) + min);//KEEP VALUE WITHIN RANGE
    return(result);
}

//TRUNCATING
inline s32
Truncate_R32ToS32(r32 value)
{
    s32 result = ((s32)value);
    return(result);
}
inline u32
Truncate_R32ToU32(r32 value)
{
    u32 result = ((u32)value);
    return(result);
}

//CLAMPING
inline b32
IsClampedInclusive_S8(s8 value, s8 min, s8 max)
{
    b32 result = ((min <= value) && (value <= max));
    return(result);
}
inline b32
IsClamped_S32(s32 value, s32 min, s32 max)
{
    b32 result = ((min <= value) && (value < max));
    return(result);
}
inline b32
IsClamped_U32(u32 value, u32 min, u32 max)
{
    b32 result = ((min <= value) && (value < max));
    return(result);
}
inline b32
IsClamped_R32(r32 value, r32 min, r32 max)
{
    b32 result = ((min <= value) && (value < max));
    return(result);
}
inline r32
ClampInclusive_R32(r32 value, r32 min, r32 max)
{
    r32 result = ((value <= min) ? min :
                  (value >= max) ? max : value);
    return(result);
}

inline r32
Ceiling_R32(r32 value)
{
    r32 result = ceilf(value);
    return(result);
}

inline s32
Ceiling_R32ToS32(s32 value)
{
    s32 result = (s32)ceilf(value);
    return(result);
}

//ROUNDING
inline u32
Round_R32ToU32(r32 value)
{
    u32 result = (u32)roundf(value);
    return(result);
}
inline s32
Round_R32ToS32(r32 value)
{
    s32 result = (s32)roundf(value);
    return(result);
}

//FLOORING
inline u32
Floor_R32ToU32(r32 value)
{
    u32 result = (u32)floorf(value);
    return(result);
}
inline s32
Floor_R32ToS32(r32 value)
{
    s32 result = (s32)floorf(value);
    return(result);
}
inline r32
Floor_R32(r32 value)
{
    r32 result = floorf(value);
    return(result);
}

//MAX
inline r32
Max_R32(r32 a, r32 b)
{
    r32 result = (a > b) ? a : b;
    return(result);
}
inline s32
Max_S32(s32 a, s32 b)
{
    s32 result = (a > b) ? a : b;
    return(result);
}
inline u32
Max_U32(u32 a, u32 b)
{
    u32 result = (a > b) ? a : b;
    return(result);
}

//MIN
inline r32
Min_R32(r32 a, r32 b)
{
    r32 result = (a < b) ? a : b;
    return(result);
}
inline s32
Min_S32(s32 a, s32 b)
{
    s32 result = (a < b) ? a : b;
    return(result);
}
inline u32
Min_U32(u32 a, u32 b)
{
    u32 result = (a < b) ? a : b;
    return(result);
}

//ABSOLUTE VALUE
inline r32
Abs_R32(r32 value)
{
    r32 result = ((value < 0) ? -value : value);
    return(result);
}
inline s32
Abs_S32(s32 value)
{
    s32 result = ((value < 0) ? -value : value);
    return result;
}

//SWAP
inline void
Swap_S32(s32* a, s32* b)
{
    s32 temp = *a;
    *a = *b;
    *b = temp;
}
inline void
Swap_R32(r32* a, r32* b)
{
    r32 temp = *a;
    *a = *b;
    *b = temp;
}
inline void
Swap_U32(u32* a, u32* b)
{
    u32 temp = *a;
    *a = *b;
    *b = temp;
}
inline void
Swap_V2(v2* a, v2* b)
{
    v2 temp = *a;
    *a = *b;
    *b = temp;
}
inline void
Swap_V3(v3* a, v3* b)
{
    v3 temp = *a;
    *a = *b;
    *b = temp;
}
inline void
Swap_V4(v4* a, v4* b)
{
    v4 temp = *a;
    *a = *b;
    *b = temp;
}

//POWER
inline r32
Pow(r32 base, r32 power)
{
    r32 result = powf(base, power);
    return(result);
}

//TRIG
inline r32
Tan(r32 radians)
{
    r32 result = tanf(radians);
    return(result);
}
inline r32
Cos(r32 radians)
{
    r32 result = cosf(radians);
    return(result);
}
inline r32
Sin(r32 radians)
{
    r32 result = sinf(radians);
    return(result);
}

inline r32
Sqrt(r32 value)
{
    r32 result = sqrtf(value);
    return(result);
}
inline r32
Log(r32 value)
{
    r32 result = logf(value);
    return(result);
}

//////////////////////////////// V2 ////////////////////////////////

inline r32
LengthSquared(v2 vector)
{
    r32 result = ((vector.X * vector.X) +
                  (vector.Y * vector.Y));
    return(result);
}

inline r32
Magnitude(v2 vector)
{
    r32 result = Sqrt((vector.X * vector.X) +
                      (vector.Y * vector.Y));
    return(result);
}

inline v2
Normalized(v2 result)
{
    r32 magnitude = Magnitude(result);
    if(magnitude)
    {
        result.X = (result.X / magnitude);
        result.Y = (result.Y / magnitude);
    }
    return(result);
}
inline void
Normalize(v2* result)
{
    *result = Normalized(*result);
}

inline v2
HadamardProduct(v2 a, v2 b)
{
    v2 result =
    {
        (a.X * b.X),
        (a.Y * b.Y)
    };
    return(result);
}

inline r32
DotProduct(v2 a, v2 b)
{
    r32 result = ((a.X * b.X) +
                  (a.Y * b.Y));
    return(result);
}

inline v2
Perpendicular(v2 vector)
{
    v2 result = { -vector.Y, vector.X };
    return(result);
}

//////////////////////////////// V3 ////////////////////////////////

inline r32
LengthSquared(v3 vector)
{
    r32 result = ((vector.X * vector.X) +
                  (vector.Y * vector.Y) +
                  (vector.Z * vector.Z));
    return(result);
}

inline r32
Magnitude(v3 vector)
{
    r32 result = Sqrt((vector.X * vector.X) +
                      (vector.Y * vector.Y) +
                      (vector.Z * vector.Z));
    return(result);
}

inline v3
Normalized(v3 result)
{
    r32 magnitude = Magnitude(result);
    if(magnitude)
    {
        result.X = (result.X / magnitude);
        result.Y = (result.Y / magnitude);
        result.Z = (result.Z / magnitude);
    }
    return(result);
}

inline void
Normalize(v3* result)
{
    *result = Normalized(*result);
}

inline v3
HadamardProduct(v3 a, v3 b)
{
    v3 result =
    {
        (a.X * b.X),
        (a.Y * b.Y),
        (a.Z * b.Z)
    };
    return(result);
}

inline r32
DotProduct(v3 a, v3 b)
{
    r32 result = ((a.X * b.X) +
                  (a.Y * b.Y) +
                  (a.Z * b.Z));
    return(result);
}

inline v3
CrossProduct(v3 a, v3 b)
{
    v3 result =
    {
        ((a.Y * b.Z) - (a.Z * b.Y)),
        ((a.Z * b.X) - (a.X * b.Z)),
        ((a.X * b.Y) - (a.Y * b.X))
    };
    return(result);
}

//////////////////////////////// V4 ////////////////////////////////

inline v4
Unpack4x8_V4(u32 packed)
{
    v4 result;
    result.X = ((packed >> 24) & 0xFF);
    result.Y = ((packed >> 16) & 0xFF);
    result.Z = ((packed >>  8) & 0xFF);
    result.W = ((packed >>  0) & 0xFF);
    return(result);
}

inline u32
Pack4x8_U32_255(v4 unpacked)
{
    u32 result = (((u32)(unpacked.X * 255.0f) << 24) |
                  ((u32)(unpacked.Y * 255.0f) << 16) |
                  ((u32)(unpacked.Z * 255.0f) <<  8) |
                  ((u32)(unpacked.W * 255.0f) <<  0));
    return(result);
}

inline v4
HadamardProduct(v4 a, v4 b)
{
    v4 result =
    {
        (a.X * b.X),
        (a.Y * b.Y),
        (a.Z * b.Z),
        (a.W * b.W),
    };
    return(result);
}

//////////////////////////////// MATRIX ////////////////////////////////



inline m2x2
M2x2_Identity(void)
{
    m2x2 result;
    result.E[0][0] = 1.0f;
    result.E[0][1] = 0;
    
    result.E[1][0] = 0;
    result.E[1][1] = 1.0f;
    return(result);
}

inline m3x3
M3x3_Identity(void)
{
    m3x3 result;
    result.E[0][0] = 1.0f;
    result.E[0][1] = 0;
    result.E[0][2] = 0;
    
    result.E[1][0] = 0;
    result.E[1][1] = 1.0f;
    result.E[1][2] = 0;
    
    result.E[2][0] = 0;
    result.E[2][1] = 0;
    result.E[2][2] = 1.0f;
    return(result);
}

inline m4x4
M4x4_Identity(void)
{
    m4x4 result;
    result.E[0][0] = 1.0f;
    result.E[0][1] = 0;
    result.E[0][2] = 0;
    result.E[0][3] = 0;
    
    result.E[1][0] = 0;
    result.E[1][1] = 1.0f;
    result.E[1][2] = 0;
    result.E[1][3] = 0;
    
    result.E[2][0] = 0;
    result.E[2][1] = 0;
    result.E[2][2] = 1.0f;
    result.E[2][3] = 0;
    
    result.E[3][0] = 0;
    result.E[3][1] = 0;
    result.E[3][2] = 0;
    result.E[3][3] = 1.0f;
    
    return(result);
}

//TRANSPOSE
inline m2x2
M2x2_Transpose(m2x2* matrix)
{
    /*
    |a b| => |a c|
    |c d|    |b d|
    */
    m2x2 result;
    result.E[0][0] = matrix->E[0][0];//a -> a
    result.E[0][1] = matrix->E[1][0];//b -> c
    
    result.E[1][0] = matrix->E[0][1];//c -> b
    result.E[1][1] = matrix->E[1][1];//d -> d
    return(result);
}

inline m3x3
M3x3_Transpose(m3x3* matrix)
{
    /*
    |a b c| => |a d g|
    |d e f|    |b e h|
    |g h i|    |c f i|
    */
    m3x3 result;
    result.E[0][0] = matrix->E[0][0];//a -> a
    result.E[0][1] = matrix->E[1][0];//b -> d
    result.E[0][2] = matrix->E[2][0];//c -> g
    
    result.E[1][0] = matrix->E[0][1];//d -> b
    result.E[1][1] = matrix->E[1][1];//e -> e
    result.E[1][2] = matrix->E[2][1];//f -> h
    
    result.E[2][0] = matrix->E[0][2];//g -> c
    result.E[2][1] = matrix->E[1][2];//h -> f
    result.E[2][2] = matrix->E[2][2];//i -> i
    return(result);
}

inline m4x4
M4x4_Transpose(m4x4* matrix)
{
    /*
    |a b c d| => |a e i m|
    |e f g h|    |b f j n|
    |i j k l|    |c g k o|
    |m n o p|    |d h l p|
    */
    m4x4 result;
    result.E[0][0] = matrix->E[0][0];//a -> a
    result.E[0][1] = matrix->E[1][0];//b -> e
    result.E[0][2] = matrix->E[2][0];//c -> i
    result.E[0][3] = matrix->E[3][0];//d -> m
    
    result.E[1][0] = matrix->E[0][1];//e -> b
    result.E[1][1] = matrix->E[1][1];//f -> f
    result.E[1][2] = matrix->E[2][1];//g -> j
    result.E[1][3] = matrix->E[3][1];//h -> n
    
    result.E[2][0] = matrix->E[0][2];//e -> b
    result.E[2][1] = matrix->E[1][2];//f -> f
    result.E[2][2] = matrix->E[2][2];//g -> j
    result.E[2][3] = matrix->E[3][2];//h -> n
    
    result.E[3][0] = matrix->E[0][3];//e -> b
    result.E[3][1] = matrix->E[1][3];//f -> f
    result.E[3][2] = matrix->E[2][3];//g -> j
    result.E[3][3] = matrix->E[3][3];//h -> n
    return(result);
}

//MULTIPLY
inline v2
M2x2_MultiplyV2(m2x2* matrix, v2 vector)
{
    /*
    |a b|   |x|   |ax + by|
    |c d| x |y| = |cx + dy|
    */
    v2 result = {};
    result.X = ((matrix->E[0][0] * vector.X) +
                (matrix->E[0][1] * vector.Y));
    
    result.Y = ((matrix->E[1][0] * vector.X) +
                (matrix->E[1][1] * vector.Y));
    return(result);
}

inline v3
M3x3_MultiplyV3(m3x3* matrix, v3 vector)
{
    /*
    |a b c|   |x|   |ax + by + cz|
    |d e f| x |y| = |dx + ey + fz|
    |g h i|   |z|   |gx + hy + iz|
    */
    v3 result = {};
    result.X = ((matrix->E[0][0] * vector.X) +
                (matrix->E[0][1] * vector.Y) +
                (matrix->E[0][2] * vector.Z));
    
    result.Y = ((matrix->E[1][0] * vector.X) +
                (matrix->E[1][1] * vector.Y) +
                (matrix->E[1][2] * vector.Z));
    
    result.Z = ((matrix->E[2][0] * vector.X) +
                (matrix->E[2][1] * vector.Y) +
                (matrix->E[2][2] * vector.Z));
    return(result);
}

inline v3
M4x4_MultiplyV3(m4x4* matrix, v3 vector, r32 w = 1.0f)
{
    /*
    |a b c d|   |x|   |ax + by + cz + dw|
    |e f g h| x |y| = |ex + fy + gz + hw|
    |i j k l|   |z|   |ix + jy + kz + lw|
    |m n o p|   |w|   |mx + ny + oz + pw|
    */
    v3 result = {};
    result.X = ((matrix->E[0][0] * vector.X) +
                (matrix->E[0][1] * vector.Y) +
                (matrix->E[0][2] * vector.Z) +
                (matrix->E[0][3] * w));
    
    result.Y = ((matrix->E[1][0] * vector.X) +
                (matrix->E[1][1] * vector.Y) +
                (matrix->E[1][2] * vector.Z) +
                (matrix->E[1][3] * w));
    
    result.Z = ((matrix->E[2][0] * vector.X) +
                (matrix->E[2][1] * vector.Y) +
                (matrix->E[2][2] * vector.Z) +
                (matrix->E[2][3] * w));
    
    w = ((matrix->E[3][0] * vector.X) +
         (matrix->E[3][1] * vector.Y) +
         (matrix->E[3][2] * vector.Z) +
         (matrix->E[3][3] * w));
    
    //TO NORMALIZE VECTOR 4(WITH W) TO VECTOR 3
    if(w)
    {
        w = 1.0f / w;
        result.X *= w;
        result.Y *= w;
        result.Z *= w;
    }
    return(result);
}

inline v4
M4x4_MultiplyV4(m4x4* matrix, v4 vector)
{
    /*
    |a b c d|   |x|   |ax + by + cz + dw|
    |e f g h| x |y| = |ex + fy + gz + hw|
    |i j k l|   |z|   |ix + jy + kz + lw|
    |m n o p|   |w|   |mx + ny + oz + pw|
    */
    v4 result = {};
    result.X = ((matrix->E[0][0] * vector.X) +
                (matrix->E[0][1] * vector.Y) +
                (matrix->E[0][2] * vector.Z) +
                (matrix->E[0][3] * vector.W));
    
    result.Y = ((matrix->E[1][0] * vector.X) +
                (matrix->E[1][1] * vector.Y) +
                (matrix->E[1][2] * vector.Z) +
                (matrix->E[1][3] * vector.W));
    
    result.Z = ((matrix->E[2][0] * vector.X) +
                (matrix->E[2][1] * vector.Y) +
                (matrix->E[2][2] * vector.Z) +
                (matrix->E[2][3] * vector.W));
    
    result.W = ((matrix->E[3][0] * vector.X) +
                (matrix->E[3][1] * vector.Y) +
                (matrix->E[3][2] * vector.Z) +
                (matrix->E[3][3] * vector.W));
    return(result);
}

inline v4
M4x4_MultiplyV4(m4x4* matrix, v3 vector, r32 w = 1.0f)
{
    v4 result = M4x4_MultiplyV4(matrix, {vector.X, vector.Y, vector.Z, w});
    return(result);
}

inline m2x2
M2x2_MultiplyM2x2(m2x2* a, m2x2* b)
{
    m2x2 result;
    //ROW 0
    result.E[0][0] = ((a->E[0][0] * b->E[0][0]) +
                      (a->E[0][1] * b->E[1][0]));
    
    result.E[0][1] = ((a->E[0][0] * b->E[0][1]) +
                      (a->E[0][1] * b->E[1][1]));
    //ROW 1
    result.E[1][0] = ((a->E[1][0] * b->E[0][0]) +
                      (a->E[1][1] * b->E[1][0]));
    
    result.E[1][1] = ((a->E[1][0] * b->E[0][1]) +
                      (a->E[1][1] * b->E[1][1]));
    return(result);
}

inline m3x3
M3x3_MultiplyM3x3(m3x3* a, m3x3* b)
{
    m3x3 result;
    //ROW 0
    result.E[0][0] = ((a->E[0][0] * b->E[0][0]) +
                      (a->E[0][1] * b->E[1][0]) +
                      (a->E[0][2] * b->E[2][0]));
    
    result.E[0][1] = ((a->E[0][0] * b->E[0][1]) +
                      (a->E[0][1] * b->E[1][1]) +
                      (a->E[0][2] * b->E[2][1]));
    
    result.E[0][2] = ((a->E[0][0] * b->E[0][2]) +
                      (a->E[0][1] * b->E[1][2]) +
                      (a->E[0][2] * b->E[2][2]));
    //ROW 1
    result.E[1][0] = ((a->E[1][0] * b->E[0][0]) +
                      (a->E[1][1] * b->E[1][0]) +
                      (a->E[1][2] * b->E[2][0]));
    
    result.E[1][1] = ((a->E[1][0] * b->E[0][1]) +
                      (a->E[1][1] * b->E[1][1]) +
                      (a->E[1][2] * b->E[2][1]));
    
    result.E[1][2] = ((a->E[1][0] * b->E[0][2]) +
                      (a->E[1][1] * b->E[1][2]) +
                      (a->E[1][2] * b->E[2][2]));
    //ROW 2
    result.E[2][0] = ((a->E[2][0] * b->E[0][0]) +
                      (a->E[2][1] * b->E[1][0]) +
                      (a->E[2][2] * b->E[2][0]));
    
    result.E[2][1] = ((a->E[2][0] * b->E[0][1]) +
                      (a->E[2][1] * b->E[1][1]) +
                      (a->E[2][2] * b->E[2][1]));
    
    result.E[2][2] = ((a->E[2][0] * b->E[0][2]) +
                      (a->E[2][1] * b->E[1][2]) +
                      (a->E[2][2] * b->E[2][2]));
    return(result);
}

inline m4x4
M4x4_MultiplyM4x4(m4x4* a, m4x4* b)
{
    m4x4 result;
    //ROW 0
    result.E[0][0] = ((a->E[0][0] * b->E[0][0]) +
                      (a->E[0][1] * b->E[1][0]) +
                      (a->E[0][2] * b->E[2][0]) +
                      (a->E[0][3] * b->E[3][0]));
    
    result.E[0][1] = ((a->E[0][0] * b->E[0][1]) +
                      (a->E[0][1] * b->E[1][1]) +
                      (a->E[0][2] * b->E[2][1]) +
                      (a->E[0][3] * b->E[3][1]));
    
    result.E[0][2] = ((a->E[0][0] * b->E[0][2]) +
                      (a->E[0][1] * b->E[1][2]) +
                      (a->E[0][2] * b->E[2][2]) +
                      (a->E[0][3] * b->E[3][2]));
    
    result.E[0][3] = ((a->E[0][0] * b->E[0][3]) +
                      (a->E[0][1] * b->E[1][3]) +
                      (a->E[0][2] * b->E[2][3]) +
                      (a->E[0][3] * b->E[3][3]));
    //ROW 1
    result.E[1][0] = ((a->E[1][0] * b->E[0][0]) +
                      (a->E[1][1] * b->E[1][0]) +
                      (a->E[1][2] * b->E[2][0]) +
                      (a->E[1][3] * b->E[3][0]));
    
    result.E[1][1] = ((a->E[1][0] * b->E[0][1]) +
                      (a->E[1][1] * b->E[1][1]) +
                      (a->E[1][2] * b->E[2][1]) +
                      (a->E[1][3] * b->E[3][1]));
    
    result.E[1][2] = ((a->E[1][0] * b->E[0][2]) +
                      (a->E[1][1] * b->E[1][2]) +
                      (a->E[1][2] * b->E[2][2]) +
                      (a->E[1][3] * b->E[3][2]));
    
    result.E[1][3] = ((a->E[1][0] * b->E[0][3]) +
                      (a->E[1][1] * b->E[1][3]) +
                      (a->E[1][2] * b->E[2][3]) +
                      (a->E[1][3] * b->E[3][3]));
    //ROW 2
    result.E[2][0] = ((a->E[2][0] * b->E[0][0]) +
                      (a->E[2][1] * b->E[1][0]) +
                      (a->E[2][2] * b->E[2][0]) +
                      (a->E[2][3] * b->E[3][0]));
    
    result.E[2][1] = ((a->E[2][0] * b->E[0][1]) +
                      (a->E[2][1] * b->E[1][1]) +
                      (a->E[2][2] * b->E[2][1]) +
                      (a->E[2][3] * b->E[3][1]));
    
    result.E[2][2] = ((a->E[2][0] * b->E[0][2]) +
                      (a->E[2][1] * b->E[1][2]) +
                      (a->E[2][2] * b->E[2][2]) +
                      (a->E[2][3] * b->E[3][2]));
    
    result.E[2][3] = ((a->E[2][0] * b->E[0][3]) +
                      (a->E[2][1] * b->E[1][3]) +
                      (a->E[2][2] * b->E[2][3]) +
                      (a->E[2][3] * b->E[3][3]));
    //ROW 3
    result.E[3][0] = ((a->E[3][0] * b->E[0][0]) +
                      (a->E[3][1] * b->E[1][0]) +
                      (a->E[3][2] * b->E[2][0]) +
                      (a->E[3][3] * b->E[3][0]));
    
    result.E[3][1] = ((a->E[3][0] * b->E[0][1]) +
                      (a->E[3][1] * b->E[1][1]) +
                      (a->E[3][2] * b->E[2][1]) +
                      (a->E[3][3] * b->E[3][1]));
    
    result.E[3][2] = ((a->E[3][0] * b->E[0][2]) +
                      (a->E[3][1] * b->E[1][2]) +
                      (a->E[3][2] * b->E[2][2]) +
                      (a->E[3][3] * b->E[3][2]));
    
    result.E[3][3] = ((a->E[3][0] * b->E[0][3]) +
                      (a->E[3][1] * b->E[1][3]) +
                      (a->E[3][2] * b->E[2][3]) +
                      (a->E[3][3] * b->E[3][3]));
    return(result);
}

//ROTATION
inline m4x4
M4x4_RotationX(r32 radians)
{
    r32 sin = Sin(radians);
    r32 cos = Cos(radians);
    
    m4x4 result;
    result.E[0][0] = 1.0f;
    result.E[0][1] = 0;
    result.E[0][2] = 0;
    result.E[0][3] = 0;
    
    result.E[1][0] = 0;
    result.E[1][1] = cos;
    result.E[1][2] = -sin;
    result.E[1][3] = 0;
    
    result.E[2][0] = 0;
    result.E[2][1] = sin;
    result.E[2][2] = cos;
    result.E[2][3] = 0;
    
    result.E[3][0] = 0;
    result.E[3][1] = 0;
    result.E[3][2] = 0;
    result.E[3][3] = 1.0f;
    return(result);
}

inline m4x4
M4x4_RotationY(r32 radians)
{
    r32 sin = Sin(radians);
    r32 cos = Cos(radians);
    
    m4x4 result;
    result.E[0][0] = cos;
    result.E[0][1] = 0;
    result.E[0][2] = sin;
    result.E[0][3] = 0;
    
    result.E[1][0] = 0;
    result.E[1][1] = 1.0f;
    result.E[1][2] = 0;
    result.E[1][3] = 0;
    
    result.E[2][0] = -sin;
    result.E[2][1] = 0;
    result.E[2][2] = cos;
    result.E[2][3] = 0;
    
    result.E[3][0] = 0;
    result.E[3][1] = 0;
    result.E[3][2] = 0;
    result.E[3][3] = 1.0f;
    return(result);
}

inline m4x4
M4x4_RotationZ(r32 radians)
{
    r32 sin = Sin(radians);
    r32 cos = Cos(radians);
    
    m4x4 result;
    result.E[0][0] = cos;
    result.E[0][1] = -sin;
    result.E[0][2] = 0;
    result.E[0][3] = 0;
    
    result.E[1][0] = sin;
    result.E[1][1] = cos;
    result.E[1][2] = 0;
    result.E[1][3] = 0;
    
    result.E[2][0] = 0;
    result.E[2][1] = 0;
    result.E[2][2] = 1.0f;
    result.E[2][3] = 0;
    
    result.E[3][0] = 0;
    result.E[3][1] = 0;
    result.E[3][2] = 0;
    result.E[3][3] = 1.0f;
    return(result);
}

inline m4x4
M4x4_RotationXYZ(v3 radians)
{
    r32 xSin = Sin(radians.X);
    r32 xCos = Cos(radians.X);
    r32 ySin = Sin(radians.Y);
    r32 yCos = Cos(radians.Y);
    r32 zSin = Sin(radians.Z);
    r32 zCos = Cos(radians.Z);
    
    m4x4 result;
    result.E[0][0] = (yCos * zCos);
    result.E[0][1] = ((xSin * ySin * zCos) + (xCos * -zSin));
    result.E[0][2] = ((xCos * ySin * zCos) + ((-xSin) * (-zSin)));
    result.E[0][3] = 0;
    
    result.E[1][0] = (yCos * zSin);
    result.E[1][1] = ((xSin * ySin * zSin) + (xCos * zCos));
    result.E[1][2] = ((xCos * ySin * zSin) + (-xSin * zCos));
    result.E[1][3] = 0;
    
    result.E[2][0] = (-ySin);
    result.E[2][1] = (xSin * yCos);
    result.E[2][2] = (xCos * yCos);
    result.E[2][3] = 0;
    
    result.E[3][0] = 0;
    result.E[3][1] = 0;
    result.E[3][2] = 0;
    result.E[3][3] = 1.0f;
    return(result);
}

// TODO(Stephen): DOUBLE CHECK CALCULATIONS AND DESIRED RESULT
inline v3
RotateAround(v3 point,
             v3 pivotPoint,
             v3 axis,
             r32 angle)
{
    v3 origin = point - pivotPoint;
    m4x4 rotation = M4x4_RotationXYZ(angle * Normalized(axis));
    v3 result = M4x4_MultiplyV3(&rotation, origin) + pivotPoint;
    return(result);
}

inline m4x4
M4x4_Scale(v3 scale)
{
    m4x4 result = {};
    result.E[0][0] = scale.X;
    result.E[1][1] = scale.Y;
    result.E[2][2] = scale.Z;
    result.E[3][3] = 1.0f;
    return(result);
}

//TRANSLATION
m4x4 inline
M4x4_Translation(v3 translation)
{
    m4x4 result = M4x4_Identity();
    result.E[0][3] = translation.X;
    result.E[1][3] = translation.Y;
    result.E[2][3] = translation.Z;
    result.E[3][3] = 1.0f;
    return(result);
}

void inline
M4x4_Translate(m4x4* matrix, v3 translation)
{
    matrix->E[0][3] += translation.X;
    matrix->E[1][3] += translation.Y;
    matrix->E[2][3] += translation.Z;
}

// NOTE(Stephen): SEE PROJECTIVE MATRIX FOR DETAILS
//MAYBE USE SIMPLIFIED PROJECTION MATRIX FOR SOFTWARE RENDER???
inline m4x4
M4x4_GetPerspectiveMatrix(r32 screenLeft, r32 screenRight,
                          r32 screenTop, r32 screenBottom,
                          r32 fieldOfView, r32 nearPlane, r32 farPlane)
{
    r32 screenWidth = (screenRight - screenLeft);
    r32 screenHeight = (screenBottom - screenTop);
    
    r32 aspectRatio = (screenWidth / (r32)screenHeight);
    r32 scale = (nearPlane * Tan(RADIANS(fieldOfView * 0.5f)));
    r32 viewRight = aspectRatio * scale;
    r32 viewLeft = -viewRight;
    r32 viewTop = scale;
    r32 viewBottom = -viewTop;
    r32 xScale = (2 * nearPlane) / (viewRight - viewLeft);
    r32 yScale = (2 * nearPlane) / (viewTop - viewBottom);
    
    m4x4 result;
    result.E[0][0] = xScale;
    result.E[0][1] = 0;
    result.E[0][2] = (viewRight + viewLeft) / (viewRight - viewLeft);
    result.E[0][3] = 0;
    
    result.E[1][0] = 0;
    result.E[1][1] = yScale;
    result.E[1][2] = (viewBottom + viewTop) / (viewTop - viewBottom);
    result.E[1][3] = 0;
    
    result.E[2][0] = 0;
    result.E[2][1] = 0;
    result.E[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    result.E[2][3] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
    
    result.E[3][0] = 0;
    result.E[3][1] = 0;
    result.E[3][2] = -1;
    result.E[3][3] = 0;
    
    return(result);
}

inline m4x4
M4x4_LookAtViewMatrix(v3 position, v3 target, v3 worldUp = V3_UP)
{
    v3 forward = Normalized(position - target);
    v3 right = CrossProduct(Normalized(worldUp), forward);
    v3 up = CrossProduct(forward, right);
    
    m4x4 result = {};
    result.E[0][0] = right.X;
    result.E[0][1] = right.Y;
    result.E[0][2] = right.Z;
    result.E[0][3] = -DotProduct(right, position);
    
    result.E[1][0] = up.X;
    result.E[1][1] = up.Y;
    result.E[1][2] = up.Z;
    result.E[1][3] = -DotProduct(up, position);
    
    result.E[2][0] = forward.X;
    result.E[2][1] = forward.Y;
    result.E[2][2] = forward.Z;
    result.E[2][3] = -DotProduct(forward, position);
    
    result.E[3][3] = 1;
    
    return(result);
}

inline m4x4
M4x4_FPSViewMatrix(v3 position, r32 pitch, r32 yaw)
{
    r32 pitchSin = Sin(pitch);
    r32 pitchCos = Cos(pitch);
    r32 yawSin = Sin(yaw);
    r32 yawCos = Cos(yaw);
    
    v3 right = { yawCos, 0, -yawSin };
    v3 up = { (pitchSin * yawSin), pitchCos, (yawCos * pitchSin) };
    v3 forward = { (yawSin * pitchCos), -pitchSin, (pitchCos * yawCos)  };
    
    m4x4 result = {};
    result.E[0][0] = right.X;
    result.E[0][1] = right.Y;
    result.E[0][2] = right.Z;
    result.E[0][3] = -DotProduct(right, position);
    
    result.E[1][0] = up.X;
    result.E[1][1] = up.Y;
    result.E[1][2] = up.Z;
    result.E[1][3] = -DotProduct(up, position);
    
    result.E[2][0] = forward.X;
    result.E[2][1] = forward.Y;
    result.E[2][2] = forward.Z;
    result.E[2][3] = -DotProduct(forward, position);
    
    result.E[3][3] = 1;
    
    return(result);
}


//////////////////////////////// NOISE ////////////////////////////////

s32 PERLIN_HASH[512] =
{
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
    8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
    35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
    134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
    55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,
    18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,
    226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,
    17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,
    167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,
    246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,
    239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,
    254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
    
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
    8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
    35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
    134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
    55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,
    18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,
    226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,
    17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,
    167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,
    246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,
    239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,
    254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

inline r32
Lerp(r32 t, r32 a, r32 b)
{
    r32 result = (a + (t * (b - a)));
    return(result);
}

inline r32
Fade(r32 value)
{
    r32 result = (value * value * value *
                  (value * (value * 6.0f - 15.0f) + 10.0f));
    return(result);
}

inline r32
Gradient(s32 hash, r32 x, r32 y, r32 z)
{
    switch(hash & 0xF)
    {
        case 0x0: return  x + y;
        case 0x1: return -x + y;
        case 0x2: return  x - y;
        case 0x3: return -x - y;
        case 0x4: return  x + z;
        case 0x5: return -x + z;
        case 0x6: return  x - z;
        case 0x7: return -x - z;
        case 0x8: return  y + z;
        case 0x9: return -y + z;
        case 0xA: return  y - z;
        case 0xB: return -y - z;
        case 0xC: return  y + x;
        case 0xD: return -y + z;
        case 0xE: return  y - x;
        case 0xF: return -y - z;
        default: return 0; //NEVER HAPPENES
    }
}

inline r32
PerlinNoise3D(r32 xR32, r32 yR32, r32 zR32,
              r32 frequency = 1.0f)
{
    xR32 *= frequency;
    yR32 *= frequency;
    zR32 *= frequency;
    
    s32 x = Floor_R32ToS32(xR32);
    s32 y = Floor_R32ToS32(yR32);
    s32 z = Floor_R32ToS32(zR32);
    
    xR32 = (xR32 - (r32)x);
    yR32 = (yR32 - (r32)y);
    zR32 = (zR32 - (r32)z);
    
    r32 u = Fade(xR32);
    r32 v = Fade(yR32);
    r32 w = Fade(zR32);
    
    x = (x & 0xFF);
    y = (y & 0xFF);
    z = (z & 0xFF);
    
    s32 a = PERLIN_HASH[x + 0] + y;
    s32 b = PERLIN_HASH[x + 1] + y;
    s32 aa = PERLIN_HASH[a + 0] + z;
    s32 ba = PERLIN_HASH[b + 0] + z;
    s32 ab = PERLIN_HASH[a + 1] + z;
    s32 bb = PERLIN_HASH[b + 1] + z;
    r32 result = Lerp(w,
                      Lerp(v,
                           Lerp(u,
                                Gradient(PERLIN_HASH[aa + 0], xR32 - 0, yR32 - 0, zR32 - 0),
                                Gradient(PERLIN_HASH[ba + 0], xR32 - 1, yR32 - 0, zR32 - 0)),
                           Lerp(u,
                                Gradient(PERLIN_HASH[ab + 0], xR32 - 0, yR32 - 1, zR32 - 0),
                                Gradient(PERLIN_HASH[bb + 0], xR32 - 1, yR32 - 1, zR32 - 0))),
                      Lerp(v,
                           Lerp(u,
                                Gradient(PERLIN_HASH[aa + 1], xR32 - 0, yR32 - 0, zR32 - 1),
                                Gradient(PERLIN_HASH[ba + 1], xR32 - 1, yR32 - 0, zR32 - 1)),
                           Lerp(u,
                                Gradient(PERLIN_HASH[ab + 1], xR32 - 0, yR32 - 1, zR32 - 1),
                                Gradient(PERLIN_HASH[bb + 1], xR32 - 1, yR32 - 1, zR32 - 1))));
    return((1 + result) * 0.5f);
}

inline r32
PerlinNoise3D(r32 xR32, r32 yR32, r32 zR32,
              r32 frequency,
              r32 lacunarity, //RANGE 1.0 - 4.0
              r32 persistence, //RANGE 0.0 - 1.0
              s32 octaves)//RANGE 1 - 8
{
    r32 result = PerlinNoise3D(xR32, yR32, zR32, frequency);
    r32 amplitude = 1.0f;
    r32 range = 1.0f;
    
    for(s32 i = 1; i < octaves; ++i)
    {
        frequency *= lacunarity;
        amplitude *= persistence;
        range += amplitude;
        result += (PerlinNoise3D(xR32, yR32, zR32, frequency) * amplitude);
    }
    return(result / range);
}