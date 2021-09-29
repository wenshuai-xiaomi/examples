/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// Declarations for 1D FFT routines in third_party/fft2d/fft2d.

#ifndef MFCC_C_INTERFACE_H__
#define MFCC_C_INTERFACE_H__ __

#ifdef __cplusplus
extern "C" {
#endif

extern void get_micro_audio_frontend(short* input_data, float* mfcc_result);

#ifdef __cplusplus
}
#endif

#endif  // FFT2D_FFT_H__