cmake_minimum_required(VERSION 3.19)
project(03_lab_matrix)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto -pedantic")

set(GTEST
        gtest/gtest.h
        gtest/gtest-all.cc
        gtest/gtest_main.cc
        ../04-lab-newton/src/methods/newton_methods/newton_methods.h ../04-lab-newton/src/methods/newton_methods/newton_methods.cpp)

include_directories(gtest src src/matrix)

set(FILES
        src/matrix/CanonicalMatrix.h
        src/matrix/LUMatrix.h
        src/matrix/Matrix.h
        src/matrix/ProfileMatrix.cpp
        src/matrix/ProfileMatrix.h
        src/matrix/SparseMatrix.cpp
        src/matrix/SparseMatrix.h
        src/matrix/Vector.h

        src/generator.h

        src/new_generators.h
        src/new_generators.cpp

        src/LinearSystem.cpp
        src/LinearSystem.h

        src/latex_tools.h
        )

add_executable(03-lab-matrix ${FILES} test.cpp)

add_executable(gtest-testing ${GTEST} ${FILES} gtest_test.cpp)

add_executable(conj_grad_tables ${FILES} conj_grad_tables_generator.cpp)

add_executable(lu_tables ${FILES} lu_tables_generator.cpp)

add_executable(leading_tables ${FILES} leading_tables_generators.cpp)


target_link_libraries(gtest-testing PRIVATE -pthread)
