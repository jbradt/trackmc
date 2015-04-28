//
//  Constants.h
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#ifndef trackmc_Constants_h
#define trackmc_Constants_h

namespace Constants {
    const double e_mc2 = 0.510998928;
    const double p_mc2 = 938.272046;
    const double p_kg = 1.672621777e-27;
    const double e_chg = 1.602176565e-19;
    const double N_avo = 6.02214129e+23;
    const double c_lgt = 299792458;
    const double pi = 3.141592653589793;
    const double eps_0 = 8.8541878e-12;
}

namespace Conversions {
    const double MeVtokg = 1e6 * Constants::e_chg /
                            Constants::c_lgt*Constants::c_lgt;
    const double amuTokg = 1.66054e-27;
    const double amuToMeV = 931.494;
    const double degrees = Constants::pi / 180;
}

#endif
