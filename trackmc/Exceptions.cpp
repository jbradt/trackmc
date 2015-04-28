//
//  Exceptions.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include "Exceptions.h"

using namespace Exceptions;

SpeedOfLightError::SpeedOfLightError(double vmag)
: vmag(vmag)
{}

const char* SpeedOfLightError::what() const noexcept
{
    char* msg;
    sprintf(msg, "Velocity %f exceeded speed of light.", vmag);
    return msg;
}