//
//  Vector3D.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/27/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include "Vector3D.h"

Vector3D::Vector3D(const double x, const double y, const double z)
: x(x), y(y), z(z)
{}

Vector3D::Vector3D(const Vector3D& other)
: x(other.x), y(other.y), z(other.z)
{}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    Vector3D result {0, 0, 0};
    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;
    return result;
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    Vector3D result {0, 0, 0};
    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;
    return result;
}


Vector3D Vector3D::operator*(const double scalar) const
{
    Vector3D result {0, 0, 0};
    result.x = x * scalar;
    result.y = y * scalar;
    result.z = z * scalar;
    return result;
}

Vector3D Vector3D::operator/(const double scalar) const
{
    assert(scalar != 0);
    Vector3D result {0, 0, 0};
    result.x = x * scalar;
    result.y = y * scalar;
    result.z = z * scalar;
    return result;
}

double Vector3D::dot(const Vector3D& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D& other) const
{
    Vector3D result {0, 0, 0};
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
    return result;
}

double Vector3D::norm() const
{
    return sqrt(x*x + y*y + z*z);
}