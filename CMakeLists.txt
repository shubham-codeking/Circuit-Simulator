cmake_minimum_required(VERSION 3.20)

project(CircuitSimulator
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CircuitSimulator
    src/main.cpp

    src/core/circuit.cpp
    src/core/components.cpp
    src/core/elec_quantity.cpp
    src/core/node.cpp

    src/components/battery.cpp
    src/components/resistors.cpp
    src/components/switch.cpp

    src/calculations/circuitCalc.cpp
    src/calculations/elec_calculation.cpp
    src/calculations/resistance.cpp

    src/ui/menus.cpp

    src/utilities/circuitUtilities.cpp
    src/utilities/utilities.cpp
)

target_include_directories(CircuitSimulator
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)