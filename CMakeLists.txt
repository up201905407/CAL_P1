cmake_minimum_required(VERSION 3.19)
project(CAL_P1)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (WIN32)
    include_directories("$ENV{SFML_PATH}/include")
    link_directories("$ENV{SFML_PATH}/lib")
endif()


# Build GraphViewerCpp
set(GRAPHVIEWERCPP_PATH lib/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

add_executable(CAL_P1 main.cpp
        src/Vehicle/vehicle.h src/Vehicle/vehicle.cpp
        src/Basket/basket.h src/Basket/basket.cpp
        src/Company/company.h src/Company/company.cpp
        src/Graph/Graph.h
        src/Graph/MutablePriorityQueue.h
        src/GraphBuilder/graphbuilder.h
        src/Utils/utils.h src/Utils/utils.cpp
        src/Gui/gui.h
        src/Menu/menu.h src/Menu/menu.cpp
        src/ClarkeWright/ClarkeWright.h
        )

target_link_libraries(CAL_P1 graphviewer)
