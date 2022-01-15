/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/**
 * Unit tests for reporting basic timed operations
 */
#include "vecmath.h"
#include "test_common.h"
#include "Timer.h"

BTEST(Timed, Matrix3f_creation)
{
    Timer timer;

    timer.start();
    for (uint32_t i=0; i<1000000; ++i)
    {
        vecmath::Matrix3f m;

        // need to access some part of m so compiler won't optimize it away
        ASSERT_FPEQ(m.get(1,1), vecmath::Matrix3f::fptype(1.0), EPS);
    }
    timer.end();

    std::cout << "Matrix3f creation: 1,000,000 = " << timer.elapsed() << " msec\n";
}

BTEST(Timed, Matrix3f_copy)
{
    Timer timer;

    vecmath::Matrix3f a;
    vecmath::Matrix3f translate = vecmath::Matrix3f::translation(1.0, 2.0, 1.0);
    vecmath::Matrix3f const identity;

    uint32_t i;
    timer.start();
    for (i=0; i<5000000; ++i)
    {
        a = identity;
        if (!vecmath::fpequal(a.get(1,3), 0.0f))
            break;
        a = translate;
        if (!vecmath::fpequal(a.get(1,3), 2.0f))
            break;
    }
    timer.end();

    if (i != 5000000)
    {
        FAIL() << "Matrix copying failed (bug)\n";
    }

    std::cout << "Matrix3f copy: 10,000,000 = " << timer.elapsed() << " msec\n";
}

BTEST(Timed, Matrix3f_mm_mult)
{
    Timer timer;

    vecmath::Matrix3f a;
    vecmath::Matrix3f translate = vecmath::Matrix3f::translation(1.0, 2.0, 1.0);
    vecmath::Matrix3f const identity;

    timer.start();
    for (uint32_t i=0; i<1000000; ++i)
    {
        a = identity * translate;
        ASSERT_FPEQ(a.get(1,3), vecmath::Matrix3f::fptype(2.0), EPS);
    }
    timer.end();

    std::cout << "Matrix3f mm_mult: 1,000,000 = " << timer.elapsed() << " msec\n";
    std::cout << "Matrix3f mm_mult: rate = " << (1.0e3f / timer.elapsed()) << " Mmults/sec\n";
}

BTEST(Timed, Matrix3f_mv_mult)
{
    Timer timer;

    vecmath::Matrix3f translate = vecmath::Matrix3f::translation(1.0, 2.0, 1.0);
    vecmath::Vector3f pt {1.0, 1.0, 1.0};

    timer.start();
    for (uint32_t i=0; i<1000000; ++i)
    {
        vecmath::Vector3f a = translate * pt;
        ASSERT_FPEQ(a.Y(), 3.0f, EPS);
    }
    timer.end();

    std::cout << "Matrix3f mv_mult: 1,000,000 = " << timer.elapsed() << " msec\n";
    std::cout << "Matrix3f mv_mult: rate = " << (1.0e3f / timer.elapsed()) << " Mmults/sec\n";
}
