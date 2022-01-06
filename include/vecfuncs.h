/*
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/*
 * Extra functions
 */
#ifndef VM_VECFUNCS_H
#define VM_VECFUNCS_H

namespace vecmath {

/**
 * Midpoint between two Points.
 *
 * @return Point3<> result of (a+b)/2
 */
template <typename fptype>
Point3<fptype> midpoint(Point3<fptype> const &a, Point3<fptype> const &b)
{
    return {(a.X()+b.X())/2, (a.Y()+b.Y())/2, (a.Z()+b.Z())/2};
}

} // ::vecmath

#endif // VM_VECFUNCS_H
