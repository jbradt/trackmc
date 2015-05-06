//
// Created by Joshua Bradt on 5/6/15.
//

#include "catch.hpp"
#include "EventGenerator.h"
#include "Constants.h"

SCENARIO("Drift velocity vector must be calculated")
{
    GIVEN("Vd mag, fields, and tilt")
    {
        double vd {5};
        double bmag {10};
        double emag {2};
        double tilt {10*Conversions::degrees};

        double ot = bmag / emag * vd * 1e+4;

        WHEN("tilt is zero")
        {
            tilt = 0;
            THEN("vd is along z")
            {
                Vector3D vdv = EventGenerator::make_drift_velocity_vector(vd, emag, bmag, tilt);
                REQUIRE(vdv.x == 0);
                REQUIRE(vdv.y == 0);
            }
        }

        WHEN("the B field is zero")
        {
            bmag = 0;
            THEN("vd is along z")
            {
                Vector3D vdv = EventGenerator::make_drift_velocity_vector(vd, emag, bmag, tilt);
                REQUIRE(vdv.x == 0);
                REQUIRE(vdv.y == 0);
            }
        }

        WHEN("the vd magnitude is 1.0")
        {
            vd = 1.0;
            THEN("the vd vector is a unit vector")
            {
                Vector3D vdv = EventGenerator::make_drift_velocity_vector(vd, emag, bmag, tilt);
                REQUIRE(vdv.norm() == Approx(1.0).epsilon(1e-2));
            }
        }

        WHEN("E is perpendicular to B")
        {
            tilt = Constants::pi / 2;

            THEN("vd has the correct components")
            {
                Vector3D vdv = EventGenerator::make_drift_velocity_vector(vd, emag, bmag, tilt);
                double xcomp = -vd / (1 + ot*ot) * ot;
                double ycomp = 0.0;
                double zcomp = vd / (1 + ot*ot);
                REQUIRE(vdv.x == Approx(xcomp));
                REQUIRE(vdv.y == Approx(ycomp));
                REQUIRE(vdv.z == Approx(zcomp));
            }
        }

        WHEN("E, B, and tilt have typical values")
        {
            THEN("vd has the correct magnitude")
            {
                Vector3D vdv = EventGenerator::make_drift_velocity_vector(vd, emag, bmag, tilt);
                REQUIRE(vdv.norm() == Approx(vd).epsilon(1e-1));
            }
        }
    }
}