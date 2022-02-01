#ifndef MATH_IO_H
#define MATH_IO_H

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "mat2.h"
#include "mat3.h"
#include "mat4.h"

void vec2_print(struct Vec2 vec);
void vec3_print(struct Vec3 vec);
void vec4_print(struct Vec4 vec);

void mat2_print(struct Mat2 mat);
void mat3_print(struct Mat3 mat);
void mat4_print(struct Mat4 mat);

#endif