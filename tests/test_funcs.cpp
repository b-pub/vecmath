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

BTEST(Add, point_vector)
{
    vecmath::Point3f pt;

    pt = pt + xunit;
    ASSERT_FPEQ(pt.X(), 1.0f, EPS);
    ASSERT_FPEQ(pt.Y(), 0.0f, EPS);

    pt = pt + yunit;
    ASSERT_FPEQ(pt.Y(), 1.0f, EPS);
}

BTEST(Add, vector_point)
{
    vecmath::Point3f pt;

    pt = xunit + pt;
    ASSERT_FPEQ(pt.X(), 1.0f, EPS);
    ASSERT_FPEQ(pt.Y(), 0.0f, EPS);

    pt = yunit + pt;
    ASSERT_FPEQ(pt.Y(), 1.0f, EPS);
}

BTEST(Sub, point_point)
{
    vecmath::Point3f pt1 {-2.0f, 0.0f, 0.0f};
    vecmath::Point3f pt2 {0.0f, 2.0f, 0.0f};
    vecmath::Vector3f dir = pt2 - pt1;

    dir.normalize();

    ASSERT_FPEQ(dir.X(), std::sqrt(2.0f)/2, EPS);
    ASSERT_FPEQ(dir.Y(), std::sqrt(2.0f)/2, EPS);
}
