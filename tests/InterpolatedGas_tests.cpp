//
// Created by Joshua Bradt on 5/1/15.
//

#include "catch.hpp"
#include "Gas.h"
#include <string>

SCENARIO("InterpolatedGas class is working")
{
    GIVEN("An InterpolatedGas object and a file name")
    {
        double press {100.};
        double molar {4.};

        InterpolatedGas gas {press, molar};
        std::string testfilename {"test_data/testgas.dat"};

        REQUIRE(gas.get_pressure() == press);
        REQUIRE(gas.get_molar_mass() == molar);

        WHEN("the density is calculated")
        {
            auto dens = gas.get_density();

            THEN("it is correct")
            {
                double expect = press / 760 * molar / 24040;
                REQUIRE(dens == expect);
            }
        }

        WHEN("the file is read")
        {
            gas.read_file(testfilename);

            THEN("the energy loss function works correctly")
            {
                auto dens = gas.get_density();

                for (int i = 1; i <= 10; i++) {
                    REQUIRE(gas.energy_loss((i-1)*0.001) == i*100*dens);
                }
            }
        }
    }
}