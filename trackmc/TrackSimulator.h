//
// Created by Joshua Bradt on 5/2/15.
//

#ifndef TRACKMC_TRACKSIMULATOR_H
#define TRACKMC_TRACKSIMULATOR_H


#include "Vector3D.h"
#include "Particle.h"
#include "Gas.h"
#include "Constants.h"

#include <vector>

struct SimulatedTrack
{
    std::vector<Vector3D> position;
    std::vector<Vector3D> momentum;
    std::vector<double> time;
    std::vector<double> energy;
    std::vector<double> de;
    std::vector<double> azimuth;
    std::vector<double> polar;
};

class TrackSimulator
{
public:
    TrackSimulator(Gas gas, Vector3D ef, Vector3D bf);

    Particle find_next_state(Particle pt, const double tstep) const;
    SimulatedTrack track_particle(Particle pt, const double final_en = 0) const;

    static Vector3D lorentz_force(const Vector3D& vel, const Vector3D& ef, const Vector3D& bf, const double chg);

private:
    Gas gas;
    Vector3D ef {0, 0, 0};
    Vector3D bf {0, 0, 0};
};


#endif //TRACKMC_TRACKSIMULATOR_H
