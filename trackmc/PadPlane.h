//
// Created by Joshua Bradt on 5/6/15.
//

#ifndef TRACKMC_PADPLANE_H
#define TRACKMC_PADPLANE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class PadPlane
{
public:
    PadPlane();
    const int find_pad_number(const double x, const double y) const;
    void load_csv(std::string path);
    void load_binary(std::string path, unsigned long nrows, unsigned long ncols);

    typedef int16_t pad_t;

private:
    std::vector<std::vector<pad_t>> table;

    class UnsafeCastException : public std::exception {};

    template<typename Target, typename Source>
    static Target safe_cast(Source v);
};


#endif //TRACKMC_PADPLANE_H
