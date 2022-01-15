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
 * A direction in 3D space.
 */
template <typename _fptype>
class Vector3
{
  private:
    _fptype m_v[4];

    static constexpr _fptype EPS = 1.0e-6;

  public:
    typedef _fptype fptype;

    Vector3()
        : m_v {0, 0, 0, 1}
    { }

    Vector3(_fptype x, _fptype y, _fptype z = 0)
        : m_v {x, y, z, 1}
    { }

    Vector3(Vector3 const &o)
    {
        std::memcpy(m_v, o.m_v, sizeof(m_v));
    }

    Vector3& operator=(Vector3 const &o)
    {
        if (this != &o)
            std::memcpy(m_v, o.m_v, sizeof(m_v));
        return *this;
    }

    /**
     * Calculate length of vector.
     * Returns the raw length of the vector.
     */
    _fptype length() const
    {
        _fptype result = (X() * X() +
                          Y() * Y() +
                          Z() * Z());

        if ( !fpequal(result, _fptype(1.0)) )
        {
            result = std::sqrt(result);
        }

        if (result <= EPS)            // snap to zero if close
        {
            result = 0;
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

        if (len == 0)              // length() snaps to zero
        {
            m_v[0] = m_v[1] = m_v[2] = 0;
            m_v[3] = 1.0;
        }
        else if ( !fpequal(len, _fptype(1.0)) )
        {
            m_v[0] /= len;
            m_v[1] /= len;
            m_v[2] /= len;
            m_v[3]  = 1.0;
        }

        return *this;
    }

    /* Component getters */
    inline fptype X() const noexcept { return m_v[0]; }
    inline fptype Y() const noexcept { return m_v[1]; }
    inline fptype Z() const noexcept { return m_v[2]; }
    inline fptype W() const noexcept { return m_v[3]; }

    template <typename FP>
    friend Vector3<FP> operator*(Vector3<FP> const& v,
                                 Matrix3<FP> const& m);
    template <typename FP>
    friend Vector3<FP> operator*(Matrix3<FP> const& m,
                                 Vector3<FP> const& v);
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

    fptype get(uint32_t r, uint32_t c) const
    {
        if (r > 3 || c > 3)
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
