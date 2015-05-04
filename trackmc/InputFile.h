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

struct InputParameters
{
    unsigned int proj_mass;
    unsigned int proj_charge;
    double proj_energy;
    std::vector<double> proj_position;
    double proj_polar;
    double proj_azimuth;
    bool is_interaction;
    unsigned int target_mass;
    unsigned int target_charge;
    double vertex_energy;
};

class InputFile
{
public:
    InputFile();

    const std::vector<double>& get_efield() const;
    const std::vector<double>& get_bfield() const;
    const std::string& get_gas_path() const;
    double get_gas_pressure() const;
    const std::vector<InputParameters>& get_track_parameters() const;

    void parse(const std::string filename);

private:
    std::vector<double> efield;
    std::vector<double> bfield;

    std::string gas_path;
    double gas_pressure;

    std::vector<InputParameters> track_parameters;
};


#endif //TRACKMC_INPUTFILE_H
