//
// Created by Joshua Bradt on 5/3/15.
//

#include "catch.hpp"
#include "InputFile.h"
#include <vector>

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
                REQUIRE(inputs.get_efield() == ef_exp);
                REQUIRE(inputs.get_bfield() == bf_exp);

                std::string path_exp {"gasdata/helium.dat"};
                REQUIRE(inputs.get_gas_path() == path_exp);
                REQUIRE(inputs.get_gas_pressure() == 760);

                auto trackparams = inputs.get_track_parameters();
                REQUIRE(trackparams.size() == 1);

                std::vector<double> zero_vec {0, 0, 0};
                REQUIRE(trackparams[0].proj_mass == 4);
                REQUIRE(trackparams[0].proj_charge == 2);
                REQUIRE(trackparams[0].proj_energy == 2);
                REQUIRE(trackparams[0].proj_position == zero_vec);
                REQUIRE(trackparams[0].proj_azimuth == 0);
                REQUIRE(trackparams[0].proj_polar == 0.78);
                REQUIRE(trackparams[0].is_interaction == true);
                REQUIRE(trackparams[0].target_charge == 2);
                REQUIRE(trackparams[0].target_mass == 4);
                REQUIRE(trackparams[0].vertex_energy == 1);
            }
        }
    }
}