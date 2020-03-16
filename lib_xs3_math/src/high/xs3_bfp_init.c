


#include "xs3_math.h"

#include "low/xs3_math_util_low.h"
#include "low/xs3_bfp_init_low.h"


void bfp_init_vect_s16(
    bfp_s16_t* a, 
    int16_t* data, 
    const exponent_t exp, 
    const unsigned length,
    const unsigned calc_hr)
{
    a->data = data;
    a->length = length;
    a->exp = exp;

    if(calc_hr){
        bfp_cls_vect_s16(a);
    } else {
        a->hr = 0;
    }
}



void bfp_init_vect_s32(
    bfp_s32_t* a, 
    int32_t* data, 
    const int exp, 
    const unsigned length,
    const unsigned calc_hr)
{
    a->data = data;
    a->length = length;
    a->exp = exp;

    if(calc_hr){
        bfp_cls_vect_s32(a);
    } else {
        a->hr = 0;
    }
}


void bfp_init_vect_complex_s16(
    bfp_complex_s16_t* a, 
    int16_t* real_data,
    int16_t* imag_data, 
    const int exp, 
    const unsigned length,
    const unsigned calc_hr)
{
    a->real = real_data;
    a->imag = imag_data;
    a->length = length;
    a->exp = exp;

    if(calc_hr){
        bfp_cls_vect_complex_s16(a);
    } else {
        a->hr = 0;
    }
}


void bfp_init_vect_complex_s32(
    bfp_complex_s32_t* a, 
    complex_s32_t* data, 
    const int exp, 
    const unsigned length,
    const unsigned calc_hr)
{
    a->data = data;
    a->length = length;
    a->exp = exp;

    if(calc_hr){
        bfp_cls_vect_complex_s32(a);
    } else {
        a->hr = 0;
    }
}




void bfp_init_vect_ch_pair_s16(
    bfp_ch_pair_s16_t* a, 
    ch_pair_s16_t* data, 
    const int exp, 
    const unsigned length,
    const unsigned calc_hr)
{
    a->data = data;
    a->length = length;
    a->exp = exp;

    if(calc_hr){
        bfp_cls_vect_ch_pair_s16(a);
    } else {
        a->hr = 0;
    }
}


    
void bfp_init_vect_ch_pair_s32(
    bfp_ch_pair_s32_t* a, 
    ch_pair_s32_t* data, 
    const int exp, 
    const unsigned length,
    const unsigned calc_hr)
{
    a->data = data;
    a->length = length;
    a->exp = exp;

    if(calc_hr){
        bfp_cls_vect_ch_pair_s32(a);
    } else {
        a->hr = 0;
    }
}






void bfp_set_vect_s16(
    bfp_s16_t* a,
    const int16_t value,
    const int exp)
{
    a->exp = exp;
    a->hr = CLS(value);
    xs3_set_array_s16(a->data, value, a->length);
}


void bfp_set_vect_s32(
    bfp_s32_t* a,
    const int32_t value,
    const int exp)
{
    a->exp = exp;
    a->hr = CLS(value);
    xs3_set_array_s32(a->data, value, a->length);
}



void bfp_set_vect_complex_s16(
    bfp_complex_s16_t* a,
    const complex_s16_t value,
    const int exp)
{
    a->exp = exp;
    a->hr = CLS(value.re) < CLS(value.im)? CLS(value.re) : CLS(value.im);

    xs3_set_array_s16( a->real, value.re, a->length );
    xs3_set_array_s16( a->imag, value.im, a->length );
}



void bfp_set_vect_complex_s32(
    bfp_complex_s32_t* a,
    const complex_s32_t value,
    const int exp)
{
    a->exp = exp;
    a->hr = CLS(value.re) < CLS(value.im)? CLS(value.re) : CLS(value.im);
    xs3_set_array_complex_s32( a->data, value.re, value.im, a->length);
}



void bfp_set_vect_ch_pair_s16(
    bfp_ch_pair_s16_t* a,
    const ch_pair_s16_t value,
    const int exp)
{
    a->exp = exp;
    a->hr = CLS(value.ch_a) < CLS(value.ch_b)? CLS(value.ch_a) : CLS(value.ch_b);
    int32_t v = (value.ch_a << 16 | value.ch_b);
    xs3_set_array_s32( (int32_t*) a->data, v, a->length);
}



void bfp_set_vect_ch_pair_s32(
    bfp_ch_pair_s32_t* a,
    const ch_pair_s32_t value,
    const int exp)
{
    a->exp = exp;
    a->hr = CLS(value.ch_a) < CLS(value.ch_b)? CLS(value.ch_a) : CLS(value.ch_b);
    xs3_set_array_complex_s32( (complex_s32_t*) a->data, value.ch_a, value.ch_b, a->length);
}