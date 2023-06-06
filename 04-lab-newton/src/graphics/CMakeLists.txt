cmake_minimum_required(VERSION 3.19)
project(04_lab_newton_graphics)



set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)



add_executable(visualiser
        ${QCUSTOMPLOT}
        ${VISUALISER}
        ${FUNCTIONS}
        ${GENERATORS_MATRIX_LAB}
        ${MATRICES}
        ${LINEAR_SYSTEM_SOLVERS}
        ${NEWTON_METHODS}
        ${QUASI_NEWTON_METHODS}
        ${UNIDIM_METHODS}
        ${SRC}/graphics/visualiser/visualiser.cpp
        )

target_link_libraries(visualiser -pthread Qt5::Widgets Qt5::PrintSupport)



add_executable(graph_drawer
        ${QCUSTOMPLOT}
        ${GRAPH_DRAWER}
        ${FUNCTIONS}
        ${GENERATORS_MATRIX_LAB}
        ${MATRICES}
        ${QUASI_NEWTON_METHODS}
        ${UNIDIM_METHODS}
        ${SRC}/graphics/graph_drawer/graph_drawer.cpp
        )

target_link_libraries(graph_drawer -pthread Qt5::Widgets Qt5::PrintSupport)