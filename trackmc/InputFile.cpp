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

const std::vector<std::string> InputFile::get_gas_paths() const
{
    return gas_paths;
}


const std::vector<double> InputFile::get_gas_proportions() const
{
    return gas_proportions;
}

double InputFile::get_gas_pressure() const
{
    return gas_pressure;
}

const std::vector<InputEvent>& InputFile::get_events() const
{
    return events;
}

void InputFile::parse(const std::string filename)
{
    YAML::Node config = YAML::LoadFile(filename);

    // Parse fields section

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

    // Parse gas section

    if (config["gas"]) {
        YAML::Node gas = config["gas"];

        if (gas["pressure"]) {
            gas_pressure = gas["pressure"].as<double>();
        }
        else {
            std::cout << "Must specify gas pressure." << std::endl;
            throw Exceptions::InvalidInput();
        }

        gas_paths.clear();
        gas_proportions.clear();

        if (gas["components"]) {
            YAML::Node components = gas["components"];
            for (auto comp : components) {
                if (comp["path"] and comp["proportion"]) {
                    gas_paths.push_back(comp["path"].as<std::string>());
                    gas_proportions.push_back(comp["proportion"].as<double>());
                }
                else {
                    std::cout << "Must specify path and proportion for each gas component"
                              << std::endl;
                    throw Exceptions::InvalidInput();
                }
            }
            assert(gas_paths.size() == gas_proportions.size());
        }
        else {
            std::cout << "Must specify at least 1 gas component" << std::endl;
            throw Exceptions::InvalidInput();
        }
    }
    else {
        std::cout << "Missing gas section in input file." << std::endl;
        throw Exceptions::InvalidInput();
    }

    // Parse events section

    if (config["events"]) {
        YAML::Node events_node = config["events"];

        for (auto event : events_node) {
            InputEvent evt_in;

            if (event["particles"]) {
                YAML::Node particles = event["particles"];
                for (auto part : particles) {
                    ParticleParameters params;

                    if (part["mass"] and part["charge"]) {
                        params.mass = part["mass"].as <unsigned int>();
                        params.charge = part["charge"].as <unsigned int>();
                    }
                    else {
                        std::cout << "Must specify particle charge and mass." << std::endl;
                        throw Exceptions::InvalidInput();
                    }

                    if (part["energy"]) {
                        params.energy = part["energy"].as<double>();
                    }
                    else {
                        std::cout << "Particle energy not given. Assuming zero." << std::endl;
                        params.energy = 0;
                    }

                    if (part["final_energy"]) {
                        params.final_energy = part["final_energy"].as<double>();
                    }
                    else {
                        std::cout << "Particle final energy not given. Assuming zero." << std::endl;
                        params.final_energy = 0;
                    }

                    if (part["position"]) {
                        params.position = part["position"].as<std::vector<double>>();
                        assert(params.position.size() == 3);
                    }
                    else {
                        std::cout << "Particle position not given. Assuming [0, 0, 0]" << std::endl;
                        params.position = {0, 0, 0};
                    }

                    if (part["polar"]) {
                        params.polar = part["polar"].as<double>();
                    }
                    else {
                        std::cout << "Particle polar angle not given. Assuming zero." << std::endl;
                        params.polar = 0;
                    }

                    if (part["azimuthal"]) {
                        params.azimuth = part["azimuthal"].as<double>();
                    }
                    else {
                        std::cout << "Particle azimuthal angle not given. Assuming zero." << std::endl;
                        params.azimuth = 0;
                    }
                    evt_in.particles.push_back(std::move(params));
                }
            }  // if particles key exists
            else {
                std::cout << "No particles were specified." << std::endl;
                throw Exceptions::InvalidInput();
            }

            this->events.push_back(std::move(evt_in));
        }  // for loop over events_node section
    }  // if events key exists
    else {
        std::cout << "No events were specified." << std::endl;
        throw Exceptions::InvalidInput();
    }
}
