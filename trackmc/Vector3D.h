//
//  Vector3D.h
//  trackmc
//
//  Created by Joshua Bradt on 4/27/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#ifndef __trackmc__Vector3D__
#define __trackmc__Vector3D__

#include <iostream>
#include <cmath>
#include <assert.h>

class Vector3D
{
public:
    Vector3D(const double x, const double y, const double z);
    Vector3D(const Vector3D& other);
    
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    
    Vector3D operator*(const double scalar) const;
    Vector3D operator/(const double scalar) const;
    friend Vector3D operator*(const double scalar, const Vector3D& vec);
    
    double dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;

    const bool operator==(const Vector3D& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec);
    
    double norm() const;
    
    double x {0};
    double y {0};
    double z {0};
};

#endif /* defined(__trackmc__Vector3D__) */
