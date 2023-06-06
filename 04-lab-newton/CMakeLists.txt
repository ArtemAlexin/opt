cmake_minimum_required(VERSION 3.19)
project(04_lab_newton)

set(CMAKE_CXX_STANDARD 20)



include(definitions.cmake)

add_subdirectory(${SRC}/graphics)



add_executable(matrix_lab_tests
        ${GENERATORS_MATRIX_LAB}
        ${LATEX_TOOLS}
        ${LINEAR_SYSTEM_SOLVERS}
        ${MATRICES}
        ${GTEST}
        ${TEST}/matrix_lab_tests.cpp
        )

target_link_libraries(matrix_lab_tests -pthread)



add_executable(newton_lab_tests
        ${GENERATORS_MATRIX_LAB}
        ${LATEX_TOOLS}
        ${LINEAR_SYSTEM_SOLVERS}
        ${MATRICES}
        ${NEWTON_METHODS}
        ${GTEST}
        ${UNIDIM_METHODS}
        ${QUASINEWTON_METHODS}
        ${TEST}/newton_lab_tests.cpp
        )

target_link_libraries(newton_lab_tests -pthread)



add_executable(quasi_newton_lab_tests
        ${FUNCTIONS}
        ${GENERATORS_MATRIX_LAB}
        ${MATRICES}
        ${QUASI_NEWTON_METHODS}
        ${UNIDIM_METHODS}
        ${GTEST}
        ${TEST}/quasi_newton_lab_tests.cpp
        )

target_link_libraries(quasi_newton_lab_tests -pthread)

