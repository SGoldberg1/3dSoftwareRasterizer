#ifndef ENGINE_MATH_H
#define ENGINE_MATH_H

#define PI (3.141592654)

#define RADIANS(degree) ((degree) * (PI / 180.0f))
#define DEGREES(radians) ((radians) * (180.0f / PI))
#define GRAVITY (9.80991f)

#define INVERSE_255 (1.0f / 255.0f)

#define INT_MAX (0x7fffffff)
#define INT_MIN (0x80000000)


//////////////////////////////// V2 ////////////////////////////////

struct v2
{
    r32 X;
    r32 Y;
};

global_variable const v2 V2_ZERO  = {  0.0f,  0.0f };

global_variable const v2 V2_LEFT  = { -1.0f,  0.0f };
global_variable const v2 V2_RIGHT = {  1.0f,  0.0f };

global_variable const v2 V2_UP    = {  0.0f,  1.0f };
global_variable const v2 V2_DOWN  = {  0.0f, -1.0f };

inline v2
V2(r32 x, r32 y)
{
    v2 result;
    result.X = x;
    result.Y = y;
    return(result);
}

inline v2
operator*(v2 vector, r32 scalar)
{
    v2 result = {};
    result.X = (vector.X * scalar);
    result.Y = (vector.Y * scalar);
    return(result);
}

inline v2
operator*(r32 scalar, v2 vector)
{
    v2 result = (vector * scalar);
    return(result);
}

inline v2 &
operator*=(v2& vector, r32 scalar)
{
    vector = (vector * scalar);
    return(vector);
}

inline v2
operator+(v2 a, v2 b)
{
    v2 result = {};
    result.X = (a.X + b.X);
    result.Y = (a.Y + b.Y);
    return(result);
}

inline v2 &
operator+=(v2& a, v2 b)
{
    a = (a + b);
    return(a);
}

inline v2
operator-(v2 a, v2 b)
{
    v2 result = {};
    result.X = (a.X - b.X);
    result.Y = (a.Y - b.Y);
    return(result);
}

inline v2 &
operator-=(v2& a, v2 b)
{
    a = (a - b);
    return(a);
}


inline v2
operator-(v2 a)
{
    v2 result = {};
    result.X = -a.X;
    result.Y = -a.Y;
    return(result);
}

//////////////////////////////// V3 ////////////////////////////////

union v3
{
    struct//VECTOR
    {
        r32 X;
        r32 Y;
        r32 Z;
    };
    struct//COLOR
    {
        r32 R;
        r32 G;
        r32 B;
    };
};

global_variable const v3 V3_ZERO     = {  0.0f,  0.0f,  0.0f };

global_variable const v3 V3_RIGHT    = {  1.0f,  0.0f,  0.0f };
global_variable const v3 V3_LEFT     = { -1.0f,  0.0f,  0.0f };

global_variable const v3 V3_UP       = {  0.0f,  1.0f,  0.0f };
global_variable const v3 V3_DOWN     = {  0.0f, -1.0f,  0.0f };

global_variable const v3 V3_FORWARD  = {  0.0f,  0.0f, -1.0f };
global_variable const v3 V3_BACKWARD = {  0.0f,  0.0f,  1.0f };

inline v3
operator*(v3 vector, r32 scalar)
{
    v3 result = {};
    result.X = (vector.X * scalar);
    result.Y = (vector.Y * scalar);
    result.Z = (vector.Z * scalar);
    return(result);
}

inline v3
operator*(r32 scalar, v3 vector)
{
    v3 result = (vector * scalar);
    return(result);
}

inline v3 &
operator*=(v3& vector, r32 scalar)
{
    vector = (vector * scalar);
    return(vector);
}

inline v3
operator+(v3 a, v3 b)
{
    v3 result = {};
    result.X = (a.X + b.X);
    result.Y = (a.Y + b.Y);
    result.Z = (a.Z + b.Z);
    return(result);
}

inline v3 &
operator+=(v3& a, v3 b)
{
    a = (a + b);
    return(a);
}

inline v3
operator-(v3 a, v3 b)
{
    v3 result = {};
    result.X = (a.X - b.X);
    result.Y = (a.Y - b.Y);
    result.Z = (a.Z - b.Z);
    return(result);
}

inline v3 &
operator-=(v3& a, v3 b)
{
    a = (a - b);
    return(a);
}

inline v3
operator-(v3 a)
{
    v3 result = {};
    result.X = -a.X;
    result.Y = -a.Y;
    result.Z = -a.Z;
    return(result);
}


//////////////////////////////// V3 ////////////////////////////////

union v4
{
    struct//VECTOR
    {
        r32 X;
        r32 Y;
        r32 Z;
        r32 W;
    };
    struct//COLOR
    {
        r32 A;
        r32 R;
        r32 G;
        r32 B;
    };
};

global_variable const v4 V4_ZERO     = {  0.0f,  0.0f,  0.0f,  1.0f };

global_variable const v4 V4_RIGHT    = {  1.0f,  0.0f,  0.0f,  1.0f };
global_variable const v4 V4_LEFT     = { -1.0f,  0.0f,  0.0f,  1.0f };

global_variable const v4 V4_UP       = {  0.0f,  1.0f,  0.0f,  1.0f  };
global_variable const v4 V4_DOWN     = {  0.0f, -1.0f,  0.0f,  1.0f  };

global_variable const v4 V4_FORWARD  = {  0.0f,  0.0f, -1.0f,  1.0f  };
global_variable const v4 V4_BACKWARD = {  0.0f,  0.0f,  1.0f,  1.0f  };

inline v4
V4(r32 x, r32 y, r32 z, r32 w = 1.0f)
{
    v4 result;
    result.X = x;
    result.Y = y;
    result.Z = z;
    result.W = w;
    return(result);
}

inline v4
operator*(v4 vector, r32 scalar)
{
    v4 result = {};
    result.X = (vector.X * scalar);
    result.Y = (vector.Y * scalar);
    result.Z = (vector.Z * scalar);
    result.W = (vector.W * scalar);
    return(result);
}

inline v4
operator*(r32 scalar, v4 vector)
{
    v4 result = (vector * scalar);
    return(result);
}

inline v4 &
operator*=(v4& vector, r32 scalar)
{
    vector = (vector * scalar);
    return(vector);
}

inline v4
operator+(v4 a, v4 b)
{
    v4 result = {};
    result.X = (a.X + b.X);
    result.Y = (a.Y + b.Y);
    result.Z = (a.Z + b.Z);
    result.W = (a.W + b.W);
    return(result);
}

inline v4 &
operator+=(v4& a, v4 b)
{
    a = (a + b);
    return(a);
}

inline v4
operator-(v4 a, v4 b)
{
    v4 result = {};
    result.X = (a.X - b.X);
    result.Y = (a.Y - b.Y);
    result.Z = (a.Z - b.Z);
    result.W = (a.W - b.W);
    return(result);
}

inline v4 &
operator-=(v4& a, v4 b)
{
    a = (a - b);
    return(a);
}

inline v4
operator-(v4 a)
{
    v4 result = {};
    result.X = -a.X;
    result.Y = -a.Y;
    result.Z = -a.Z;
    result.W = -a.W;
    return(result);
}


//////////////////////////////// MATRIX ////////////////////////////////

/*NOTE:
ALL MATRIX OPERATIONS ARE ASSUMED COLUMN MAJOR:

COLUMN MAJOR:
    |a b|   |x|   |ax + by|
    |c d| x |y| = |cx + dy|
    
    ROW MAJOR:
    
    |x y| X |a b| = |ax + cy|
         .       |c d|   |bx + dy|
         
         NOTICE THE RESULT IS DIFFERENT
         BOTH CAN RESULT IN THE SAME ANSWER BY TRANSPOSING THE MATRIX
         
|a b| => |a c|
         |c d|    |b d|
         
*/

struct m4x4
{
    r32 E[4][4];
};

struct m3x3
{
    r32 E[3][3];
};

struct m2x2
{
    r32 E[2][2];
};
#endif