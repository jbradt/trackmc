//
// Created by Joshua Bradt on 5/2/15.
//

#include "TrackSimulator.h"

TrackSimulator::TrackSimulator(Gas gas, Vector3D ef, Vector3D bf)
: gas(gas), ef(ef), bf(bf)
{}

Vector3D TrackSimulator::lorentz_force(const Vector3D& vel, const Vector3D& ef, const Vector3D& bf, const double chg)
{
    return chg * (ef + vel.cross(bf));
}

Particle TrackSimulator::find_next_state(Particle pt, const double tstep) const
{
    double en = pt.energy;
    Vector3D mom = pt.get_momentum();
    Vector3D vel = pt.get_velocity();
    double chg = pt.get_charge();

    double beta = pt.get_beta();
    if (beta == 0) {
        pt.energy = 0;
        return pt;
    }

    auto force = lorentz_force(vel, ef, bf, chg);
    Vector3D new_mom = mom + force * tstep;

    double dpos = tstep * beta * Constants::c_lgt;
    double stopping = gas.energy_loss(en);
    double de = stopping * dpos;

    if (stopping <= 0 or de == 0) {
        pt.energy = 0;
        return pt;
    }
    else {
        double new_en = en - de;
        if (new_en < 0) {
            new_en = 0;
        }

        pt.set_momentum(new_mom);
        pt.energy = new_en;
        pt.position = pt.position + pt.get_velocity() * tstep;

        return pt;
    }
}

SimulatedTrack TrackSimulator::track_particle(Particle pt, const double final_en) const
{
    std::vector<Vector3D> pos, mom;
    std::vector<double> time, en, de, azi, pol;
    double current_time {0};
    double pos_step {1e-3};

    pos.push_back(pt.position);
    mom.push_back(pt.get_momentum());
    time.push_back(current_time);
    en.push_back(pt.energy / pt.charge_num);
    de.push_back(0);
    azi.push_back(pt.azimuth);
    pol.push_back(pt.polar);

    bool done {false};
    for (int i = 0; not done; i++) {
        double tstep = pos_step / (pt.get_beta() * Constants::c_lgt);
        pt = find_next_state(pt, tstep);

        if (pt.energy <= final_en) {
            done = true;
        }

        pos.push_back(pt.position);
        mom.push_back(pt.get_momentum());
        en.push_back(pt.energy / pt.mass_num);
        de.push_back(en[i-1] - en[i]);
        azi.push_back(pt.azimuth);
        pol.push_back(pt.polar);

        current_time += tstep;
        time.push_back(current_time);

        if (pt.position.z > 1 or pt.position.z < 0
            or sqrt(pt.position.x*pt.position.x + pt.position.y*pt.position.y) > 0.275) {
                done = true;
        }
    }

    SimulatedTrack res {pos, mom, time, en, de, azi, pol};
    return res;
}
