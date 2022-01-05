/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
#ifndef VECMATH_H
#define VECMATH_H

#include <ostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <cstring>                          // std::memcpy()

namespace vecmath {

/**
 * The degenerate_case exception is thrown when computations
 * detect a calculation with no solution.
 */
class degenerate_error : public std::domain_error
{
  public:
    degenerate_error(char const* msg)
        : std::domain_error(msg)
    { }
};

/**
 * fpequal() determines if two \c fptype values
 * are close enough to be considered equal.
 */
template <typename fptype>
inline bool fpequal(fptype const a, fptype const b, fptype EPS = 1.0e-6)
{
    return (std::abs(a - b) < EPS);
}

/**
 * This abstract class is the base storage for 3D vector types.
 *
 * It exists to provide uniform storage, initialization, and
 * common getters.
 *
 * Subclasses of Vector3Base are Points and Vectors and
 * while somewhat intercahngeable from a computational
 * perspective, they are separated for semantics.
 */
template <typename fptype>
class Vector3Base {
  protected:
    fptype m_v[4];

    Vector3Base()
        : m_v {0, 0, 0, 1}
    { }
    Vector3Base(fptype x, fptype y, fptype z)
        : m_v {x, y, z, 1}
    { }
    virtual ~Vector3Base() { }

    Vector3Base(Vector3Base const &o)
    {
        std::memcpy(m_v, o.m_v, sizeof(m_v));
    }

    Vector3Base& operator=(Vector3Base const &o)
    {
        if (this != &o)
            std::memcpy(m_v, o.m_v, sizeof(m_v));
        return *this;
    }

  public:
    inline fptype X() const noexcept { return m_v[0]; }
    inline fptype Y() const noexcept { return m_v[1]; }
    inline fptype Z() const noexcept { return m_v[2]; }
    inline fptype W() const noexcept { return m_v[3]; }
};

/**
 * A direction in 3D space.
 */
template <typename _fptype>
class Vector3 : public Vector3Base<_fptype>
{
  public:
    typedef _fptype fptype;

    Vector3() = default;

    Vector3(_fptype x, _fptype y, _fptype z = 0.0)
        : Vector3Base<_fptype>(x,y,z)
    { }

    /**
     * Calculate length of vector.
     * Returns the raw length of the vector.
     */
    _fptype length() const
    {
        _fptype result = (Vector3Base<_fptype>::X() * Vector3Base<_fptype>::X() +
                          Vector3Base<_fptype>::Y() * Vector3Base<_fptype>::Y() +
                          Vector3Base<_fptype>::Z() * Vector3Base<_fptype>::Z());

        if ( !fpequal(result, _fptype(1.0)) )
        {
            result = std::sqrt(result);
        }

        return result;
    }

    /**
     * Normalize a vector to unit length.
     * Returns a reference to the vector.
     */
    Vector3& normalize()
    {
        _fptype len = length();

        if ( !fpequal(len, _fptype(1.0)) )
        {
            Vector3Base<_fptype>::m_v[0] /= len;
            Vector3Base<_fptype>::m_v[1] /= len;
            Vector3Base<_fptype>::m_v[2] /= len;
            Vector3Base<_fptype>::m_v[3] = 1.0;
        }

        return *this;
    }
};

/**
 * A location in 3D space.
 */
template <typename _fptype>
class Point3 : public Vector3Base<_fptype>
{
  public:
    typedef _fptype fptype;

    Point3() = default;

    Point3(_fptype x, _fptype y, _fptype z=0.0)
        : Vector3Base<_fptype>(x,y,z)
    { }
};

/*
 * Type specializations for float and double variants
 */
using Point3f  = Point3<float>;
using Point3d  = Point3<double>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

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



/**
 * Print Vector3Base<> types in a canonical way.
 *
 * Print vectors with format "[x, y, z]", where precision of x,y,z
 * is:
 *   * 5 digits for <float>
 *   * 8 digits for <double>
 *
 * @return reference to input std::ostream.
 */
template <typename fptype>
std::ostream& operator<<(std::ostream &os, vecmath::Vector3Base<fptype> const& v)
{
    int const prec = (sizeof(fptype) == 4) ? 5 : 8;
    os << '[' << std::fixed << std::setprecision(prec)
       << v.X() << ", "
       << v.Y() << ", "
       << v.Z() << ", "
       << v.W() << std::defaultfloat
       << "]";
    return os;
}

#endif // VECMATH_H
