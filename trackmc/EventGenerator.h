//
// Created by Joshua Bradt on 5/6/15.
//

#ifndef TRACKMC_EVENTGENERATOR_H
#define TRACKMC_EVENTGENERATOR_H

#include "Vector3D.h"
#include <cmath>

class EventGenerator
{
public:
    EventGenerator();

    static Vector3D make_drift_velocity_vector(const double vd, const double emag, const double bmag, const double tilt);
    static Vector3D calibrate(const Vector3D& data, const Vector3D& vd, const double clock);
    static Vector3D uncalibrate(const Vector3D& data, const Vector3D& vd, const double clock);
};


#endif //TRACKMC_EVENTGENERATOR_H
