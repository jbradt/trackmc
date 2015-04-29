//
//  Gas.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include "Gas.h"

InterpolatedGas::InterpolatedGas(std::string name, double pressure)
: pressure(pressure)
{
}

const double InterpolatedGas::energy_loss(const double en, const unsigned int proj_mass,
                                          const unsigned int proj_charge)
{
    return 0;
}

const double InterpolatedGas::get_pressure() const
{
    return pressure;
}

const double InterpolatedGas::get_molar_mass() const
{
    return molar_mass;
}

const double InterpolatedGas::get_density() const
{
    return pressure / 760. * molar_mass / 24040;
}