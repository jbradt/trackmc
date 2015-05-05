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
#include "InputFile.h"
#include "GasMixture.h"

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cout << "Please provide an input file." << std::endl;
        return 1;
    }

    const char* inputFilePath = argv[1];
    InputFile inputs {};
    try {
        inputs.parse(inputFilePath);
    }
    catch (std::exception& e) {
        std::cout << "Reading of input file failed: " << e.what() << std::endl;
        return 2;
    }

    GasMixture gas(inputs.get_gas_pressure(), inputs.get_gas_paths(), inputs.get_gas_proportions());

    Vector3D ef {inputs.get_efield()};
    Vector3D bf {inputs.get_bfield()};

    TrackSimulator ts {gas, ef, bf};

//    for (const auto& track : inputs.get_events()) {
//        Particle proj {track.mass, track.charge, track.energy, track.position,
//                       track.azimuth, track.polar};
//        SimulatedTrack res = ts.track_particle(proj);
//        for (auto item : res.energy) {
//            std::cout << item << std::endl;
//        }
//    }
}
