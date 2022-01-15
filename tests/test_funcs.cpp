/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/*
 * Test of common functions: length, normalization, addition, and subtraction.
 */
#include "vecmath.h"

#include "test_common.h"

BTEST(Length, basic)
{
    ASSERT_FPEQ(xunit.length(), 1.0f, EPS);
    ASSERT_FPEQ(yunit.length(), 1.0f, EPS);
    ASSERT_FPEQ(zunit.length(), 1.0f, EPS);
}

BTEST(Length, basic_norm)
{
    vecmath::Vector3f xdir {4.0f, 0.0f, 0.0f};
    ASSERT_FPEQ(xdir.length(), 4.0f, EPS);

    vecmath::Vector3f::fptype len = xdir.normalize().length();
    ASSERT_FPEQ(len, 1.0f, EPS);
}

BTEST(Length, extended_norm)
{
    // Make a direction 3 units +X, 3 units +Y.
    vecmath::Vector3f dir {3.0f, 3.0f, 0.0f};
    ASSERT_FPEQ(dir.length(), std::sqrt(18.0f), EPS);

    vecmath::Vector3f::fptype len = dir.normalize().length();
    ASSERT_FPEQ(len, 1.0f, EPS);
}

BTEST(Add, extended_norm)
{
    vecmath::Vector3f dir;

    // Make a direction 3 units +X, 3 units +Y.
    // Len = sqrt(3^2 + 3^2) = sqrt(18)
    dir = xunit + yunit + xunit + yunit + yunit + xunit;
    ASSERT_FPEQ(dir.length(), std::sqrt(18.0f), EPS);

    vecmath::Vector3f::fptype len = dir.normalize().length();
    ASSERT_FPEQ(len, 1.0f, EPS);
}

BTEST(Sub, extended_norm)
{
    vecmath::Vector3f dir;

    // Make a direction 3 units +X, 3 units -Y.
    dir = xunit - yunit + xunit - yunit - yunit + xunit;
    ASSERT_FPEQ(dir.length(), std::sqrt(18.0f), EPS);

    vecmath::Vector3f::fptype len = dir.normalize().length();
    ASSERT_FPEQ(len, 1.0f, EPS);
}

BTEST(Add, vector_vector)
{
    vecmath::Vector3f v;

    v = v + xunit;
    ASSERT_FPEQ(v.X(), 1.0f, EPS);
    ASSERT_FPEQ(v.Y(), 0.0f, EPS);

    v = v + yunit;
    ASSERT_FPEQ(v.Y(), 1.0f, EPS);
}
