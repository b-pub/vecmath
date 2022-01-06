/*
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
#ifndef VM_VECOPS_H
#define VM_VECOPS_H

namespace vecmath {

/**
 * Calculate the dot product of two Vector3<>.
 *
 * This function does not normalize \c a or \c b.
 *
 * @return the <fptype> dot result
 */
template <typename fptype>
fptype dot(Vector3<fptype> const &a, Vector3<fptype> const &b)
{
    return (a.X()*b.X() + a.Y()*b.Y() + a.Z()*b.Z());
}

/**
 * Calculate the cross product of two Vector3<>.
 *
 * This function does not normalize \c a or \c b.
 *
 * @return the Vector3<fptype> cross result
 */
template <typename fptype>
Vector3<fptype> cross(Vector3<fptype> const &a, Vector3<fptype> const &b)
{
    return {a.Y()*b.Z() - a.Z()*b.Y(),
            a.Z()*b.X() - a.X()*b.Z(),
            a.X()*b.Y() - a.Y()*b.X()};
}

/*
 * Arithmetic functions. Nothing too fancy here,
 * but basic operations on Vector3s and Point3s.
 */
/**
 * Vector addition
 *
 * Calculates the sum of two vectors, \c a + \c b.
 *
 * @return Vector3<> sum of a and b
 */
template <typename fptype>
Vector3<fptype> operator+(Vector3<fptype> const &a, Vector3<fptype> const &b)
{
    return {a.X()+b.X(), a.Y()+b.Y(), a.Z()+b.Z()};
}

/**
 * Point offset (point + vector)
 *
 * Calculates the new location (pt + dir), given old location \c pt and
 * direction (offset) \c dir.
 *
 * @return Point3<> the new point(pt + dir)
 */
template <typename fptype>
Point3<fptype>  operator+(Point3<fptype> const &pt, Vector3<fptype> const &dir)
{
    return {pt.X()+dir.X(), pt.Y()+dir.Y(), pt.Z()+dir.Z()};
}

/**
 * Point offset (vector + point)
 *
 * Calculates the new location (pt + dir), given old location \c pt and
 * direction (offset) \c dir.
 *
 * @return Point3<> the new point(pt + dir)
 */
template <typename fptype>
Point3<fptype>  operator+(Vector3<fptype> const &dir, Point3<fptype> const &pt)
{
    return {pt.X()+dir.X(), pt.Y()+dir.Y(), pt.Z()+dir.Z()};
}

/**
 * Vector difference
 *
 * Calculates the difference of two vectors, \c a - \c b.
 *
 * @return Vector3<> result of a - b
 */
template <typename fptype>
Vector3<fptype> operator-(Vector3<fptype> const &a, Vector3<fptype> const &b)
{
    return {a.X()-b.X(), a.Y()-b.Y(), a.Z()-b.Z()};
}

/**
 * Point difference
 *
 * Calculates the difference of two points, \c a - \c b.
 *
 * @return Vector3<> result of a - b
 */
template <typename fptype>
Vector3<fptype> operator-(Point3<fptype> const &a, Point3<fptype> const &b)
{
    return {a.X()-b.X(), a.Y()-b.Y(), a.Z()-b.Z()};
}

} // ::vecmath

#endif // VM_VECOPS_H
