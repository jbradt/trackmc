//
// Created by Joshua Bradt on 5/4/15.
//

#include "GasMixture.h"

GasMixture::GasMixture(double press, std::vector<std::string> files, std::vector<double> proportions)
{
    pressure = press;

    if (files.size() != proportions.size()) {
        throw Exceptions::ConstructorFailure("Number of files must match number of proportions.");
    }

    double proportions_total {0};
    for (auto prop : proportions) {
        proportions_total += prop;
    }
    if (proportions_total != 1.0) {
        throw Exceptions::ConstructorFailure("Total of gas proportions must equal 1.0");
    }

    molar_mass = 0;
    std::vector<Gas> components;
    for (int i = 0; i < files.size(); i++) {
        components.push_back(Gas(pressure*proportions[i], files[i]));
        molar_mass += components[i].get_molar_mass() * proportions[i];
    }

    en_step = components[0].en_step;
    unsigned long npts = components[0].get_num_pts();
    for (const auto& comp : components) {
        if (comp.en_step != en_step or comp.get_num_pts() != npts) {
            throw Exceptions::ConstructorFailure("de/dx arrays of gas components must have same length and energy step");
        }
    }

    dedx.assign(npts, 0);  // dump the vector contents and replace them with npts copies of zero
    for (int i = 0; i < npts; i++) {
        for (auto& comp : components) {
            dedx[i] += comp.dedx[i] * comp.get_density() / this->get_density();
        }
    }
}