//
// Created by Joshua Bradt on 5/6/15.
//

#include <math.h>
#include "PadPlane.h"
#include "Exceptions.h"


template<typename Target, typename Source>
Target PadPlane::safe_cast(Source v)
{
    Target narrowed = static_cast<Target>(v);
    Source widened = static_cast<Source>(narrowed);

    if (narrowed != widened) {
        throw UnsafeCastException();
    }

    return narrowed;
}

PadPlane::PadPlane()
{

}

const int PadPlane::find_pad_number(const double x, const double y) const
{
    try {
        auto xidx = safe_cast<uint64_t>(round(x * 10) + 2800);
        auto yidx = safe_cast<uint64_t>(round(y * 10) + 2800);

        int pad = table.at(yidx).at(xidx);
        return pad;
    }
    catch (UnsafeCastException& e) {
        // This should not happen unless the point is outside the pad plane anyway, so return -1
        return -1;
    }
    catch (std::out_of_range& e) {
        // This means we're outside the pad plane anyway, so return -1
        return -1;
    }
}

void PadPlane::load_csv(std::string path)
{
    std::ifstream file;
    file.open(path, std::ios::in);
    if (not file.good()) {
        throw Exceptions::FileNotFound(path);
    }

    table.clear();

    std::string line {};
    while (std::getline(file, line)) {
        std::istringstream ss {line};
        std::string field;

        std::vector<pad_t> row {};

        while (std::getline(ss, field, ',')) {
            pad_t value = static_cast<pad_t>(atoi(field.c_str()));
            row.push_back(value);
        }
        table.push_back(std::move(row));
    }
}

void PadPlane::load_binary(std::string path, unsigned long nrows, unsigned long ncols)
{
    std::ifstream file;
    file.open(path, std::ios::in|std::ios::binary);
    if (not file.good()) {
        throw Exceptions::FileNotFound(path);
    }

    table.resize(nrows);

    for (int i = 0; i < nrows; i++) {
        std::vector<pad_t> row(ncols, -1);
        for (int j = 0; j < ncols; j++) {
            pad_t item;
            file.read((char *) &item, sizeof(item));
            row[j] = item;
        }
        table[i] = std::move(row);
    }
}
