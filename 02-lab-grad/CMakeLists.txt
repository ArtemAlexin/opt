cmake_minimum_required(VERSION 3.5)

project(02-lab-grad LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

add_executable(02-lab-grad
        main.cpp

        methods/grad_methods.cpp
        methods/grad_methods.h

        undim_methods/undim_methods.cpp
        undim_methods/undim_methods.h

        qcustomplot/qcustomplot.cpp
        qcustomplot/qcustomplot.h

        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        generator/generate_stat.cpp
        generator/generate_stat.h
        )

add_executable(test methods/grad_methods.cpp test/test.cpp
        undim_methods/undim_methods.h
        undim_methods/undim_methods.cpp)

add_executable(generate
        undim_methods/undim_methods.cpp
        undim_methods/undim_methods.h

        generator/generate_stat.cpp
        generator/generate_stat.h

        methods/grad_methods.h
        methods/grad_methods.cpp)

target_link_libraries(02-lab-grad PRIVATE Qt5::Widgets)
target_link_libraries(02-lab-grad PRIVATE Qt5::PrintSupport)

