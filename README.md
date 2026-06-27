# Circuit Simulator

A C++ project built to learn software engineering, Git/GitHub workflows, and electronics concepts by gradually developing a circuit simulator from scratch.

The long-term goal is to evolve this project from a simple calculator into a more advanced circuit analysis and simulation tool.

## Current Version

v4.1 – Circuit Builder 2.0

### Features

#### Electrical Calculations

- Calculate Resistance, Voltage, Power, Current from any combination of two or more known quantities
- SI units (ohm, V, W, A) are now supported
- prefixes k(kilo) and m(milli) are now supported

#### Resistance Networks

- Series Resistance
- Parallel Resistance
- Build arbitrary series/parallel resistor networks using expressions such as: R1+R2||R3
- "+" is series and "||" is parallel
---

## Project Structure

src/
│
├── main.cpp
├── menus.cpp
├── menus.h
│
├── elec_calculation.cpp
├── elec_calculation.h
│
├── elec_quantity.cpp
├── elec_quantity.h
│
├── resistance.cpp
├── resistance.h
│
├── resistors.cpp
├── resistors.h
│
├── utilities.cpp
└── utilities.h

## Concepts Practiced

- Functions
- Header Files
- Multi-file Projects
- Strings
- STL
- Modular Design
- Vectors
- Git
- GitHub
- Version Tags
- OOPs
- Maps
- Unordered_maps
- Stacks
- Exception Handling
- Expression Parsing

## Building the Project

Compile:
g++ -std=c++23 *.cpp -o main

Run:
./main

## Roadmap

- [x] V1 - Ohm's Law Calculator
- [x] V2 - Circuit Fundamentals Calculator
- [x] V3 - Component-Based Architecture
- [x] V4 - Circuit Builder
    - [x] V4.1 - Circuit Builder 2.0
    - [ ] V4.2 - Circuit Builder 3.0
- [ ] V5 - RC Circuit Simulation
- [ ] V6 - GUI Interface
- [ ] V7 - Mini-SPICE Style Simulator

---

## Why I Built This

This project serves as a long-term learning project for:

- C++
- Software Engineering
- Git & GitHub
- Project Architecture

Rather than building many small projects, the goal is to continuously expand a single project and learn how software evolves over time.