/*
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
#ifndef VM_MATOPS_H
#define VM_MATOPS_H

namespace vecmath {

/**
 * Matrix-Matrix multiplication
 */
template <typename fptype>
Matrix3<fptype> operator*(Matrix3<fptype> const& mata,
                          Matrix3<fptype> const& matb)
{
    Matrix3<fptype> result;
    fptype const (&a)[4][4] = mata.m_m;
    fptype const (&b)[4][4] = matb.m_m;

    for (int i=0; i<4; i++)
    {
        fptype (&r)[4] = result.m_m[i];

        r[0] = (a[i][0]*b[0][0] + a[i][1]*b[1][0] +
                a[i][2]*b[2][0] + a[i][3]*b[3][0]);

        r[1] = (a[i][0]*b[0][1] + a[i][1]*b[1][1] +
                a[i][2]*b[2][1] + a[i][3]*b[3][1]);

        r[2] = (a[i][0]*b[0][2] + a[i][1]*b[1][2] +
                a[i][2]*b[2][2] + a[i][3]*b[3][2]);

        r[3] = (a[i][0]*b[0][3] + a[i][1]*b[1][3] +
                a[i][2]*b[2][3] + a[i][3]*b[3][3]);
    }
    return result;
}

/**
 * Row vector-Matrix multiplication
 *
 */
template <typename fptype>
Vector3<fptype> operator*(Vector3<fptype> const& vec,
                          Matrix3<fptype> const& mat)
{
    Vector3<fptype> result;
    fptype (&r)[4] = result.m_v;
    fptype const (&v)[4] = vec.m_v;
    fptype const (&m)[4][4] = mat.m_m;

    // vm_mult
    r[0] = (v[0]*m[0][0] + v[1]*m[1][0] +
            v[2]*m[2][0] + v[3]*m[3][0]);

    r[1] = (v[0]*m[0][1] + v[1]*m[1][1] +
            v[2]*m[2][1] + v[3]*m[3][1]);

    r[2] = (v[0]*m[0][2] + v[1]*m[1][2] +
            v[2]*m[2][2] + v[3]*m[3][2]);

    r[3] = (v[0]*m[0][3] + v[1]*m[1][3] +
            v[2]*m[2][3] + v[3]*m[3][3]);

    return result;
}

/**
 * Matrix-column Vector multiplication
 *
 */
template <typename fptype>
Vector3<fptype> operator*(Matrix3<fptype> const& mat,
                          Vector3<fptype> const& vec)
{
    Vector3<fptype> result;
    fptype (&r)[4] = result.m_v;
    fptype const (&v)[4] = vec.m_v;
    fptype const (&m)[4][4] = mat.m_m;

    // mv_mult
    r[0] = (v[0]*m[0][0] + v[1]*m[0][1] +
            v[2]*m[0][2] + v[3]*m[0][3]);

    r[1] = (v[0]*m[1][0] + v[1]*m[1][1] +
            v[2]*m[1][2] + v[3]*m[1][3]);

    r[2] = (v[0]*m[2][0] + v[1]*m[2][1] +
            v[2]*m[2][2] + v[3]*m[2][3]);

    r[3] = (v[0]*m[3][0] + v[1]*m[3][1] +
            v[2]*m[3][2] + v[3]*m[3][3]);

    return result;
}

} // ::vecmath

#endif // VM_MATOPS_H
