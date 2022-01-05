/**
 * The "vecmath" 3D vector library
 *
 * Copyright 1996-2022 Brent Burton
 * Licensed under the MIT License. See LICENSE for details.
 *
 */
/*
 * Shared definitions for testing.
 */
#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <btest.h>

/**
 * EPS is a "close enough" value for equality checking.
 */
constexpr float EPS {1.0e-6};

static const vecmath::Vector3f xunit(1.0, 0.0, 0.0);
static const vecmath::Vector3f yunit(0.0, 1.0, 0.0);
static const vecmath::Vector3f zunit(0.0, 0.0, 1.0);

#endif // TEST_COMMON_H
