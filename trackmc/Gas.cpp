//
//  Gas.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include <fstream>
#include "Gas.h"

InterpolatedGas::InterpolatedGas(double pressure, double molar_mass)
: pressure(pressure), molar_mass(molar_mass)
{
}

const double InterpolatedGas::energy_loss(const double en)
{
    // en is in MeV. Divide by the energy step and floor to find
    // the nearest integer point
    auto en_idx = static_cast<unsigned long>(round(en / en_step));
    assert(en_idx < dedx.size());
    return dedx.at(en_idx) * get_density();
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

void InterpolatedGas::read_file(std::string filename)
{
    std::ifstream datafile;
    datafile.open(filename, std::ios::in);
    if (datafile.good()) {
        while (datafile.peek() == '#') {
            std::string junkstr;
            std::getline(datafile, junkstr);
        }

        unsigned int numpts {0};

        datafile >> en_step;
        datafile >> numpts;

        dedx.resize(numpts);
        for (int i = 0; i < numpts; i++) {
            datafile >> dedx[i];
        }
    }
    else {
        throw Exceptions::FileNotFound(filename);
    }
}