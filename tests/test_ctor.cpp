/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/**
 * Unit tests for vecmath constructors
 */
#include "vecmath.h"
#include "test_common.h"

BTEST(Ctor, Vector3f_default)
{
    vecmath::Vector3f v3;

    ASSERT_EQ(v3.X(), 0.0);
    ASSERT_EQ(v3.Y(), 0.0);
    ASSERT_EQ(v3.Z(), 0.0);
    ASSERT_EQ(v3.W(), 1.0);
}

BTEST(Ctor, Vector3f_2arg)
{
    constexpr vecmath::Vector3f::fptype val {1.2};
    vecmath::Vector3f v3(val, 2.0*val);

    ASSERT_EQ(v3.X(), val);
    ASSERT_EQ(v3.Y(), 2.0*val);
    ASSERT_EQ(v3.Z(), 0.0);
    ASSERT_EQ(v3.W(), 1.0);
}

BTEST(Ctor, Vector3f_3arg)
{
    constexpr vecmath::Vector3f::fptype val {1.2};
    vecmath::Vector3f v3(val, 2.0*val, 3.0*val);

    ASSERT_EQ(v3.X(), val);
    ASSERT_EQ(v3.Y(), 2.0*val);
    ASSERT_EQ(v3.Z(), 3.0*val);
    ASSERT_EQ(v3.W(), 1.0);
}

BTEST(Ctor, Vector3f_copy)
{
    vecmath::Vector3f v3(xunit);

    ASSERT_EQ(v3.X(), 1.0);
    ASSERT_EQ(v3.Y(), 0.0);
    ASSERT_EQ(v3.Z(), 0.0);
    ASSERT_EQ(v3.W(), 1.0);
}

BTEST(Ctor, Vector3f_assign)
{
    vecmath::Vector3f v3;

    v3 = xunit;

    ASSERT_EQ(v3.X(), 1.0);
    ASSERT_EQ(v3.Y(), 0.0);
    ASSERT_EQ(v3.Z(), 0.0);
    ASSERT_EQ(v3.W(), 1.0);
}
