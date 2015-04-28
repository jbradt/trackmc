//
//  Exceptions.h
//  trackmc
//
//  Created by Joshua Bradt on 4/28/15.
//  Copyright (c) 2015 NSCL. All rights reserved.
//

#ifndef __trackmc__Exceptions__
#define __trackmc__Exceptions__

#include <exception>
#include <string>

namespace Exceptions {

    class SpeedOfLightError : public std::exception
    {
    public:
        SpeedOfLightError(double vmag);
        virtual const char* what() const noexcept;
        
    private:
        double vmag;
    };
}

#endif /* defined(__trackmc__Exceptions__) */