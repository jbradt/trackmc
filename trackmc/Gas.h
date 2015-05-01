//
//  Gas.h
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#ifndef __trackmc__Gas__
#define __trackmc__Gas__

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <assert.h>

#include "Constants.h"
#include "Exceptions.h"

class InterpolatedGas
{
public:
    InterpolatedGas(double pressure, double molar_mass);

    virtual const double energy_loss(const double en);
    const double get_pressure() const;
    const double get_molar_mass() const;
    const double get_density() const;

    void read_file(std::string filename);

private:
    double pressure {0};
    double molar_mass {0};
    double en_step {0};
    std::vector<double> dedx;
};

#endif /* defined(__trackmc__Gas__) */
