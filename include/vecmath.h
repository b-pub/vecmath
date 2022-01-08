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
 * The degenerate_error exception is thrown when computations
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
 * The index_error exception is thrown when invalid
 * vector or matrix indices are specified. Valid range
 * of an index is [0,3].
 */
class index_error : public std::domain_error
{
  public:
    index_error(char const* msg)
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

/*
 * Forward declarations of Vector3 and Matrix3, and the operator
 * overloads that work with multiple argument types at
 * once. These operators must be declared as friends in each
 * class to access members.
 */
template <typename fptype> class Vector3;
template <typename fptype> class Matrix3;

template <typename fptype>
Vector3<fptype> operator*(Vector3<fptype> const& v,  // V' = V * M
                          Matrix3<fptype> const& m);

template <typename fptype>
Vector3<fptype> operator*(Matrix3<fptype> const& m,  // V' = M * V
                          Vector3<fptype> const& v);

/**
 * This abstract class is the base storage for 3D vector types.
 *
 * It exists to provide uniform storage, initialization, and
 * common getters.
 *
 * Subclasses of Vector3Base are Points and Vectors and
 * while somewhat interchangeable from a computational
 * perspective, they are separated for semantics.
 */
template <typename fptype>
class Vector3Base {
  protected:
    fptype m_v[4];

    constexpr static fptype zero = 0.0;
    constexpr static fptype one  = 1.0;
    constexpr static fptype EPS  = 1.0e-6;

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

    /*
     * The type of the Vector3<> function parameter for these
     * operators is intentional. Clients use the Vector3<> type,
     * but the operator needs access to this base class' members.
     */
    template <typename FP>
    friend Vector3<FP> operator*(Vector3<FP> const& v,
                                 Matrix3<FP> const& m);
    template <typename FP>
    friend Vector3<FP> operator*(Matrix3<FP> const& m,
                                 Vector3<FP> const& v);
};

/**
 * A direction in 3D space.
 */
template <typename _fptype>
class Vector3 : public Vector3Base<_fptype>
{
  protected:
    using Base = Vector3Base<_fptype>;

  public:
    typedef _fptype fptype;

    Vector3() = default;

    Vector3(_fptype x, _fptype y, _fptype z = Base::zero)
        : Vector3Base<_fptype>(x,y,z)
    { }

    /**
     * Calculate length of vector.
     * Returns the raw length of the vector.
     */
    _fptype length() const
    {
        _fptype result = (Base::X() * Base::X() +
                          Base::Y() * Base::Y() +
                          Base::Z() * Base::Z());

        if ( !fpequal(result, Base::one) )
        {
            result = std::sqrt(result);
        }

        if (result <= Base::EPS)            // snap to zero if close
        {
            result = Base::zero;
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

        if (len == Base::zero)              // length() snaps to zero
        {
            Base::m_v[0] = Base::m_v[1] = Base::m_v[2] = Base::zero;
            Base::m_v[3] = Base::one;
        }
        else if ( !fpequal(len, Base::one) )
        {
            Base::m_v[0] /= len;
            Base::m_v[1] /= len;
            Base::m_v[2] /= len;
            Base::m_v[3]  = Base::one;
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
  protected:
    using Base = Vector3Base<_fptype>;

  public:
    typedef _fptype fptype;

    Point3() = default;

    Point3(_fptype x, _fptype y, _fptype z = Base::zero)
        : Vector3Base<_fptype>(x,y,z)
    { }
};

/**
 * A 3D transformation matrix
 */
template <typename _fptype>
class Matrix3
{
  public:
    typedef _fptype fptype;

  protected:
    fptype m_m[4][4];

  public:
    constexpr static fptype zero = 0.0;
    constexpr static fptype one  = 1.0;

    Matrix3()
        : m_m {{one,  zero, zero, zero},    // identity is default
               {zero, one,  zero, zero},
               {zero, zero, one,  zero},
               {zero, zero, zero, one}}
    { }

    Matrix3(Matrix3 const &o)
    {
        std::memcpy(m_m, o.m_m, sizeof(m_m));
    }

    Matrix3& operator=(Matrix3 const &o)
    {
        if (this != &o)
        {
            std::memcpy(m_m, o.m_m, sizeof(m_m));
        }
        return *this;
    }

    fptype get(int r, int c) const
    {
        if (r < 0 || r > 3 || c < 0 || c > 3)
        {
            throw index_error("Matrix3::get()");
        }
        return m_m[r][c];
    }

    // static factory methods:

    static Matrix3 translation(fptype dx, fptype dy, fptype dz)
    {
        Matrix3 r;
        r.m_m[0][3] = dx;                   // | 1 0 0 x |
        r.m_m[1][3] = dy;                   // | 0 1 0 y |
        r.m_m[2][3] = dz;                   // | 0 0 1 z |
        return r;
    }

    static Matrix3 scale(fptype sx, fptype sy, fptype sz)
    {
        Matrix3 r;
        r.m_m[0][0] = sx;                   // | x 0 0 0 |
        r.m_m[1][1] = sy;                   // | 0 y 0 0 |
        r.m_m[2][2] = sz;                   // | 0 0 z 0 |
        return r;
    }

    static Matrix3 rotateX(fptype theta)
    {
        fptype ct = std::cos(theta);
        fptype st = std::sin(theta);

        Matrix3 r;
        r.m_m[1][1] = r.m_m[2][2] = ct;
        r.m_m[1][2] = -st;
        r.m_m[2][1] = st;
        return r;
    }

    static Matrix3 rotateY(fptype theta)
    {
        fptype ct = std::cos(theta);
        fptype st = std::sin(theta);

        Matrix3 r;
        r.m_m[0][0] = r.m_m[2][2] = ct;
        r.m_m[0][2] = st;
        r.m_m[2][0] = -st;
        return r;
    }

    static Matrix3 rotateZ(fptype theta)
    {
        fptype ct = std::cos(theta);
        fptype st = std::sin(theta);

        Matrix3 r;
        r.m_m[0][0] = r.m_m[1][1] = ct;
        r.m_m[0][1] = -st;
        r.m_m[1][0] = st;
        return r;
    }

    // Declare friend functions for data access:
    template <typename FP>
    friend Matrix3<FP> operator*(Matrix3<FP> const& a,
                                 Matrix3<FP> const& b);
    template <typename FP>
    friend Vector3<FP> operator*(Vector3<FP> const& v,
                                 Matrix3<FP> const& m);
    template <typename FP>
    friend Vector3<FP> operator*(Matrix3<FP> const& m,
                                 Vector3<FP> const& v);
};

/*
 * Type specializations for float and double variants
 */
using Point3f  = Point3<float>;
using Point3d  = Point3<double>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Matrix3f = Matrix3<float>;
using Matrix3d = Matrix3<double>;

} // ::vecmath

#include "vecops.h"
#include "vecfuncs.h"

#include "vecprint.h"

#include "matops.h"

#endif // VECMATH_H
