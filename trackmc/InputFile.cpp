//
// Created by Joshua Bradt on 5/3/15.
//

#include "InputFile.h"

InputFile::InputFile()
{

}

const std::vector<double>& InputFile::get_efield() const
{
    return efield;
}

const std::vector<double>& InputFile::get_bfield() const
{
    return bfield;
}

const std::string& InputFile::get_gas_path() const
{
    return gas_path;
}

double InputFile::get_gas_pressure() const
{
    return gas_pressure;
}

const std::vector<InputParameters>& InputFile::get_track_parameters() const
{
    return track_parameters;
}


void InputFile::parse(const std::string filename)
{
    YAML::Node config = YAML::LoadFile(filename);

    if (config["fields"]) {
        YAML::Node fields = config["fields"];
        if (fields["electric"]) {
            auto ef_in = fields["electric"].as<std::vector<double>>();
            assert(ef_in.size() == 3);
            efield = ef_in;
        }
        else {
            std::cout << "No electric field given. Assuming zero." << std::endl;
            efield = {0, 0, 0};
        }

        if (fields["magnetic"]) {
            auto bf_in = fields["magnetic"].as<std::vector<double>>();
            assert(bf_in.size() == 3);
            bfield = bf_in;
        }
        else {
            std::cout << "No magnetic field given. Assuming zero." << std::endl;
            bfield = {0, 0, 0};
        }
    }
    else {
        std::cout << "No fields specified. Assuming zero for both." << std::endl;
        efield = {0, 0, 0};
        bfield = {0, 0, 0};
    }

    if (config["gas"]) {
        YAML::Node gas = config["gas"];

        if (gas["path"] and gas["pressure"]) {
            gas_path = gas["path"].as<std::string>();
            gas_pressure = gas["pressure"].as<double>();
        }
        else {
            std::cout << "Must specify gas path and pressure." << std::endl;
            throw Exceptions::InvalidInput();
        }
    }

    if (config["tracks"]) {
        YAML::Node tracks = config["tracks"];

        for (auto track : tracks) {
            InputParameters params;

            if (track["projectile"]) {
                YAML::Node proj = track["projectile"];
                if (proj["mass"] and proj["charge"]) {
                    params.proj_mass = proj["mass"].as <unsigned int>();
                    params.proj_charge = proj["charge"].as <unsigned int>();
                }
                else {
                    std::cout << "Must specify projectile charge and mass." << std::endl;
                    throw Exceptions::InvalidInput();
                }

                if (proj["energy"]) {
                    params.proj_energy = proj["energy"].as<double>();
                }
                else {
                    std::cout << "Projectile energy not given. Assuming zero." << std::endl;
                    params.proj_energy = 0;
                }

                if (proj["position"]) {
                    params.proj_position = proj["position"].as<std::vector<double>>();
                    assert(params.proj_position.size() == 3);
                }
                else {
                    std::cout << "Projectile position not given. Assuming [0, 0, 0]" << std::endl;
                    params.proj_position = {0, 0, 0};
                }

                if (proj["polar"]) {
                    params.proj_polar = proj["polar"].as<double>();
                }
                else {
                    std::cout << "Projectile polar angle not given. Assuming zero." << std::endl;
                    params.proj_polar = 0;
                }

                if (proj["azimuthal"]) {
                    params.proj_azimuth = proj["azimuthal"].as<double>();
                }
                else {
                    std::cout << "Projectile azimuthal angle not given. Assuming zero." << std::endl;
                    params.proj_azimuth = 0;
                }
            }
            else {
                std::cout << "Track must have a projectile." << std::endl;
                throw Exceptions::InvalidInput();
            }

            if (track["target"] and track["vertex"]) {
                YAML::Node target = track["target"];
                YAML::Node vertex = track["vertex"];

                params.is_interaction = true;

                if (target["mass"] and target["charge"]) {
                    params.target_mass = target["mass"].as<unsigned int>();
                    params.target_charge = target["charge"].as<unsigned int>();
                }
                else {
                    std::cout << "Target must have mass and charge specified." << std::endl;
                    throw Exceptions::InvalidInput();
                }

                if (vertex["energy"]) {
                    params.vertex_energy = vertex["energy"].as<double>();
                }
            }
            else {
                params.is_interaction = false;
                params.target_mass = 0;
                params.target_charge = 0;
                params.vertex_energy = 0;
            }

            track_parameters.push_back(params);
        }  // for loop over tracks section
    }  // if tracks key exists
    else {
        std::cout << "No tracks were specified." << std::endl;
        throw Exceptions::InvalidInput();
    }
}
