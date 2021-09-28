#include <cmath>
#include <iostream>
#include <fstream>
#include "mfcc.h"
#include "mfcc_dct.h"
#include "mfcc_mel_filterbank.h"
#include "spectrogram.h"
#include "mfcc_c_interface.h"
#include <android/log.h>

// Android log function wrappers
static const char* kTAG = "wenshuai";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))

void get_mfcc(float* input_data, float* mfcc_result) {

  tensorflow::Mfcc mfcc;
  tensorflow::Spectrogram sgram;

  const int kSampleCount = 16000;
  std::vector<double> input(kSampleCount);

  for (int i = 0; i < kSampleCount; ++i) {
    input[i] = input_data[i];
  }

  sgram.Initialize(480, 160);
  
  std::vector<double> output;
  std::vector<std::vector<double>> sgram_output;

  sgram.ComputeSquaredMagnitudeSpectrogram(input, &sgram_output);
  mfcc.Initialize(sgram_output[0].size(), 16000 /*sample rate*/);

  for (int i=0; i<sgram_output.size(); i++) {
    mfcc.Compute(sgram_output[i], &output);
    for (int j = 0; j < 40; ++j) {
      mfcc_result[i*40 + j] = output[j];
    }
  }
}

