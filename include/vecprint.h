/*
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/*
 * Printing utility function
 */
#ifndef VM_VECPRINT_H
#define VM_VECPRINT_H

// NOT in ::vecmath namespace

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

#endif // VM_VECPRINT_H
