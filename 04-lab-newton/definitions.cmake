set(LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST ${CMAKE_CURRENT_SOURCE_DIR}/test)


include_directories(
        ${LIB}/gtest
        ${LIB}/qcustomplot

        ${SRC}/functions

        ${SRC}/generators/grad_lab
        ${SRC}/generators/matrix_lab

        ${SRC}/graphics/graph_drawer
        ${SRC}/graphics/visualiser

        ${SRC}/latex_tools

        ${SRC}/linear_system_solvers

        ${SRC}/matrices

        ${SRC}/methods
        ${SRC}/methods/grad_methods
        ${SRC}/methods/unidim_methods
        ${SRC}/methods/newton_methods
        ${SRC}/methods/quasi_newton_methods
)

set(GTEST
        ${LIB}/gtest/gtest.h
        ${LIB}/gtest/gtest-all.cc
        ${LIB}/gtest/gtest_main.cc
        )

set(QCUSTOMPLOT
        ${LIB}/qcustomplot/qcustomplot.h
        ${LIB}/qcustomplot/qcustomplot.cpp
        )

set(FUNCTIONS
        ${SRC}/functions/Function.h
        ${SRC}/functions/QuadFunction.h
        )

set(GENERATORS_MATRIX_LAB
        ${SRC}/generators/matrix_lab/new_generators.h
        ${SRC}/generators/matrix_lab/new_generators.cpp
        ${SRC}/generators/matrix_lab/old_generators.h
        )

set(GRAPH_DRAWER
        ${SRC}/graphics/graph_drawer/GraphDrawerWindow.h
        ${SRC}/graphics/graph_drawer/GraphDrawerWindow.cpp
        )

set(VISUALISER
        ${SRC}/methods/logging.h
        ${SRC}/graphics/visualiser/ui_VisualiserWindow.h
        ${SRC}/graphics/visualiser/VisualiserWindow.h
        ${SRC}/graphics/visualiser/VisualiserWindow.cpp
        )

set(LATEX_TOOLS
        ${SRC}/latex_tools/latex_tools.h
        )

set(LINEAR_SYSTEM_SOLVERS
        ${SRC}/linear_system_solvers/LinearSystem.h
        ${SRC}/linear_system_solvers/LinearSystem.cpp
        )

set(MATRICES
        ${SRC}/matrices/CanonicalMatrix.h
        ${SRC}/matrices/LUMatrix.h
        ${SRC}/matrices/Matrix.h
        ${SRC}/matrices/ProfileMatrix.h
        ${SRC}/matrices/ProfileMatrix.cpp
        ${SRC}/matrices/SparseMatrix.h
        ${SRC}/matrices/SparseMatrix.cpp
        ${SRC}/matrices/Vector.h
        )

set(UNIDIM_METHODS
        ${SRC}/methods/unidim_methods/unidim_methods.h
        ${SRC}/methods/unidim_methods/unidim_methods.cpp
        )

set(NEWTON_METHODS
        ${SRC}/methods/newton_methods/newton_methods.h
        ${SRC}/methods/newton_methods/newton_methods.cpp
        )

set(QUASI_NEWTON_METHODS
        ${SRC}/methods/quasi_newton_methods/quasi_newton_methods.h
        ${SRC}/methods/quasi_newton_methods/quasi_newton_methods.cpp
        )

set(GRAD_METHODS
        ${SRC}/methods/grad_methods/grad_methods.h
        ${SRC}/methods/grad_methods/grad_methods.cpp
        )
