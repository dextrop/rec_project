#include <jni.h>
#include <string>
#include <android/log.h>
#include <core/lib_trill.h>
#include <core/responses.h>

//setting up the configuration
//step 1 : Setting the configuration before libtrill instance is created
ConfigSettings cfg("noisy");

//creating the lib-trill instance
//make sure the configuration is set before creating libtrill instance
//step 2 : Create the LibTrill Instance
LibTrill sdkInstance;
int dataLength = 6;

//LibTrill sdkInstance;

//DATA_TYPE dataType = DATA_TYPE::LIQUIDCHAR10;
//fec_scheme fec_s = LIQUID_FEC_CONV_V39;
//bool isDebug = true;
//int NO_OF_PREV_CTS_CHUNKS = 8;

void info_callback(string info) {
//    __android_log_print(ANDROID_LOG_ERROR, "Native LOGS -> ", "Data :  %s ", info.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_trillbit_myapplication_core_CWrapper_setUp(JNIEnv *env, jclass clazz) {
    // TODO: implement setUp()
    __android_log_print(ANDROID_LOG_ERROR, "Native LOGS", "Setting Up -> SDK Started");
    sdkInstance.SetCallBack(info_callback);
    sdkInstance.Setup(dataLength);
    __android_log_print(ANDROID_LOG_ERROR, "Native LOGS", "Setting Up -> SDK Done");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_trillbit_myapplication_core_CWrapper_resetDecodedString(JNIEnv *env, jclass clazz) {
    // TODO: implement setUp()
    sdkInstance.ResetDecodedString();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_trillbit_myapplication_core_CWrapper_addBuffer(JNIEnv *env, jclass clazz,
                                                        jshortArray samples, jint len) {
    // TODO: implement addBuffer()
    jsize arr_size = env->GetArrayLength( samples );
    std::vector<short> input( arr_size );

    env->GetShortArrayRegion( samples, 0, arr_size, &input[0] );

    std::vector<double> double_vec;
    for (auto val : input)
    {
        double_vec.push_back(val);
    }
//    __android_log_print(ANDROID_LOG_ERROR, "Add Buffer ","This is add buffer");
    sdkInstance.AddBuffer(double_vec);
}

extern "C"
JNIEXPORT int JNICALL
Java_com_trillbit_myapplication_core_CWrapper_processBuffer(JNIEnv *env, jclass clazz) {
    // TODO: implement processBuffer()
    try {

        int result = sdkInstance.ProcessBuffer();
        return result;
    } catch (...){
        __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", "DATA Abort catch done");
        int result =99;
        return result;
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

    float * floatData = new float[audioData.size()];

    for (int i = 0; i < audioData.size() ; i++)
    {
        floatData[i] = audioData[i];
    }
    jfloatArray result_arr = env->NewFloatArray(audioData.size());
    env->SetFloatArrayRegion(result_arr, 0, audioData.size(), floatData);
    return result_arr;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_trillbit_myapplication_core_CWrapper_getDecodedString(JNIEnv *env) {
    // TODO: implement getAudioSamples()
    string decodedString = sdkInstance.GetDecodedString();
    return (env)->NewStringUTF(decodedString.c_str());
}