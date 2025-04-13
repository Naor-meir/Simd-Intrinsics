#include <xmmintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pmmintrin.h>

#define MAX_STR 255

float formula1(float *x, unsigned int length)
{
    // number of loops when the loop is 4 bytes
    size_t len = length / 4;
    // result of the formula : sum {sqrt(x[i])}
    float result_1 = 0.0f;
    // result of the formula : mult {x[i]^2 + 1}
    float result_2 = 0.0f;
    for (size_t i = 0; i < len; i++)
    {
        // Load 4 floats from the array into an SSE register
        __m128 vec1 = _mm_loadu_ps(x);
        // Calculate the square root of each element in the vector
        __m128 sqrt_vec = _mm_sqrt_ps(vec1);
        // calculate the sum of the square roots using horizontal addition : [v0+v1, v2+v3, v0+v1, v2+v3]
        __m128 t1 = _mm_hadd_ps(sqrt_vec, sqrt_vec);
        //[total_sum, total_sum, total_sum, total_sum]
        __m128 t2 = _mm_hadd_ps(t1, t1);
        // Store the result in a temporary variable
        result_1 += _mm_cvtss_f32(t2);
        //----------------------------------------------------
        // Load 4 floats from the array into an SSE register
        __m128 vec2 = _mm_loadu_ps(x);
        // Calculate the square of each element in the vector
        __m128 squared = _mm_mul_ps(vec2, vec2);
        // set the value of 1.0f in all elements of the vector
        __m128 ones = _mm_set1_ps(1.0f);
        // Calculate the sum of squares and 1.0f
        __m128 squar_plus_one = _mm_add_ps(squared, ones);
        // shuffle the elements of the vector to prepare for multiplication : [v0,v1,v2,v3] -> [v1,v1,v3,v3]
        // move the 1th and 3th elements of the vector to the 0th and 2th elements of the vector : [v0,v1,v2,v3] -> [v1,v1,v3,v3]
        __m128 shuf = _mm_movehdup_ps(squar_plus_one);
        // multiply the elements of the vector : [v1,v1,v3,v3] with [v0,v1,v2,v3] -> [v0*v1,v1*v1,v2*v3,v3*v3]
        __m128 curr_mult = _mm_mul_ps(squar_plus_one, shuf);
        // shuffle the elements of the vector to prepare for multiplication : [v0*v1,v1*v1,v2*v3,v3*v3] -> [v2*v3,v3*v3,?,?]
        // move the high 2 elements of the vector to the low 2 elements of the vector : [v0*v1,v1*v1,v2*v3,v3*v3] -> [v2*v3,v3*v3,v2*v3,v3*v3]
        __m128 temp = _mm_movehl_ps(curr_mult, curr_mult);
        // multiply the elements of the vector like scalar multiplication : cuur_mult[0]*temp[0]=xmm[0]*xmm[1]*xmm[2]*xmm[3]
        __m128 scalar_prod = _mm_mul_ss(curr_mult, temp);
        // Store the result in a temporary variable
        result_2 += _mm_cvtss_f32(scalar_prod);
    }
    // calculat the third root of the result_1
    float third_root_res = powf(result_1, 1.0f / 3.0f);
    // calculate the division of the third root of the result_1 by the result_2
    float div_res = third_root_res / result_2;
    // calculate the final result of the formula : sqrt(1 + div_res)
    float final_res = sqrt(1.0f + div_res);
    return final_res;
}
