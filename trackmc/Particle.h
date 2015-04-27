//
//  Particle.h
//  trackmc
//
//  Created by Joshua Bradt on 4/27/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#ifndef __trackmc__Particle__
#define __trackmc__Particle__

#include "Vector3D.h"
#include <cmath>

class Particle {
public:
    Particle(unsigned int mass_num, unsigned int charge_num,
             double energy_per_particle, Vector3D position,
             double azimuth, double polar);
    
    Vector3D get_momentum() const;
    void set_momentum(Vector3D& value);
    
    double get_mass() const;
    double get_si_mass() const;
    
    Vector3D get_velocity() const;
    void set_velocity(Vector3D& value);
    
    double get_beta() const;
    double get_gamma() const;
    
    unsigned int mass_num {0};
    unsigned int charge_num {0};
    double energy {0};
    double polar {0};
    double azimuth {0};
    Vector3D position {0, 0, 0};
};

#endif /* defined(__trackmc__Particle__) */
