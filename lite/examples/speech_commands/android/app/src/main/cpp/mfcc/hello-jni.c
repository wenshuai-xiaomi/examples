/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include "mfcc_c_interface.h"
#include "array_input.h"

// Android log function wrappers
static const char* kTAG = "wenshuai";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))


/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   hello-jni/app/src/main/java/com/example/hellojni/HelloJni.java
 */
JNIEXPORT jstring JNICALL
Java_org_tensorflow_lite_examples_speech_SpeechActivity_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
    //return (*env)->NewStringUTF(env, "arm64-v8a");
    return (*env)->NewStringUTF(env, "arm64-v8a");
}


JNIEXPORT jfloatArray JNICALL
Java_org_tensorflow_lite_examples_speech_SpeechActivity_getMfccFromSampleData( JNIEnv* env,
                                                           jobject thiz,
                                                           jfloatArray data )
{
    //1.获取数组指针
    jfloat *inputArray = (*env)->GetFloatArrayElements(env, data, NULL);

    //2.获取数组长度
    int len = (*env)->GetArrayLength(env, data);
    //LOGI("input len should be 16000 %d", len);
    //LOGI("test input data: %f %f", inputArray[0], inputArray[1]);

    //3.Process data

    //4.释放资源
    (*env)->ReleaseFloatArrayElements(env, data , inputArray, JNI_COMMIT);

    //1.新建长度len数组
    jfloatArray joutputArray = (*env)->NewFloatArray(env, 98*40);
    //jfloatArray joutputArray = (*env)->NewFloatArray(env, 2);
    //2.获取数组指针
    jfloat *arr = (*env)->GetFloatArrayElements(env, joutputArray, NULL);
    //3. process data
    //arr[0] = 23.45;
    //arr[1] = 89.12;


    //get_mfcc(input_test, arr);
    get_mfcc(inputArray, arr);
#if 0
    for (int i=0; i<40; i++) {
        LOGI("%f", arr[i]);
    }
#endif

    //4.释放资源
    (*env)->ReleaseFloatArrayElements(env, joutputArray, arr, 0);
    //5.返回数组
    return joutputArray;
}
