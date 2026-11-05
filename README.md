# C++ Data Structures in the STL

Coursera guided project completed on 5 Nov 2026.

Certificate: https://coursera.org/verify/4ISVYRX48NML

## What I built

A small C++ program that reads weather/rainfall data from a file and uses STL containers to process it:

1. Load rows into a `std::vector`
2. Write the vector to an output file
3. Remove duplicates with a `std::set`
4. Sort unique rows by rainfall into a vector and save them
5. Store records in a `std::map` keyed by year and look one up

## Files

- `main.cpp` — full project
- `rainfall.txt` — sample input (includes duplicates on purpose)
- `Makefile` — build with `make`

## Run

```bash
make
./rainfall
```

## What I practiced

- `vector`, `set`, `map`
- File I/O with `fstream`
- Sorting with `std::sort`
