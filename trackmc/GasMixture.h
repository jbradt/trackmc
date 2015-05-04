//
// Created by Joshua Bradt on 5/4/15.
//

#ifndef TRACKMC_GASMIXTURE_H
#define TRACKMC_GASMIXTURE_H

#include <vector>
#include "Gas.h"

class GasMixture : public Gas
{
public:
    GasMixture(double pressure, std::vector<std::string> files, std::vector<double> proportions);
};

#endif //TRACKMC_GASMIXTURE_H
