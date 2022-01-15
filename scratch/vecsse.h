/*
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
#ifndef VECSSE_H
#define VECSSE_H

#include <pmmintrin.h>

namespace vecmath {

class Matrix3fmm;

/**
 * A 3x1 float Vector that uses SSE instructions.
 */
class Vector3fmm {
  protected:
    __m128 m_v;                             // a [4 x float] vector

  public:
    Vector3fmm()
        : m_v {0, 0, 0, 1}
    { }
    Vector3fmm(float x, float y, float z)
        : m_v {x, y, z, 1}
    { }

    Vector3fmm(Vector3fmm const &o)
    {
        m_v = o.m_v;
    }

    Vector3fmm& operator=(Vector3fmm const &o)
    {
        if (this != &o)
            std::memcpy(&m_v, &o.m_v, sizeof(m_v));
        return *this;
    }

  public:
    inline float X() const noexcept { return m_v[0]; }
    inline float Y() const noexcept { return m_v[1]; }
    inline float Z() const noexcept { return m_v[2]; }
    inline float W() const noexcept { return m_v[3]; }

    friend Vector3fmm operator*(Vector3fmm const& v,
                                Matrix3fmm const& m);
    friend Vector3fmm operator*(Matrix3fmm const& m,
                                Vector3fmm const& v);
};

/**
 * A 3x3 float Matrix that uses SSE instructions.
 */
class Matrix3fmm
{
  public:
    typedef float fptype;

  protected:
    __m128 m_m[4];                          // [4] of [4 x float] types

  public:
    constexpr static fptype zero = 0.0;
    constexpr static fptype one  = 1.0;

    Matrix3fmm()
        : m_m {{one,  zero, zero, zero},    // identity is default
               {zero, one,  zero, zero},
               {zero, zero, one,  zero},
               {zero, zero, zero, one}}
    { }

    Matrix3fmm(Matrix3fmm const &o)
    {
        std::memcpy(m_m, o.m_m, sizeof(m_m));
    }

    Matrix3fmm& operator=(Matrix3fmm const &o)
    {
        if (this != &o)
        {
            std::memcpy(m_m, o.m_m, sizeof(m_m));
        }
        return *this;
    }

    float get(uint32_t r, uint32_t c) const
    {
        if (r > 3 || c > 3)
        {
            throw index_error("Matrix3::get()");
        }
        return m_m[r][c];
    }

    void transpose()
    {
        _MM_TRANSPOSE4_PS(m_m[0], m_m[1], m_m[2], m_m[3]);
    }

    // static factory methods:

    static Matrix3fmm translation(float dx, float dy, float dz)
    {
        Matrix3fmm r;
        r.m_m[0][3] = dx;                   // | 1 0 0 x |
        r.m_m[1][3] = dy;                   // | 0 1 0 y |
        r.m_m[2][3] = dz;                   // | 0 0 1 z |
        return r;
    }

    static Matrix3fmm scale(float sx, float sy, float sz)
    {
        Matrix3fmm r;
        r.m_m[0][0] = sx;                   // | x 0 0 0 |
        r.m_m[1][1] = sy;                   // | 0 y 0 0 |
        r.m_m[2][2] = sz;                   // | 0 0 z 0 |
        return r;
    }

    static Matrix3fmm rotateX(float theta)
    {
        float ct = std::cos(theta);
        float st = std::sin(theta);

        Matrix3fmm r;
        r.m_m[1][1] = r.m_m[2][2] = ct;
        r.m_m[1][2] = -st;
        r.m_m[2][1] = st;
        return r;
    }

    static Matrix3fmm rotateY(float theta)
    {
        float ct = std::cos(theta);
        float st = std::sin(theta);

        Matrix3fmm r;
        r.m_m[0][0] = r.m_m[2][2] = ct;
        r.m_m[0][2] = st;
        r.m_m[2][0] = -st;
        return r;
    }

    static Matrix3fmm rotateZ(float theta)
    {
        float ct = std::cos(theta);
        float st = std::sin(theta);

        Matrix3fmm r;
        r.m_m[0][0] = r.m_m[1][1] = ct;
        r.m_m[0][1] = -st;
        r.m_m[1][0] = st;
        return r;
    }

    // Declare friend functions for data access:
    friend Matrix3fmm operator*(Matrix3fmm const& a,
                                Matrix3fmm const& b);
    friend Vector3fmm operator*(Matrix3fmm const& m,
                                Vector3fmm const& v);
    friend Vector3fmm operator*(Vector3fmm const& v,
                                Matrix3fmm const& m);
};

} // ::vecmath

#endif // VECSSE_H
