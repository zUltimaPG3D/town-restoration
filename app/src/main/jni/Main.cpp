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

#define HTTP_SERVER_URL "http://localhost:15151/"

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