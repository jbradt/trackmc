# Resources for trackmc program

This folder contains some resources that the program uses.

## Pad lookup table

The pad plane lookup table is stored in ``pad_lookup.dat``. This file is a binary file containing a lookup table
for the pad plane. The lookup table is 5600 x 5600. The entries are in row-major order, and each entry is a 
16-bit signed integer. 

The rows correspond to x positions on the pad plane, and the columns correspond to y positions. Index 0 in each dimension
maps to a position of -280 mm, and the step between positions is 0.1 mm. 