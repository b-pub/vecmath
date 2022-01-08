/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/**
 * Unit tests for matrix
 */
#include "vecmath.h"
#include "test_common.h"

BTEST(Matrix3Float, Matrix3f_ctorIdentity)
{
    /*
     * This test confirms the default constructor
     * creates an identity matrix.
     */
    vecmath::Matrix3f m;

    ASSERT_FPEQ(m.get(0,0), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(m.get(1,1), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(m.get(2,2), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(m.get(3,3), vecmath::Matrix3f::one, EPS);

    ASSERT_FPEQ(m.get(0,1), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(m.get(0,2), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(m.get(0,3), vecmath::Matrix3f::zero, EPS);

    ASSERT_FPEQ(m.get(1,0), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(m.get(1,2), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(m.get(1,3), vecmath::Matrix3f::zero, EPS);

    ASSERT_FPEQ(m.get(2,0), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(m.get(2,1), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(m.get(2,3), vecmath::Matrix3f::zero, EPS);

    ASSERT_FPEQ(m.get(3,0), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(m.get(3,1), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(m.get(3,2), vecmath::Matrix3f::zero, EPS);
}

BTEST(Matrix3Float, Matrix3f_getIndexCheck)
{
    /*
     * This test confirms indices passed to the get()
     * accessor are restricted to [0,3] inclusive.
     */
    vecmath::Matrix3f m;

    try {
        (void)m.get(-2,0);
        FAIL() << "get(-2,0) didn't throw expected exception\n";
    }
    catch (vecmath::index_error &) {
        // expected
    }

    try {
        (void)m.get(5,0);
        FAIL() << "get(5,0) didn't throw expected exception\n";
    }
    catch (vecmath::index_error &) {
        // expected
    }

    try {
        (void)m.get(0,-2);
        FAIL() << "get(0,-2) didn't throw expected exception\n";
    }
    catch (vecmath::index_error &) {
        // expected
    }

    try {
        (void)m.get(0,5);
        FAIL() << "get(0,5) didn't throw expected exception\n";
    }
    catch (vecmath::index_error &) {
        // expected
    }
}

BTEST(Matrix3Float, scale)
{
    vecmath::Matrix3f::fptype const two = 2.0f;
    vecmath::Matrix3f m = vecmath::Matrix3f::scale(two, two, two);
    ASSERT_FPEQ(m.get(0,0), two, EPS);
    ASSERT_FPEQ(m.get(1,1), two, EPS);
    ASSERT_FPEQ(m.get(2,2), two, EPS);
}

BTEST(Matrix3Float, translate)
{
    vecmath::Matrix3f::fptype const two = 2.0f;
    vecmath::Matrix3f m = vecmath::Matrix3f::translation(two, two, two);
    ASSERT_FPEQ(m.get(0,3), two, EPS);
    ASSERT_FPEQ(m.get(1,3), two, EPS);
    ASSERT_FPEQ(m.get(2,3), two, EPS);
}

BTEST(Matrix3Float, rotateX)
{
    vecmath::Matrix3f m = vecmath::Matrix3f::rotateX(M_PI/2.0);

    ASSERT_FPEQ(m.get(0,0), vecmath::Matrix3f::one, EPS);

    ASSERT_FPEQ(m.get(1,1), vecmath::Matrix3f::zero, EPS); // cos
    ASSERT_FPEQ(m.get(2,2), vecmath::Matrix3f::zero, EPS); // cos
    ASSERT_FPEQ(m.get(1,2), -vecmath::Matrix3f::one, EPS); // -sin
    ASSERT_FPEQ(m.get(2,1), vecmath::Matrix3f::one, EPS); // sin
}

BTEST(Matrix3Float, rotateY)
{
    vecmath::Matrix3f m = vecmath::Matrix3f::rotateY(M_PI/2.0);

    ASSERT_FPEQ(m.get(1,1), vecmath::Matrix3f::one, EPS);

    ASSERT_FPEQ(m.get(0,0), vecmath::Matrix3f::zero, EPS); // cos
    ASSERT_FPEQ(m.get(2,2), vecmath::Matrix3f::zero, EPS); // cos
    ASSERT_FPEQ(m.get(0,2), vecmath::Matrix3f::one, EPS); // sin
    ASSERT_FPEQ(m.get(2,0), -vecmath::Matrix3f::one, EPS); // -sin
}

BTEST(Matrix3Float, rotateZ)
{
    vecmath::Matrix3f m = vecmath::Matrix3f::rotateZ(M_PI/2.0);

    ASSERT_FPEQ(m.get(2,2), vecmath::Matrix3f::one, EPS);

    ASSERT_FPEQ(m.get(0,0), vecmath::Matrix3f::zero, EPS); // cos
    ASSERT_FPEQ(m.get(1,1), vecmath::Matrix3f::zero, EPS); // cos
    ASSERT_FPEQ(m.get(0,1), -vecmath::Matrix3f::one, EPS); // -sin
    ASSERT_FPEQ(m.get(1,0), vecmath::Matrix3f::one, EPS); // sin
}

BTEST(Matrix3Float, multVM_identity)
{
    vecmath::Matrix3f m;

    auto xprime = xunit * m;
    ASSERT_FPEQ(xprime.X(), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(xprime.Y(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(xprime.Z(), vecmath::Matrix3f::zero, EPS);

    auto yprime = yunit * m;
    ASSERT_FPEQ(yprime.X(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(yprime.Y(), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(yprime.Z(), vecmath::Matrix3f::zero, EPS);

    auto zprime = zunit * m;
    ASSERT_FPEQ(zprime.X(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(zprime.Y(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(zprime.Z(), vecmath::Matrix3f::one, EPS);
}

BTEST(Matrix3Float, multMV_identity)
{
    vecmath::Matrix3f m;

    auto xprime = xunit * m;
    ASSERT_FPEQ(xprime.X(), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(xprime.Y(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(xprime.Z(), vecmath::Matrix3f::zero, EPS);

    auto yprime = yunit * m;
    ASSERT_FPEQ(yprime.X(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(yprime.Y(), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(yprime.Z(), vecmath::Matrix3f::zero, EPS);

    auto zprime = zunit * m;
    ASSERT_FPEQ(zprime.X(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(zprime.Y(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(zprime.Z(), vecmath::Matrix3f::one, EPS);
}

BTEST(Matrix3Float, multMM_identity)
{
    vecmath::Matrix3f a;
    vecmath::Matrix3f b;

    vecmath::Matrix3f r = a*b;

    ASSERT_FPEQ(r.get(0,0), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(r.get(1,1), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(r.get(2,2), vecmath::Matrix3f::one, EPS);
    ASSERT_FPEQ(r.get(3,3), vecmath::Matrix3f::one, EPS);

    ASSERT_FPEQ(r.get(0,1), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.get(0,2), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.get(0,3), vecmath::Matrix3f::zero, EPS);

    ASSERT_FPEQ(r.get(1,0), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.get(1,2), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.get(1,3), vecmath::Matrix3f::zero, EPS);

    ASSERT_FPEQ(r.get(2,0), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.get(2,1), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.get(2,3), vecmath::Matrix3f::zero, EPS);

    ASSERT_FPEQ(r.get(3,0), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.get(3,1), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.get(3,2), vecmath::Matrix3f::zero, EPS);
}

BTEST(Matrix3Float, CT_rotateZX)
{
    /*
     * This test creates a coordinate transformation consisting
     * of a 45° rotation about Z, then a 90° rotation about X.
     *
     * It confirms the original X vector is transformed to the
     * X-Z plane, pointing in +X,+Z direction (45°).
     *
     * It's equivalent to rotating X vec about Y by -45°.
     */

    // Rotate about Z,X:
    vecmath::Matrix3f RZ = vecmath::Matrix3f::rotateZ(M_PI / 4);
    vecmath::Matrix3f RX = vecmath::Matrix3f::rotateX(M_PI / 2);
    vecmath::Vector3f r = RX * RZ * xunit;

    ASSERT_FPEQ(r.X(), std::sqrt(2.0f) / 2.0f, EPS);
    ASSERT_FPEQ(r.Y(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.Z(), std::sqrt(2.0f) / 2.0f, EPS);

    // Rotate about Y:
    vecmath::Matrix3f RY = vecmath::Matrix3f::rotateY(-M_PI / 4);
    r = RY * xunit;

    ASSERT_FPEQ(r.X(), std::sqrt(2.0f) / 2.0f, EPS); // same assertions
    ASSERT_FPEQ(r.Y(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.Z(), std::sqrt(2.0f) / 2.0f, EPS);
}


BTEST(Matrix3Float, vmAndMv)
{
    /*
     * This test makes a rotation of 90° about Z, then checks
     * the results of v*m and m*v multiplication ordering.
     */
    vecmath::Matrix3f RZ = vecmath::Matrix3f::rotateZ(M_PI / 2);
    vecmath::Vector3f r;

    r = RZ * xunit;
    std::cout << "  RZ * xunit => " << r << std::endl;

    ASSERT_FPEQ(r.X(), vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.Y(), vecmath::Matrix3f::one, EPS); // along +Y
    ASSERT_FPEQ(r.Z(), vecmath::Matrix3f::zero, EPS);

    r = xunit * RZ;
    std::cout << "  xunit * RZ => " << r << std::endl;

    ASSERT_FPEQ(r.X(),  vecmath::Matrix3f::zero, EPS);
    ASSERT_FPEQ(r.Y(), -vecmath::Matrix3f::one, EPS); // along -Y
    ASSERT_FPEQ(r.Z(),  vecmath::Matrix3f::zero, EPS);
}
