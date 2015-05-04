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

class Gas
{
public:
    Gas();
    Gas(double pressure, std::string file);

    virtual const double energy_loss(const double en) const;
    const double get_pressure() const;
    const double get_molar_mass() const;
    const double get_density() const;
    const double get_max_energy() const;
    const unsigned long get_num_pts() const;

    void read_file(std::string filename);

protected:

    double pressure {0};
    double molar_mass {0};
    double en_step {0};
    std::vector<double> dedx;

    friend class GasMixture;
};

#endif /* defined(__trackmc__Gas__) */
