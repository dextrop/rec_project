#ifndef LOG_DEBUG_H

#define LOG_DEBUG_H

#include <iostream>
#include <string>
#include <core/sdkconfig.h>
using namespace std;
#ifdef Android
#include <android/log.h>
#endif


using namespace std;
#define DEBUG_LEVEL_HIGH 1
#define DEBUG_LEVEL_MEDIUM 2
#define DEBUG_LEVEL_LOW 3
#define DEBUG_LEVEL_NONE 0

#if RELEASE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#else
#define DEBUG_LEVEL DEBUG_LEVEL_HIGH
#endif

#if DEBUG_LEVEL == DEBUG_LEVEL_NON
#define DEBUG_HIGH(a)
#define DEBUG_MEDIUM(a)
#define DEBUG_LOW(a)
#define DEBUG_HIGH_WITHOUT_ENDL(a)
#define DEBUG_MEDIUM_WITHOUT_ENDL(a)
#endif

//Temp Fix
#if 1
#define DEBUG_HIGH(a) cout << "DEBUG_HIGH : " << a << endl
#define DEBUG_HIGH_WITHOUT_ENDL(a) cout << a
#define DEBUG_HIGH_WITH_CARRY_RETURN(a) cout << "\r" << a
#define DEBUG_MEDIUM_WITHOUT_ENDL(a)
#define DEBUG_MEDIUM(a)
#define DEBUG_LOW(a)

#endif

#if DEBUG_LEVEL == DEBUG_LEVEL_HIGH
#ifdef Linux
#define DEBUG_HIGH(a) cout << "DEBUG_HIGH : " << a << endl
#define DEBUG_HIGH_WITHOUT_ENDL(a) cout << a
#define DEBUG_HIGH_WITH_CARRY_RETURN(a) cout << "\r" << a
#define DEBUG_MEDIUM_WITHOUT_ENDL(a)
#define DEBUG_MEDIUM(a)
#define DEBUG_LOW(a)
#endif

#ifdef Web
#define DEBUG_HIGH(a) cout << "DEBUG_HIGH : " << a << endl
#define DEBUG_HIGH_WITHOUT_ENDL(a) cout << a
#define DEBUG_HIGH_WITH_CARRY_RETURN(a) cout << "\r" << a
#define DEBUG_MEDIUM_WITHOUT_ENDL(a)
#define DEBUG_MEDIUM(a)
#define DEBUG_LOW(a)
#endif

#ifdef Android
#define DEBUG_HIGH(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str());
#define DEBUG_HIGH_WITHOUT_ENDL(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#define DEBUG_HIGH_WITH_CARRY_RETURN(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#define DEBUG_MEDIUM_WITHOUT_ENDL(a)
#define DEBUG_MEDIUM(a)
#define DEBUG_LOW(a)
#endif

#endif

#if DEBUG_LEVEL == DEBUG_LEVEL_MEDIUM

#ifdef Linux
#define DEBUG_HIGH(a) cout << "DEBUG_HIGH : " << a << endl
#define DEBUG_HIGH_WITHOUT_ENDL(a) cout << a
#define DEBUG_MEDIUM_WITHOUT_ENDL(a) cout << a
#define DEBUG_MEDIUM(a) cout << "DEBUG_MEDIUM : " << a << endl
#define DEBUG_LOW(a)
#endif

#ifdef Web
#define DEBUG_HIGH(a) cout << "DEBUG_HIGH : " << a << endl
#define DEBUG_HIGH_WITHOUT_ENDL(a) cout << a
#define DEBUG_MEDIUM_WITHOUT_ENDL(a) cout << a
#define DEBUG_MEDIUM(a) cout << "DEBUG_MEDIUM : " << a << endl
#define DEBUG_LOW(a)
#endif

#ifdef Android
#define DEBUG_HIGH(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#define DEBUG_HIGH_WITHOUT_ENDL(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#define DEBUG_MEDIUM_WITHOUT_ENDL(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#define DEBUG_MEDIUM(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#define DEBUG_LOW(a)
#endif

#endif

#if DEBUG_LEVEL == DEBUG_LEVEL_LOW

#ifdef Linux
#define DEBUG_HIGH(a) cout << "DEBUG_HIGH : " << a << endl
#define DEBUG_MEDIUM(a) cout << "DEBUG_MEDIUM : " << a << endl
#define DEBUG_LOW(a) cout << "DEBUG_LOW : " << a << endl
#endif

#ifdef Web
#define DEBUG_HIGH(a) cout << "DEBUG_HIGH : " << a << endl
#define DEBUG_MEDIUM(a) cout << "DEBUG_MEDIUM : " << a << endl
#define DEBUG_LOW(a) cout << "DEBUG_LOW : " << a << endl
#endif

#ifdef Android
#define DEBUG_HIGH(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#define DEBUG_MEDIUM(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#define DEBUG_LOW(a) __android_log_print(ANDROID_LOG_ERROR, "JNI LOGS", a.c_str())
#endif


#endif

#endif
