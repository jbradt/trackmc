//
// Created by Joshua Bradt on 5/4/15.
//

#include "catch.hpp"
#include "GasMixture.h"

SCENARIO("GasMixture is constructed")
{
    GIVEN("two gas files and proportions")
    {
        std::vector<std::string> gas_files {"test_data/helium.dat", "test_data/co2.dat"};
        std::vector<double> props {0.9, 0.1};
        double pressure {200};

        WHEN("the files match and the props add to 1")
        {
            THEN("the result is the weighted mean of the two gases")
            {
                GasMixture gmix {pressure, gas_files, props};
                Gas gas0 {pressure * props[0], gas_files[0]};
                Gas gas1 {pressure * props[1], gas_files[1]};

                REQUIRE(gmix.get_pressure() == gas0.get_pressure() + gas1.get_pressure());
                REQUIRE(gmix.get_molar_mass() == gas0.get_molar_mass() * props[0] + gas1.get_molar_mass() * props[1]);

                REQUIRE(gmix.get_num_pts() == gas0.get_num_pts());
                REQUIRE(gmix.get_num_pts() == gas1.get_num_pts());
                REQUIRE(gmix.get_max_energy() == gas0.get_max_energy());
                REQUIRE(gmix.get_max_energy() == gas1.get_max_energy());

                double enstep = gmix.get_max_energy() / gmix.get_num_pts();
                for (double en = 0; en < gmix.get_max_energy(); en += enstep) {
                    CAPTURE(en);
                    REQUIRE(gmix.energy_loss(en) == Approx(gas0.energy_loss(en) + gas1.energy_loss(en)).epsilon(1e-6));
                }
            }
        }
    }
}