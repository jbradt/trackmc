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

const double Particle::get_mass() const
{
    return mass_num * Constants::p_mc2;
}

const double Particle::get_si_mass() const
{
    return mass_num * Constants::p_kg;
}

Vector3D Particle::get_velocity() const
{
    auto mom_si = get_momentum() * 1e6 / Constants::c_lgt * Constants::e_chg;
    return mom_si / (get_gamma() * get_si_mass());
}

void Particle::set_velocity(Vector3D &value)
{
    auto gamma = find_gamma(value);
    auto mom_si = value * gamma * get_si_mass();
    auto mom = mom_si / Constants::e_chg * Constants::c_lgt * 1e-6;
    set_momentum(mom);
}

double Particle::get_beta() const
{
    return find_beta(energy, get_mass());
}

double Particle::get_gamma() const
{
    return find_gamma(get_velocity());
}

double Particle::find_beta(const double energy, const double mass)
{
    assert(mass > 0.0);
    assert(energy > 0.0);
    assert(mass + energy > 0);
    
    auto beta = sqrt(energy * (energy + 2*mass)) / (energy + mass);
    if (beta > 1) {
        beta = 1.0;
    }
    return beta;
}

double Particle::find_gamma(const Vector3D &velocity)
{
    auto vmag = velocity.norm();
    if (vmag > Constants::c_lgt) {
        throw Exceptions::SpeedOfLightError(vmag);
    }
    return 1 / sqrt(1 - vmag*vmag / Constants::c_lgt*Constants::c_lgt);
}