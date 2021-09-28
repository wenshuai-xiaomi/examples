#include <stdio.h>
#include <stdint.h>
#include "frontend.h"
#include "frontend_util.h"
#include "micro_audio_c_interface.h"

#if 1
#include <android/log.h>

// Android log function wrappers
static const char* kTAG = "wenshuai";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#endif

void get_micro_audio_frontend(int16_t* input_data, float* result) {
  int sample_rate = 16000;
  int audio_data_size = 16000;
  struct FrontendConfig frontend_config;
  FrontendFillConfigWithDefaults(&frontend_config);

  struct FrontendState frontend_state;
  if (!FrontendPopulateState(&frontend_config, &frontend_state, sample_rate)) {
    fprintf(stderr, "Failed to populate frontend state\n");
    FrontendFreeStateContents(&frontend_state);
  }
  int16_t* audio_data = input_data;
  int index = 0;
  while (audio_data_size > 0) {
    size_t num_samples_read;
    struct FrontendOutput output = FrontendProcessSamples(
        &frontend_state, audio_data, audio_data_size, &num_samples_read);
    audio_data += num_samples_read;
    audio_data_size -= num_samples_read;
    if (output.values != NULL) {
      //printf("a frame output size %d\n", output.size);
      for (int i = 0; i < output.size; ++i) {
        result[index++] = output.values[i]/25.6; 
      }
    }
  }
  FrontendFreeStateContents(&frontend_state); 
}

