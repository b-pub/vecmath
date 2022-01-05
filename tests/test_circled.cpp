/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/*
 * Test of circle from 3 points function; double version
 */
#include "vecmath.h"
#include "circle3pts.h"

#include "test_common.h"

BTEST(Circle, colinearFailDbl)
{
    vecmath::Point3d a,b,c;                  // defaults are colinear/degenerate.

    try {
        vecmath::Point3d center = vecmath::circle3pts(a,b,c);
        FAIL() << "circle3pts() should have failed for colinear points\n";
    }
    catch (std::exception&) {
        // PASS, intended failure
    }
}

BTEST(Circle, basicDbl)
{
    vecmath::Point3d a {1.0, 1.0, 0.0};
    vecmath::Point3d b {2.0, 0.0, 0.0};
    vecmath::Point3d c {3.0, 1.0, 0.0}; // Center is at (2,1).

    try {
        vecmath::Point3d center = vecmath::circle3pts(a,b,c);

        std::cout << "Solution: " << center << std::endl;

        ASSERT_FPEQ(center.X(), 2.0, EPS);
        ASSERT_FPEQ(center.Y(), 1.0, EPS);
    }
    catch (std::exception& e) {
        FAIL() << e.what() << std::endl;
    }
}
