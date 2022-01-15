/*
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
#include <vecmath.h>

namespace vecmath {

/*
 * Operators and utility functions for SSE vectors.
 */

static void vm_mult(__m128 &result, __m128 const& v, __m128 const (&m)[4])
{
    /* vm_mult:
    r[0] = (v[0]*m[0][0] + v[1]*m[1][0] + v[2]*m[2][0] + v[3]*m[3][0]);
    r[1] = (v[0]*m[0][1] + v[1]*m[1][1] + v[2]*m[2][1] + v[3]*m[3][1]);
    r[2] = (v[0]*m[0][2] + v[1]*m[1][2] + v[2]*m[2][2] + v[3]*m[3][2]);
    r[3] = (v[0]*m[0][3] + v[1]*m[1][3] + v[2]*m[2][3] + v[3]*m[3][3]);
    */

    // Do column multiplications:
    __m128 r0 = _mm_mul_ps(_mm_set1_ps(v[0]), m[0]);
    __m128 r1 = _mm_mul_ps(_mm_set1_ps(v[1]), m[1]);
    __m128 r2 = _mm_mul_ps(_mm_set1_ps(v[2]), m[2]);
    __m128 r3 = _mm_mul_ps(_mm_set1_ps(v[3]), m[3]);

    // Then add across to get result vector
    r0 = _mm_add_ps(r0, r1);
    r2 = _mm_add_ps(r2, r3);
    result = _mm_add_ps(r0, r2);
}

static void mv_mult(__m128 &result, __m128 const (&m)[4], __m128 const& v)
{
    // Multiply each row of m[] by vector v[] and sum (dot product).
    __m128 r0 = _mm_mul_ps(m[0], v);
    __m128 r1 = _mm_mul_ps(m[1], v);
    __m128 r2 = _mm_mul_ps(m[2], v);
    __m128 r3 = _mm_mul_ps(m[3], v);

    // SSE3 horizontal adds complete the additions for the dot products.
    r0 = _mm_hadd_ps(r0, r1);
    r2 = _mm_hadd_ps(r2, r3);
    result = _mm_hadd_ps(r0, r2);
}

Matrix3fmm operator*(Matrix3fmm const& a, Matrix3fmm const& b)
{
    Matrix3fmm result;

    vm_mult(result.m_m[0], a.m_m[0], b.m_m);
    vm_mult(result.m_m[1], a.m_m[1], b.m_m);
    vm_mult(result.m_m[2], a.m_m[2], b.m_m);
    vm_mult(result.m_m[3], a.m_m[3], b.m_m);

    return result;
}

Vector3fmm operator*(Matrix3fmm const& m, Vector3fmm const& v)
{
    Vector3fmm result;
    mv_mult(result.m_v, m.m_m, v.m_v);
    return result;
}

Vector3fmm operator*(Vector3fmm const& v, Matrix3fmm const& m)
{
    Vector3fmm result;
    vm_mult(result.m_v, v.m_v, m.m_m);
    return result;
}

} // ::vecmath
