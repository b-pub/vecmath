/*
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

} // ::vecmath

#include "vecops.h"
#include "vecfuncs.h"

#include "vecprint.h"

#endif // VECMATH_H
