#include <jni.h>
#include <string>
#include <android/log.h>
#include <core/lib_trill.h>
#include <core/responses.h>

LibTrill sdkInstance;
int dataLength = 6;
DATA_TYPE dataType = DATA_TYPE::LIQUIDCHAR10;
fec_scheme fec_s = LIQUID_FEC_CONV_V39;
bool isDebug = true;
int NO_OF_PREV_CTS_CHUNKS = 8;

void info_callback(string info) {
    __android_log_print(ANDROID_LOG_ERROR, "Native LOGS -> ", "Data :  %s ", info.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_trillbit_myapplication_core_CWrapper_setUp(JNIEnv *env, jclass clazz) {
    // TODO: implement setUp()
    __android_log_print(ANDROID_LOG_ERROR, "Native LOGS", "Setting Up -> SDK Started");
    sdkInstance.Setup(dataLength, NO_OF_PREV_CTS_CHUNKS, dataType);
    sdkInstance.SetVersion("0.2");
    sdkInstance.SetupDemod(6, fec_s);
    __android_log_print(ANDROID_LOG_ERROR, "Native LOGS", "Setting Up -> SDK Done");
    sdkInstance.SetCallBack(info_callback);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_trillbit_myapplication_core_CWrapper_addBuffer(JNIEnv *env, jclass clazz,
                                                        jshortArray samples, jint len) {
    // TODO: implement addBuffer()
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_trillbit_myapplication_core_CWrapper_processBuffer(JNIEnv *env, jclass clazz) {
    // TODO: implement processBuffer()
    try {

        std::string result = sdkInstance.ProcessBuffer();
        __android_log_print(ANDROID_LOG_ERROR, "Final Callback ", "Decoded : %s",
                            result.c_str());
        if (result.length() > 3) {
            __android_log_print(ANDROID_LOG_ERROR, "Final Callback ", "Decoded : %s",
                                result.c_str());
        }
        return (env)->NewStringUTF(result.c_str());
    } catch (...){
        __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", "DATA Abort catch done");
        std::string result ="99";
        return (env)->NewStringUTF(result.c_str());
    }
}

extern "C"
JNIEXPORT jfloatArray JNICALL
Java_com_trillbit_myapplication_core_CWrapper_getAudioSamples(JNIEnv *env, jclass clazz,
                                                              jstring payload) {
    // TODO: implement getAudioSamples()
    const char *inputCharArray = env->GetStringUTFChars(payload,0);
    __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", "Filter: %d String: %s", false , inputCharArray);
    vector<double > audioData = sdkInstance.GetAudioSamples(inputCharArray, false);



    float floatData[audioData.size()];

    for(int h=0;h<audioData.size();h++)
    {
        floatData[h] = (float)audioData[h];
    }


    jfloatArray result_arr = env->NewFloatArray(audioData.size());
    env->SetFloatArrayRegion(result_arr, 0, audioData.size(), floatData);
    return result_arr;
}