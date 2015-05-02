//
// Created by Joshua Bradt on 5/2/15.
//

#ifndef TRACKMC_TRACKSIMULATOR_H
#define TRACKMC_TRACKSIMULATOR_H


#include "Vector3D.h"

class TrackSimulator
{
public:


    static Vector3D lorentz_force(const Vector3D& vel, const Vector3D& ef, const Vector3D& bf, const double chg);

};


#endif //TRACKMC_TRACKSIMULATOR_H
