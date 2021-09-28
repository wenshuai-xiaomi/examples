cmake_minimum_required(VERSION 3.10)
project(micro_frontend)

add_definitions("-DFIXED_POINT=16")

add_library(micro_frontend SHARED 
    #bits: just bits.h
    #fft
    fft.cc
    fft_util.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/kissfft/kiss_fft.c
    ${CMAKE_CURRENT_SOURCE_DIR}/kissfft/tools/kiss_fftr.c
    #filterbank
    filterbank.c
    filterbank_util.c
    #log_scale
    log_lut.c
    log_scale.c
    log_scale_util.c
    #noise_reduction
    noise_reduction.c
    noise_reduction_util.c
    #pcan_gain_control
    pcan_gain_control.c
    pcan_gain_control_util.c
    #window
    window.c
    window_util.c
    #frontend
    frontend.c
    frontend_util.c
    # interface used by jni
    micro_audio_c_interface.cc
    hello-jni.c 
)

target_include_directories(micro_frontend
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/kissfft
        ${PROJECT_SOURCE_DIR}/kissfft/tools
)

#add_executable(test_micro_audio_fronten test_micro_interface.c)
#target_link_libraries( test_micro_audio_fronten 
#    PRIVATE
#      micro_frontend 
#)

target_link_libraries( micro_frontend 
    PRIVATE
       android
       log
       m 
)

