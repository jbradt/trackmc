//
// Created by Joshua Bradt on 5/2/15.
//

#include "TrackSimulator.h"

Vector3D TrackSimulator::lorentz_force(const Vector3D& vel, const Vector3D& ef, const Vector3D& bf, const double chg)
{
    return chg * (ef + vel.cross(bf));
}