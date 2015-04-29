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

#include "Constants.h"
#include "Exceptions.h"

class InterpolatedGas
{
public:
    InterpolatedGas(std::string name, double pressure);

    virtual const double energy_loss(const double en, const unsigned int proj_mass,
                                     const unsigned int proj_charge);
    const double get_pressure() const;
    const double get_molar_mass() const;
    const double get_density() const;
private:
    double pressure {0};
    double molar_mass {0};
};

#endif /* defined(__trackmc__Gas__) */
