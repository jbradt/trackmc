//
//  Particle.h
//  trackmc
//
//  Created by Joshua Bradt on 4/27/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#ifndef __trackmc__Particle__
#define __trackmc__Particle__

#include <cmath>

#include "Vector3D.h"
#include "Constants.h"
#include "Exceptions.h"

class Particle {
public:
    Particle(unsigned int mass_num, unsigned int charge_num,
             double energy_per_particle, Vector3D position,
             double azimuth, double polar);
    
    Vector3D get_momentum() const;
    void set_momentum(Vector3D& value);
    
    const double get_mass() const;
    const double get_si_mass() const;
    
    Vector3D get_velocity() const;
    
    double get_beta() const;
    double get_gamma() const;
    
    unsigned int mass_num {0};
    unsigned int charge_num {0};
    double energy {0};
    double polar {0};
    double azimuth {0};
    Vector3D position {0, 0, 0};
    
private:
    static double find_beta(const double energy, const double mass);
    static double find_gamma(const Vector3D& velocity);
};

#endif /* defined(__trackmc__Particle__) */
