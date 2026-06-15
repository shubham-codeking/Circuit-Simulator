# Circuit Simulator

A C++ project built to learn software engineering, Git/GitHub workflows, and electronics concepts by gradually developing a circuit simulator from scratch.

The long-term goal is to evolve this project from a simple calculator into a more advanced circuit analysis and simulation tool.

## Current Version

v2.0 – Circuit Fundamentals Calculator

### Features

#### Ohm's Law Calculations

- Calculate Resistance
- Calculate Voltage
- Calculate Current

#### Power Calculations

- Power using Voltage and Current
- Power using Current and Resistance
- Power using Voltage and Resistance

#### Resistance Networks

- Series Resistance
- Parallel Resistance

---

## Project Structure

src/
│
├── main.cpp
├── menus.cpp
├── menus.h
│
├── ohms_law.cpp
├── ohms_law.h
│
├── power.cpp
├── power.h
│
├── resistance.cpp
└── resistance.h

## Concepts Practiced

- Functions
- Header Files
- Multi-file Projects
- Modular Design
- Vectors
- Git
- GitHub
- Version Tags

## Building the Project

Compile:
g++ *.cpp -o main

Run:
./main

## Roadmap

- [x] V1 - Ohm's Law Calculator
- [x] V2 - Circuit Fundamentals Calculator
- [ ] V3 - Component-Based Architecture
- [ ] V4 - Circuit Builder
- [ ] V5 - RC Circuit Simulation
- [ ] V6 - GUI Interface
- [ ] V7 - Mini-SPICE Style Simulator

---

## Why I Built This

This project serves as a long-term learning project for:

- C++
- Software Engineering
- Git & GitHub
- Electronics
- Project Architecture

Rather than building many small projects, the goal is to continuously expand a single project and learn how software evolves over time.