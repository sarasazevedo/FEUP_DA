cmake_minimum_required(VERSION 3.27)
project(project_1_ATWSM)

set(CMAKE_CXX_STANDARD 17)

add_executable(project_1_ATWSM src/main.cpp
        src/Interface.h
        src/Interface.cpp
        src/Station.h
        src/Reservoir.h
        src/City.h
        src/Pipe.h
        src/Pipe.cpp
        src/WaterSupplyManager.h
        src/WaterSupplyManager.cpp
        src/Node.h
        src/Node.cpp
        src/Network.h
        src/Network.cpp
        src/Edmonskarp.cpp
        src/Metrics.h
)
# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/Docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
