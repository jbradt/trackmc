//
//  Gas.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include <fstream>
#include "Gas.h"


Gas::Gas()
: pressure(0), molar_mass(0), en_step(0)
{
}

Gas::Gas(double pressure, std::string file)
: pressure(pressure)
{
    read_file(file);
}

const double Gas::energy_loss(const double en) const
{
    // en is in MeV. Divide by the energy step and floor to find
    // the nearest integer point
    auto en_idx = static_cast<unsigned long>(round(en / en_step));
    assert(en_idx < dedx.size());
    return dedx.at(en_idx) * get_density();
}

const double Gas::get_pressure() const
{
    return pressure;
}

const double Gas::get_molar_mass() const
{
    return molar_mass;
}

const double Gas::get_density() const
{
    return pressure / 760. * molar_mass / 24040;
}

const double Gas::get_max_energy() const
{
    return dedx.size() * en_step;
}

const unsigned long Gas::get_num_pts() const
{
    return dedx.size();
}

void Gas::read_file(std::string filename)
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
        datafile >> molar_mass;
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