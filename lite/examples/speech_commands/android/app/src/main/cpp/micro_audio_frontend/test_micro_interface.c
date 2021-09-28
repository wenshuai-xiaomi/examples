/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

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
#include <stdio.h>

#include "micro_audio_c_interface.h"
#include "cut100.h"

int main(void) {
  float output[98*40];
  get_micro_audio_frontend(g_pcm_data, output);
  
  printf("------------------------------------>\n");
  
  for (int i=0; i<3920; i++) {
    if (i%10== 0) printf("\n");
    printf("%f, ", output[i]);
  }
  printf("\n<------------------------------------>\n");

  return 0;
}
