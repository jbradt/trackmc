//
//  main.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/27/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include <iostream>
#include "Particle.h"
#include "Gas.h"
#include "TrackSimulator.h"
#include "Vector3D.h"
#include "Exceptions.h"
#include "Constants.h"

int main(int argc, const char * argv[]) {
    Vector3D pos {0, 0, 0};
    double azi = Constants::pi / 4;
    double pol = Constants::pi / 4;
    double en = 2;

    Particle pt {4, 2, en, pos, azi, pol};

    InterpolatedGas gas {150., 4.};
    gas.read_file("gasdata/helium.dat");

    Vector3D ef {0, 0, 15e3};
    Vector3D bf {0, 0, 1};

    double tstep = 1e-8;

    TrackSimulator ts {gas, ef, bf};

    auto res = ts.track_particle(pt);

    for (auto item : res.energy) {
        std::cout << item << std::endl;
    }
}
