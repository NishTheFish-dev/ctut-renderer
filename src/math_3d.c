#include "math_3d.h"
#include <math.h>

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

// --- Vector helper functions ---

Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

Vec3 vec3_normalize(Vec3 v) {
    float len_sq = vec3_dot(v, v);
    if (len_sq == 0.0f) return v; // Avoid dividing by 0
    float inv_len = 1.0f / sqrtf(len_sq);
    return (Vec3){ v.x * inv_len, v.y * inv_len, v.z * inv_len };
}

// --- Matrix helper functions ---

Mat4 mat4_identity(void) {
    Mat4 res = {0}; // Initialize all to 0
    res.m[0][0] = 1.0f;
    res.m[1][1] = 1.0f;
    res.m[2][2] = 1.0f;
    res.m[3][3] = 1.0f;
    return res;
}

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v) {
    Vec4 res;
    res.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    res.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    res.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    res.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
    return res;
}

Mat4 mat4_mul_mat4(Mat4 a, Mat4 b) {
    Mat4 res = {0};
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            res.m[r][c] = a.m[r][0] * b.m[0][c] +
                          a.m[r][1] * b.m[1][c] +
                          a.m[r][2] * b.m[2][c] +
                          a.m[r][3] * b.m[3][c];
        }
    }
    return res;
}

Mat4 mat4_translate(float tx, float ty, float tz) {
    Mat4 m = mat4_identity();
    m.m[0][3] = tx;
    m.m[1][3] = ty;
    m.m[2][3] = tz;
    return m;
}
Mat4 mat4_rotate_y(float angle) {
    Mat4 m = mat4_identity();
    float c = cosf(angle);
    float s = sinf(angle);
    m.m[0][0] = c;
    m.m[0][2] = s;
    m.m[2][0] = -s;
    m.m[2][2] = c;
    return m;
}
Mat4 mat4_perspective(float fov, float aspect, float near, float far) {
    Mat4 m = {0};
    float tan_half_fov = tanf(fov / 2.0f);
    m.m[0][0] = 1.0f / (aspect * tan_half_fov);
    m.m[1][1] = 1.0f / tan_half_fov;
    m.m[2][2] = -(far + near) / (far - near);
    m.m[2][3] = -(2.0f * far * near) / (far - near);
    m.m[3][2] = -1.0f; // This stores -Z into W for perspective divide
    return m;
}