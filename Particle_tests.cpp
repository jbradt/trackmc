//
//  Particle_tests.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include "catch.hpp"
#include "Particle.h"
#include "Vector3D.h"
#include "Constants.h"
#include <iostream>

SCENARIO("Particle class is working", "[Particle]") {
    
    GIVEN("A particle with some parameters") {
        unsigned int mass_num {4};
        unsigned int charge_num {2};
        double energy_per_particle {2.2};
        double energy = energy_per_particle * mass_num;
        Vector3D pos {0, 0, 1.0};
        double azi {45 * Conversions::degrees};
        double pol {3 * Constants::pi / 4};
        
        Particle pt {mass_num, charge_num, energy_per_particle, pos, azi, pol};
        
        REQUIRE(pt.mass_num == mass_num);
        REQUIRE(pt.charge_num == charge_num);
        REQUIRE(pt.energy == energy);
        REQUIRE(pt.polar == pol);
        REQUIRE(pt.azimuth == azi);
        REQUIRE(pt.position == pos);
        
        double mass = mass_num * Constants::p_mc2;
        double gamma = energy / mass + 1;
        double beta = sqrt(1 - 1 / (gamma*gamma));
        
        REQUIRE(pt.get_mass() == mass);
        REQUIRE(pt.get_gamma() == gamma);
        REQUIRE((pt.get_beta() - beta) < 1e-6);
        
        WHEN("the particle is constructed") {
            THEN("the momentum will be correct") {
                // Check this by looking at the components
                auto mom = pt.get_momentum();
                double total_en = energy + mass;
                double exp_mag = sqrt(total_en*total_en - mass*mass);
                double mom_pol = atan2(sqrt(mom.x*mom.x + mom.y*mom.y), mom.z);
                double mom_azi = atan2(mom.y, mom.x);
   
                REQUIRE((mom.norm() - exp_mag) < 1e-6);
                REQUIRE(mom_pol == pol);
                REQUIRE(mom_azi == azi);
            }
        }
        WHEN("energy is set to zero") {
            pt.energy = 0;
            
            Vector3D zero_vec {0, 0, 0};
            
            THEN("energy becomes zero") {
                REQUIRE(pt.energy == 0);
            }
            AND_THEN("momentum becomes zero") {
                auto mom = pt.get_momentum();
                REQUIRE(mom == zero_vec);
            }
            AND_THEN("velocity becomes zero") {
                auto vel = pt.get_velocity();
                REQUIRE(vel == zero_vec);
            }
            AND_THEN("beta becomes zero") {
                REQUIRE(pt.get_beta() == 0);
            }
            AND_THEN("gamma becomes one") {
                REQUIRE(pt.get_gamma() == 1);
            }
        }
        WHEN("momentum is halved") {
            auto old_mom = pt.get_momentum();
            auto new_mom = old_mom / 2;
            auto new_mom_mag = new_mom.norm();
            pt.set_momentum(new_mom);
            
            THEN("new momentum is half the old value") {
                REQUIRE(pt.get_momentum() == new_mom);
            }
            AND_THEN("energy changes") {
                double new_en = sqrt(new_mom_mag*new_mom_mag + mass*mass) - mass;
                REQUIRE(pt.energy == new_en);
            }
            AND_THEN("angles remain the same") {
                REQUIRE(pt.polar == pol);
                REQUIRE(pt.azimuth == azi);
            }
        }
    }
}