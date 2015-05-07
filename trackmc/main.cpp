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
#include "PadPlane.h"
#include <chrono>

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

    auto start2 = std::chrono::high_resolution_clock::now();
    PadPlane pads2 {};
    pads2.load_binary("./resources/pad_lookup.dat", 5600, 5600);  // TODO: Make this more flexible?
    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Read pads (bin) in " << std::chrono::duration_cast<std::chrono::milliseconds>(end2-start2).count() << " ms" << std::endl;


//    for (const auto& track : inputs.get_events()) {
//        Particle proj {track.mass, track.charge, track.energy, track.position,
//                       track.azimuth, track.polar};
//        SimulatedTrack res = ts.track_particle(proj);
//        for (auto item : res.energy) {
//            std::cout << item << std::endl;
//        }
//    }
}
