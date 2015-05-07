//
// Created by Joshua Bradt on 5/6/15.
//

#include "EventGenerator.h"

Vector3D EventGenerator::make_drift_velocity_vector(const double vd, const double emag, const double bmag,
                                                    const double tilt)
{
    double ot = bmag / emag * vd * 1e+4; // omega * tau in formula. The numerical factor converts cm/us -> m/s

    double front = vd / (1 + ot*ot);

    double xcomp = -front * ot * sin(tilt);
    double ycomp = front * ot*ot * cos(tilt) * sin(tilt);
    double zcomp = front * (1 + ot*ot * cos(tilt)*cos(tilt));

    return Vector3D {xcomp, ycomp, zcomp};
}

Vector3D EventGenerator::calibrate(const Vector3D& data, const Vector3D& vd, const double clock)
{
    Vector3D cal = data;
    cal.z = 0;
    cal += -1 * vd * data.z / clock * 10;
    return cal;
}

Vector3D EventGenerator::uncalibrate(const Vector3D& data, const Vector3D& vd, const double clock)
{
    double tbval = data.z * clock / (10 * -vd.z);  // 1 cm/(us.MHz) = 1 cm = 10 mm
    Vector3D uncal = data;
    uncal -= vd * -tbval / clock * 10;
    uncal.z = tbval;

    return uncal;
}