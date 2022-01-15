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
 * Print Vector3<> types in a canonical way.
 *
 * Print vectors with format "[x, y, z]", where precision of x,y,z
 * is:
 *   * 5 digits for <float>
 *   * 8 digits for <double>
 *
 * @return reference to input std::ostream.
 */
template <typename fptype>
std::ostream& operator<<(std::ostream &os, vecmath::Vector3<fptype> const& v)
{
    int const prec = (sizeof(fptype) == 4) ? 5 : 8;
    os << std::fixed << std::setprecision(prec)
       << '[' << v.X() << ", " << v.Y() << ", " << v.Z() << ", " << v.W() << "]"
       << std::defaultfloat;
    return os;
}

inline
std::ostream& operator<<(std::ostream &os, vecmath::Matrix3f const& m)
{
    os << std::fixed << std::setprecision(5) << "\n"
       << "[[" << m.get(0,0) << ", " << m.get(0,1) << ", " << m.get(0,2) << ", " << m.get(0,3) << "],\n"
       << " [" << m.get(1,0) << ", " << m.get(1,1) << ", " << m.get(1,2) << ", " << m.get(1,3) << "],\n"
       << " [" << m.get(2,0) << ", " << m.get(2,1) << ", " << m.get(2,2) << ", " << m.get(2,3) << "],\n"
       << " [" << m.get(3,0) << ", " << m.get(3,1) << ", " << m.get(3,2) << ", " << m.get(3,3) << "]]\n"
       << std::defaultfloat;
    return os;
}

#endif // VM_VECPRINT_H
