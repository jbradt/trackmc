//
//  Particle.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/27/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include "Particle.h"

Particle::Particle(unsigned int mass_num, unsigned int charge_num,
                   double energy_per_particle, Vector3D position,
                   double azimuth, double polar)
: mass_num(mass_num), charge_num(charge_num),
  energy(energy_per_particle * mass_num), position(position),
  azimuth(azimuth), polar(polar)
{}

Vector3D Particle::get_momentum() const
{
    auto mass = get_mass();
    auto total_en = energy + mass;
    auto mom_mag = sqrt(total_en*total_en - mass*mass);
    Vector3D mom {mom_mag * cos(azimuth) * sin(polar),
                  mom_mag * sin(azimuth) * sin(polar),
                  mom_mag * cos(polar)};
    return mom;
}

void Particle::set_momentum(Vector3D &value)
{
    auto mom_mag = value.x*value.x + value.y*value.y + value.z*value.z;
    auto mass = get_mass();
    energy = sqrt(mom_mag*mom_mag + mass*mass) - mass;
    polar = atan2(sqrt(value.x*value.x + value.y*value.y), value.z);
    azimuth = atan2(value.y, value.x);
}