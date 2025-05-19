#include <jni.h>
#include <android/log.h>
#include "SDL2/SDL.h"
#include "mygba.h"

extern "C" {
    JNIEXPORT jint JNICALL Java_com_powder_powder_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jstring path) {
        const char* path_str = env->GetStringUTFChars(path, NULL);
        hamfake_setdatapath(path_str);
        env->ReleaseStringUTFChars(path, path_str);
        return 0;
    }

    JNIEXPORT void JNICALL Java_com_powder_powder_SDLActivity_nativeQuit(JNIEnv* env, jclass cls) {
        hamfake_clearForceQuit();
        hamfake_postResurrect();
    }
} 