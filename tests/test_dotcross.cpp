/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/*
 * Test of dot product (*) operation.
 */
#include "vecmath.h"

#include "test_common.h"

BTEST(Dot, v3_basic)
{
    ASSERT_FPEQ(vecmath::dot(xunit, yunit), 0.0, EPS);
    ASSERT_FPEQ(vecmath::dot(yunit, zunit), 0.0, EPS);
    ASSERT_FPEQ(vecmath::dot(xunit, zunit), 0.0, EPS);

    vecmath::Vector3f::fptype dotxx = vecmath::dot(xunit, xunit);
    ASSERT_FPEQ(dotxx, 1.0, EPS);

    vecmath::Vector3f::fptype dotyy = vecmath::dot(yunit, yunit);
    ASSERT_FPEQ(dotyy, 1.0, EPS);

    vecmath::Vector3f::fptype dotzz = vecmath::dot(zunit, zunit);
    ASSERT_FPEQ(dotzz, 1.0, EPS);
}

BTEST(Cross, x_basic)
{
    vecmath::Vector3f result = vecmath::cross(yunit, zunit);

    // Y x Z = X
    ASSERT_FPEQ(result.X(), xunit.X(), EPS);
    ASSERT_FPEQ(result.Y(), xunit.Y(), EPS);
    ASSERT_FPEQ(result.Z(), xunit.Z(), EPS);
}

BTEST(Cross, y_basic)
{
    vecmath::Vector3f result = vecmath::cross(zunit, xunit);

    // Z x X = Y
    ASSERT_FPEQ(result.X(), yunit.X(), EPS);
    ASSERT_FPEQ(result.Y(), yunit.Y(), EPS);
    ASSERT_FPEQ(result.Z(), yunit.Z(), EPS);
}

BTEST(Cross, z_basic)
{
    vecmath::Vector3f result = vecmath::cross(xunit, yunit);

    // X x Y = Z
    ASSERT_FPEQ(result.X(), zunit.X(), EPS);
    ASSERT_FPEQ(result.Y(), zunit.Y(), EPS);
    ASSERT_FPEQ(result.Z(), zunit.Z(), EPS);
}
