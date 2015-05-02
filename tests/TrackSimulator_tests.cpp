//
// Created by Joshua Bradt on 5/2/15.
//

#include "catch.hpp"
#include "TrackSimulator.h"
#include "Vector3D.h"

SCENARIO("TrackSimulator's static functions work correctly")
{
    GIVEN("A velocity, E field, B field, and charge")
    {
        Vector3D vel {4, 5, 6};
        Vector3D ef {1, 2, 3};
        Vector3D bf {7, 8, 9};
        double charge {4};

        const Vector3D zerovec {0, 0, 0};

        WHEN("the charge is zero")
        {
            charge = 0;

            THEN("the force is zero")
            {
                auto force = TrackSimulator::lorentz_force(vel, ef, bf, charge);
                REQUIRE(force == zerovec);
            }
        }
        WHEN("the velocity is parallel to the B field")
        {
            vel = {1, 0, 0};
            bf  = {1, 0, 0};

            THEN("the force is q * ef")
            {
                auto force = TrackSimulator::lorentz_force(vel, ef, bf, charge);
                REQUIRE(force == (charge * ef));
            }
        }
        WHEN("the force is found in general")
        {
            auto force = TrackSimulator::lorentz_force(vel, ef, bf, charge);
            const Vector3D expect = charge * (ef + vel.cross(bf));
            THEN("it is correct")
            {
                REQUIRE(force == expect);
            }
        }
    }
}