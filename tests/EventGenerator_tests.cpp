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

SCENARIO("Data needs to be calibrated")
{
    GIVEN("a data set and a vd vector")
    {
        std::vector<Vector3D> data;
        for (int i = 0; i < 512; i++) {
            data.push_back(Vector3D(0, 0, i));
        }
        double clock {10};
        Vector3D vd {0, 0.5, 1};

        WHEN("the data is calibrated")
        {
            THEN("the result is right")
            {
                for (auto& item : data) {
                    Vector3D cal_item = EventGenerator::calibrate(item, vd, clock);
                    CAPTURE(item);
                    CAPTURE(cal_item);
                    REQUIRE(cal_item.x == (item.x + -vd.x * item.z / clock * 10));
                    REQUIRE(cal_item.y == (item.y + -vd.y * item.z / clock * 10));
                    REQUIRE(cal_item.z == (-vd.z * item.z / clock * 10));
                }
            }
        }

        WHEN("the data set is calibrated and then uncalibrated")
        {
            THEN("the result is identical to the input")
            {
                for (auto& item : data) {
                    Vector3D cal_item = EventGenerator::calibrate(item, vd, clock);
                    Vector3D uncal_item = EventGenerator::uncalibrate(cal_item, vd, clock);
                    CAPTURE(item);
                    CAPTURE(cal_item);
                    REQUIRE(uncal_item == item);
                }
            }
        }
    }
}