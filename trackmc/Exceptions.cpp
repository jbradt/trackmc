//
//  Exceptions.cpp
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#include "Exceptions.h"

Exceptions::SpeedOfLightError::SpeedOfLightError(double vmag)
: vmag(vmag)
{}

const char* Exceptions::SpeedOfLightError::what() const noexcept
{
    char* msg {0};
    sprintf(msg, "Velocity %f exceeded speed of light.", vmag);
    return msg;
}

Exceptions::FileNotFound::FileNotFound(const char *name)
{
    filename = std::string(name);
}

Exceptions::FileNotFound::FileNotFound(std::string& name)
{
    filename = name;
}

const char* Exceptions::FileNotFound::what() const noexcept
{
    std::string msg {"File not found: "};
    msg.append(filename);
    return msg.c_str();
}

const char* Exceptions::InvalidInput::what() const noexcept
{
    return "Input file was invalid or missing required keys.";
}

Exceptions::ConstructorFailure::ConstructorFailure(std::string msg)
: msg(msg)
{ }

const char *Exceptions::ConstructorFailure::what() const noexcept
{
    std::string base {"Constructor failed: "};
    base.append(msg);
    return base.c_str();
}
