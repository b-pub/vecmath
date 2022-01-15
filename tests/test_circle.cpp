/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/*
 * Test of circle from 3 points function
 */
#include "vecmath.h"
#include "circle3pts.h"

#include "test_common.h"

BTEST(Circle, colinearFail)
{
    vecmath::Vector3f a,b,c;                  // defaults are colinear/degenerate.

    try {
        (void) vecmath::circle3pts(a,b,c);
        FAIL() << "circle3pts() should have failed for colinear points\n";
    }
    catch (std::exception&) {
        // PASS, intended failure
    }
}

BTEST(Circle, basic)
{
    vecmath::Vector3f a {1.0f, 1.0f, 0.0f};
    vecmath::Vector3f b {2.0f, 0.0f, 0.0f};
    vecmath::Vector3f c {3.0f, 1.0f, 0.0f}; // Center is at (2,1).

    try {
        vecmath::Vector3f center = vecmath::circle3pts(a,b,c);

        std::cout << "Solution: " << center << std::endl;

        ASSERT_FPEQ(center.X(), 2.0f, EPS);
        ASSERT_FPEQ(center.Y(), 1.0f, EPS);
    }
    catch (std::exception& e) {
        FAIL() << e.what() << std::endl;
    }
}
