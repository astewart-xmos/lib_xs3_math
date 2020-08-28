#pragma once

#include "xs3_math_types.h"

typedef union {
    int8_t s8[32];
    int16_t s16[16];
    int32_t s32[8];
    complex_s32_t c32[4];
} xs3_vpu_vect_t;

extern const xs3_vpu_vect_t vpu_vec_zero;
extern const xs3_vpu_vect_t vpu_vec_neg_1;

extern const complex_s32_t vpu_vec_complex_pos_j[4];
extern const complex_s32_t vpu_vec_complex_ones[4];
extern const complex_s32_t vpu_vec_complex_conj_op[4];
extern const complex_s32_t vpu_vec_complex_neg_j[4];
extern const complex_s32_t vpu_vec_complex_neg_ones[4];

extern const int32_t vpu_vec_ones_s32[8];
extern const int32_t vpu_vec_neg_ones_s32[8];

extern const int16_t vpu_vec_0x0001[16];
extern const int16_t vpu_vec_0x4000[16];
extern const int16_t vpu_vec_neg_0x4000[16];

extern const int8_t vpu_vec_0x01[32];
extern const int8_t vpu_vec_0x40[32];