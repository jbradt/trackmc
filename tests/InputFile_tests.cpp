//
// Created by Joshua Bradt on 5/3/15.
//

#include "catch.hpp"
#include "InputFile.h"
#include <vector>
#include <Constants.h>

SCENARIO("An input file needs to be read")
{
    GIVEN("An input file")
    {
        InputFile inputs {};

        WHEN("The configuration is good")
        {
            inputs.parse("test_data/test_track.yaml");

            THEN("all fields are filled")
            {
                std::vector<double> ef_exp {0, 0, 15e3};
                std::vector<double> bf_exp {0, 0, 1};
                double tilt_exp {7 * Conversions::degrees};
                REQUIRE(inputs.get_efield() == ef_exp);
                REQUIRE(inputs.get_bfield() == bf_exp);
                REQUIRE(inputs.get_tilt() == tilt_exp);

                std::string path1 {"gasdata/helium.dat"};
                std::string path2 {"gasdata/co2.dat"};
                auto gas_paths = inputs.get_gas_paths();
                REQUIRE(gas_paths.size() == 2);
                REQUIRE(gas_paths[0] == path1);
                REQUIRE(gas_paths[1] == path2);

                double prop1 {0.9};
                double prop2 {0.1};
                auto gas_props = inputs.get_gas_proportions();
                REQUIRE(gas_props.size() == 2);
                REQUIRE(gas_props[0] == prop1);
                REQUIRE(gas_props[1] == prop2);

                REQUIRE(inputs.get_gas_pressure() == 760);

                auto evts = inputs.get_events();
                REQUIRE(evts.size() == 1);
                REQUIRE(evts[0].particles.size() == 2);

                ParticleParameters pt1 = evts[0].particles[0];
                ParticleParameters pt2 = evts[0].particles[1];

                std::vector<double> pt1pos {0, 0, 0};
                std::vector<double> pt2pos {0, 0, 0.5};

                REQUIRE(pt1.mass == 4);
                REQUIRE(pt1.charge == 2);
                REQUIRE(pt1.energy == 2);
                REQUIRE(pt1.final_energy == 1);
                REQUIRE(pt1.position == pt1pos);
                REQUIRE(pt1.polar == 0.78);
                REQUIRE(pt1.azimuth == 0);

                REQUIRE(pt2.mass == 4);
                REQUIRE(pt2.charge == 2);
                REQUIRE(pt2.energy == 1);
                REQUIRE(pt2.position == pt2pos);
                REQUIRE(pt2.polar == 0.12);
                REQUIRE(pt2.azimuth == 3.0);
                REQUIRE(pt2.final_energy == 0);
            }
        }
    }
}