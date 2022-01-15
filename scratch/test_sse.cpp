/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/**
 * The tests here aren't so much unit tests as sample
 * code to (re)learn how SIMD/SSE instructions work.
 *
 */
#include "vecmath.h"
#include "test_common.h"

#include <pmmintrin.h>

/*
    std::cout << "XMM: set result = "
              << result[0] << ", " << result[1] << ", "
              << result[2] << ", " << result[3] << '\n';
 */

BTEST(XMM, set)
{
    __m128 result;

    result = _mm_set_ps(3.0, 2.0, 1.0, 1.0);

    ASSERT_FPEQ(result[0], 1.0f, EPS);
    ASSERT_FPEQ(result[1], 1.0f, EPS);
    ASSERT_FPEQ(result[2], 2.0f, EPS);
    ASSERT_FPEQ(result[3], 3.0f, EPS);

    result = _mm_setr_ps(3.0, 2.0, 1.0, 1.0);

    ASSERT_FPEQ(result[0], 3.0f, EPS);
    ASSERT_FPEQ(result[1], 2.0f, EPS);
    ASSERT_FPEQ(result[2], 1.0f, EPS);
    ASSERT_FPEQ(result[3], 1.0f, EPS);
}

BTEST(XMM, mul)
{
    __m128 a {1, 2, 3, 4};
    __m128 s {2, 2, 2, 2};
    __m128 result = _mm_mul_ps(a, s);

    ASSERT_FPEQ(result[0], 2.0f, EPS);
    ASSERT_FPEQ(result[1], 4.0f, EPS);
    ASSERT_FPEQ(result[2], 6.0f, EPS);
    ASSERT_FPEQ(result[3], 8.0f, EPS);
}

BTEST(XMM, add)
{
    __m128 a {1, 2, 3, 4};
    __m128 b {5, 6, 7, 8};

    __m128 result = _mm_add_ps(a, b);

    ASSERT_FPEQ(result[0], 6.0f, EPS);
    ASSERT_FPEQ(result[1], 8.0f, EPS);
    ASSERT_FPEQ(result[2], 10.0f, EPS);
    ASSERT_FPEQ(result[3], 12.0f, EPS);
}

BTEST(XMM, hadd)
{
    __m128 a {1, 2, 3, 4}; // sum 3, 7
    __m128 b {2, 2, 4, 4}; // sum 4, 8

    __m128 result = _mm_hadd_ps(a, b); // [3, 7, 4, 8]

    ASSERT_FPEQ(result[0], 3.0f, EPS);
    ASSERT_FPEQ(result[1], 7.0f, EPS);
    ASSERT_FPEQ(result[2], 4.0f, EPS);
    ASSERT_FPEQ(result[3], 8.0f, EPS);

    // Here's how to sum the 4 elements of vector 'a':
    result = _mm_hadd_ps(a, _mm_setzero_ps()); // [3, 7, 0, 0]
    result = _mm_hadd_ps(result, _mm_setzero_ps()); // [10, 0, 0, 0]

    ASSERT_FPEQ(result[0], 10.0f, EPS);
    ASSERT_FPEQ(result[1], 0.0f, EPS);
}

BTEST(XMM, sqrt)
{
    __m128 a {4, 9, 16, 25};

    __m128 result = _mm_sqrt_ps(a);

    ASSERT_FPEQ(result[0], 2.0f, EPS);
    ASSERT_FPEQ(result[1], 3.0f, EPS);
    ASSERT_FPEQ(result[2], 4.0f, EPS);
    ASSERT_FPEQ(result[3], 5.0f, EPS);
}

BTEST(XMM, unpacks_moves)
{
    __m128 a {1, 2, 3, 4};
    __m128 b {5, 6, 7, 8};
    __m128 result;

    result = _mm_unpacklo_ps(a, b); // [a0, b0, a1, b1]

    ASSERT_FPEQ(result[0], 1.0f, EPS);
    ASSERT_FPEQ(result[1], 5.0f, EPS);
    ASSERT_FPEQ(result[2], 2.0f, EPS);
    ASSERT_FPEQ(result[3], 6.0f, EPS);

    result = _mm_unpackhi_ps(a, b); // [a2, b2, a3, b3]

    ASSERT_FPEQ(result[0], 3.0f, EPS);
    ASSERT_FPEQ(result[1], 7.0f, EPS);
    ASSERT_FPEQ(result[2], 4.0f, EPS);
    ASSERT_FPEQ(result[3], 8.0f, EPS);

    result = _mm_movehl_ps(a, b); // [b2, b3, a2, a3]

    ASSERT_FPEQ(result[0], 7.0f, EPS);
    ASSERT_FPEQ(result[1], 8.0f, EPS);
    ASSERT_FPEQ(result[2], 3.0f, EPS);
    ASSERT_FPEQ(result[3], 4.0f, EPS);

    result = _mm_movelh_ps(a, b); // [a0, a1, b0, b1]

    ASSERT_FPEQ(result[0], 1.0f, EPS);
    ASSERT_FPEQ(result[1], 2.0f, EPS);
    ASSERT_FPEQ(result[2], 5.0f, EPS);
    ASSERT_FPEQ(result[3], 6.0f, EPS);
}

BTEST(XMM, transpose)
{
    __m128 r0 {1, 2, 3, 4};                 // four rows of a matrix
    __m128 r1 {5, 6, 7, 8};
    __m128 r2 {9, 10, 11, 12};
    __m128 r3 {13, 14, 15, 16};

    __m128 tmp0, tmp1, tmp2, tmp3;

    /*
     * The instructions here are from the macro
     * _MM_TRANSPOSE4_PS() to see how the data moves.
     */
    tmp0 = _mm_unpacklo_ps(r0, r1); // [ 1,  5,  2, 6]
    tmp1 = _mm_unpackhi_ps(r0, r1); // [ 3,  7,  4,  8]
    tmp2 = _mm_unpacklo_ps(r2, r3); // [ 9, 13, 10, 14]
    tmp3 = _mm_unpackhi_ps(r2, r3); // [11, 15, 12, 16]

    r0 = _mm_movelh_ps(tmp0, tmp2); // [ 1,  5,  9, 13]
    r1 = _mm_movehl_ps(tmp2, tmp0); // [ 2,  6, 10, 14]
    r2 = _mm_movelh_ps(tmp1, tmp3); // [ 3,  7, 11, 15]
    r3 = _mm_movehl_ps(tmp3, tmp1); // [ 4,  8, 12, 16]

    ASSERT_FPEQ(r0[2], 9.0f, EPS);
    ASSERT_FPEQ(r1[0], 2.0f, EPS);
    ASSERT_FPEQ(r2[1], 7.0f, EPS);
    ASSERT_FPEQ(r3[2], 12.0f, EPS);
}

BTEST(XMM, veclength)
{
    __m128 v {3.0, 4.0, 0.0, 1.0}; // x,y,z,w
    __m128 v2 = _mm_mul_ps(v, v);
    v2[3] = 0.0;                            // clear W
    __m128 sum = _mm_hadd_ps(v2, _mm_setzero_ps());
    sum = _mm_hadd_ps(sum, _mm_setzero_ps()); // sum[0] = sum(all elements of v2)
    float length = std::sqrt(sum[0]);

    ASSERT_FPEQ(length, 5.0f, EPS);
}

BTEST(Timed, Matrix3fmm_mm_mult)
{
    Timer timer;

    vecmath::Matrix3fmm a;
    vecmath::Matrix3fmm translate = vecmath::Matrix3fmm::translation(1.0, 2.0, 1.0);
    vecmath::Matrix3fmm const identity;

    timer.start();
    for (uint32_t i=0; i<1000000; ++i)
    {
        a = identity * translate;
        ASSERT_FPEQ(a.get(1,3), 2.0f, EPS);
    }
    timer.end();

    std::cout << "Matrix3fmm mm_mult: 1,000,000 = " << timer.elapsed() << " msec\n";
    std::cout << "Matrix3fmm mm_mult: rate = " << (1.0e3f / timer.elapsed()) << " Mmults/sec\n";
}


BTEST(Timed, Matrix3fmm_mv_mult)
{
    Timer timer;

    vecmath::Matrix3fmm translate = vecmath::Matrix3fmm::translation(1.0, 2.0, 1.0);
    vecmath::Vector3fmm pt {1.0, 1.0, 1.0};

    timer.start();
    for (uint32_t i=0; i<1000000; ++i)
    {
        vecmath::Vector3fmm a = translate * pt;
        ASSERT_FPEQ(a.Y(), 3.0f, EPS);
    }
    timer.end();

    std::cout << "Matrix3fmm mv_mult: 1,000,000 = " << timer.elapsed() << " msec\n";
    std::cout << "Matrix3fmm mv_mult: rate = " << (1.0e3f / timer.elapsed()) << " Mmults/sec\n";
}
