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

SCENARIO("A single particle can be tracked")
{
    GIVEN("a particle, fields, and gas")
    {
        Vector3D pos {0, 0, 0};
        double azi = Constants::pi / 4;
        double pol = Constants::pi / 4;
        double en = 2;

        Particle pt {4, 2, en, pos, azi, pol};

        InterpolatedGas gas {150., 4.};
        gas.read_file("test_data/helium.dat");

        Vector3D ef {0, 0, 15e3};
        Vector3D bf {0, 0, 1};

        WHEN("the particle is tracked")
        {
            TrackSimulator ts {gas, ef, bf};
            SimulatedTrack res = ts.track_particle(pt);

            THEN("the result is constructed properly")
            {
                auto len = res.position.size();
                REQUIRE(res.momentum.size() == len);
                REQUIRE(res.time.size() == len);
                REQUIRE(res.de.size() == len);
                REQUIRE(res.azimuth.size() == len);
                REQUIRE(res.polar.size() == len);
            }
        }
    }
}

SCENARIO("The next state of a particle is needed")
{
    GIVEN("a particle, fields, and gas")
    {
        Vector3D pos {0, 0, 0};
        double azi = Constants::pi / 4;
        double pol = Constants::pi / 4;
        double en = 2;

        Particle pt {4, 2, en, pos, azi, pol};

        InterpolatedGas gas {150., 4.};
        gas.read_file("test_data/helium.dat");

        Vector3D ef {0, 0, 15e3};
        Vector3D bf {0, 0, 1};

        double tstep = 1e-8;

        TrackSimulator ts {gas, ef, bf};

        WHEN("the energy is zero")
        {
            pt.energy = 0;

            THEN("the particle doesn't move")
            {
                Particle res = ts.find_next_state(pt, tstep);
                REQUIRE(pt.position == res.position);
                REQUIRE(pt.get_momentum() == res.get_momentum());
            }
        }
    }
}