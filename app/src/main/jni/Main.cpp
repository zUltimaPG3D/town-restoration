#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.hpp"
#include "xdl/include/xdl.h"
#include "il2cpp/il2cpp_types.h"
#include "il2cpp/il2cpp_api.h"
#include "Unity.h"
#include "il2cpp_stuff.h"
#include "il2cpp_helpers/easy_api.h"

// Edit this to wherever your server is running
#define HTTP_SERVER_URL "http://192.168.1.16:15151/"

using namespace KittyMemory;

ProcMap il2cppMap;
ProcMap ntsdkMap;
std::vector<ProcMap> unityMaps;

long idx = 0;
#define STEP() idx++; LOGE("%l", idx)

bool emulator = false;

//Target lib here
#define targetLibName "libil2cpp.so"

#include "Includes/Macros.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_android.h"
#include <GLES2/gl2.h>

#include <android/native_window_jni.h>
#include <jni.h>
#include "ImGuiStuff.h"
#include "Misc/JNIStuff.h"
#include "Misc/JNIHooks.h"

void Toast(const char *text, int length = ToastLength::LENGTH_SHORT) {
	JNIEnv* env = getEnv();
	jobject context = env->GetStaticObjectField(UnityPlayer_cls, UnityPlayer_CurrentActivity_fid);
	jstring jstr = env->NewStringUTF(text);
	jclass toast = env->FindClass("android/widget/Toast");
	jmethodID methodMakeText = env->GetStaticMethodID(toast, "makeText", "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
	jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText, context, jstr, length);
	jmethodID methodShow = env->GetMethodID(toast, "show", "()V");
	env->CallVoidMethod(toastobj, methodShow);
}

#include "menu.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * reserved)
{
	JNIEnv* env;
	// updated input method?
	jvm = vm;
	vm->GetEnv((void **) &env, JNI_VERSION_1_6);

	UnityPlayer_cls = env->FindClass("com/unity3d/player/UnityPlayer");
	UnityPlayer_CurrentActivity_fid = env->GetStaticFieldID(UnityPlayer_cls,
															"currentActivity",
															"Landroid/app/Activity;");
	int ret;
	pthread_t ntid;
	if ((ret = pthread_create(&ntid, nullptr, hack_thread, nullptr)))
		LOGE("can't create thread: %s\n", strerror(ret));
	return JNI_VERSION_1_6;
}
