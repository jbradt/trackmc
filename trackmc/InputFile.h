//
// Created by Joshua Bradt on 5/3/15.
//

#ifndef TRACKMC_INPUTFILE_H
#define TRACKMC_INPUTFILE_H

#include <yaml-cpp/yaml.h>
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>
#include "Exceptions.h"

struct ParticleParameters
{
    unsigned int mass;
    unsigned int charge;
    double energy;
    double final_energy;
    std::vector<double> position;
    double polar;
    double azimuth;
};

struct InputEvent
{
    std::vector<ParticleParameters> particles;
};

class InputFile
{
public:
    InputFile();

    const std::vector<double>& get_efield() const;
    const std::vector<double>& get_bfield() const;
    const std::vector<std::string> get_gas_paths() const;
    const std::vector<double> get_gas_proportions() const;
    double get_gas_pressure() const;
    const std::vector<InputEvent>& get_events() const;

    void parse(const std::string filename);

private:
    std::vector<double> efield;
    std::vector<double> bfield;

    double gas_pressure;
    std::vector<std::string> gas_paths;
    std::vector<double> gas_proportions;

    std::vector<InputEvent> events;
};


#endif //TRACKMC_INPUTFILE_H
