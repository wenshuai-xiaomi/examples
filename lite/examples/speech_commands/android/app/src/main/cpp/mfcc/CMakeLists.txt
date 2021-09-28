cmake_minimum_required(VERSION 3.4.1)

file(
        GLOB SOURCES
        *.c
        *.cpp
        *.h
        *.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/fft2d/fftsg.c
)

add_library(hello-jni SHARED
            ${SOURCES})

# Include libraries needed for hello-jni lib
target_link_libraries(hello-jni
                      android
                      log
                      m)
