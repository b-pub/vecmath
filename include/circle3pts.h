/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
#ifndef CIRCLE3PTS_H
#define CIRCLE3PTS_H

#include "vecmath.h"

namespace vecmath {

/**
 * Calculate a circle from 3 points.
 *
 * Given three Vector3<> locations in the X,Y plane (Z=0, but ignored),
 * calculate the location of the circle's center.
 *
 * The three points should not be colinear. If so, this function
 * throws a vecmath::degenerate_error exception.
 *
 * @returns Vector3<> the center of the circle
 */
template <typename fptype>
Vector3<fptype> circle3pts(Vector3<fptype> a, Vector3<fptype> b, Vector3<fptype> c)
{
    using Vec3 = Vector3<fptype>;

    // Determine if points a,b,c are colinear.
    const Vec3 dirab = b-a;
    const Vec3 dirbc = c-b;
    Vec3 tmp = cross(dirab, dirbc);
    if (fpequal(tmp.length(), fptype(0.0)))
        throw degenerate_error("circle3pts: points a,b,c are colinear");

    // Not colinear, so calculate midpoints, perp bisectors, line intersection:
    Vec3 midab = midpoint(a, b);
    Vec3 midbc = midpoint(b, c);

    // perp bisector directions:
    Vec3 midabdir {dirab.Y(), -dirab.X(), 0.0};
    Vec3 midbcdir {dirbc.Y(), -dirbc.X(), 0.0};

    // Create line eqns for (midab, midabdi) and (midbc, midbcdir).
    // The parametric form is natural: x = x0 + t*xdir, y = y0 + t*ydir
    // but is harder to work with. Convert to implicit form
    // -ydir*x + xdir*y + (x0*ydir - y0*xdir) = 0
    // We'll store these 3 coeffs in a Vector; W() is unused.
    midabdir.normalize();
    midbcdir.normalize();

    Vec3 L1 {-midabdir.Y(), midabdir.X(),
                (midab.X()*midabdir.Y() - midab.Y()*midabdir.X())};
    Vec3 L2 {-midbcdir.Y(), midbcdir.X(),
                (midbc.X()*midbcdir.Y() - midbc.Y()*midbcdir.X())};

    // Calc where the two lines intersect. Return this point.
    // See "A Programmer's Geometry", by Adrian Bowyer & John Woodwark, 1983.
    fptype d = L1.X()*L2.Y() - L2.X()*L1.Y();
    fptype x = (L1.Y()*L2.Z() - L2.Y()*L1.Z()) / d;
    fptype y = (L2.X()*L1.Z() - L1.X()*L2.Z()) / d;

    return {x, y, 0.0};
}

} // ::vecmath

#endif // CIRCLE3PTS_H
