#pragma once

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float x, y, z, w
} Vec4;

typedef struct {
    float m[4][4];
} Mat4;

// --- Vector Operations ---
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Vec3 vec3_normalize(Vec3 v);

// --- Matrix Operations ---
Mat4 mat4_identity(void);
Vec4 mat4_mul_vec4(Mat4 m, Vec4 v);
Mat4 mat4_mul_mat4(Mat4 a, Mat4 b);