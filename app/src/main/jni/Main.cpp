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
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"
#include "xdl/include/xdl.h"
#include "il2cpp/il2cpp_types.h"
#include "il2cpp/il2cpp_api.h"
#include "Unity.h"
#include "il2cpp_stuff.h"

//Target lib here
#define targetLibName "libil2cpp.so"

#include "Includes/Macros.h"
// #include "imgui/imgui.h"
// #include "imgui/imgui_impl_opengl3.h"
// #include "imgui/imgui_impl_android.h"
#include "menu.h"
#include <GLES2/gl2.h>

// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
	jobjectArray ret;

	const char *features[] = {
		"Button_Test",
		"Toggle_True_Step 1",
		"Toggle_True_Step 2",
		"Toggle_True_Step 3",
		"Toggle_True_Step 4",
		"Toggle_True_Step 5",
		"Toggle_True_Step 6",
		"Button_Clear Prefs",
	};

	//Now you dont have to manually update the number everytime;
	int Total_Feature = (sizeof features / sizeof features[0]);
	ret = (jobjectArray)
			env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
								env->NewStringUTF(""));

	for (int i = 0; i < Total_Feature; i++)
		env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

	return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
										jint featNum, jstring featName, jint value,
										jboolean boolean, jstring str) {

	/*LOGD("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s", featNum,
		 env->GetStringUTFChars(featName, 0), value,
		 boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");*/

	//BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

	switch (featNum)
	{
		case 1:
			step1 = boolean;
			break;
		case 2:
			step2 = boolean;
			break;
		case 3:
			step3 = boolean;
			break;
		case 4:
			step4 = boolean;
			break;
		case 5:
			step5 = boolean;
			break;
		case 6:
			step6 = boolean;
			break;
		case 7:
			((void(*)()) POINTER_NOSEMICOLON("0x19F16B8"))();
			break;
	}
}

__attribute__((constructor))
void lib_main() {
	// Create a new thread so it does not block the main thread, means the game would not freeze
	pthread_t ptid;
	pthread_create(&ptid, NULL, hack_thread, NULL);
}

int RegisterMenu(JNIEnv *env) {
	JNINativeMethod methods[] = {
			{"Icon", "()Ljava/lang/String;", reinterpret_cast<void *>(Icon)},
			{"IconWebViewData",  "()Ljava/lang/String;", reinterpret_cast<void *>(IconWebViewData)},
			{"IsGameLibLoaded",  "()Z", reinterpret_cast<void *>(isGameLibLoaded)},
			{"Init",  "(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V", reinterpret_cast<void *>(Init)},
			{"SettingsList",  "()[Ljava/lang/String;", reinterpret_cast<void *>(SettingsList)},
			{"GetFeatureList",  "()[Ljava/lang/String;", reinterpret_cast<void *>(GetFeatureList)},
	};

	jclass clazz = env->FindClass("com/android/support/Menu");
	if (!clazz)
		return JNI_ERR;
	if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
		return JNI_ERR;
	return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
	JNINativeMethod methods[] = {
			{"Changes", "(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V", reinterpret_cast<void *>(Changes)},
	};
	jclass clazz = env->FindClass("com/android/support/Preferences");
	if (!clazz)
		return JNI_ERR;
	if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
		return JNI_ERR;
	return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
	JNINativeMethod methods[] = {
			{"CheckOverlayPermission", "(Landroid/content/Context;)V", reinterpret_cast<void *>(CheckOverlayPermission)},
	};
	jclass clazz = env->FindClass("com/android/support/Main");
	if (!clazz)
		return JNI_ERR;
	if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
		return JNI_ERR;

	return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
	JNIEnv *env;
	vm->GetEnv((void **) &env, JNI_VERSION_1_6);
	if (RegisterMenu(env) != 0)
		return JNI_ERR;
	if (RegisterPreferences(env) != 0)
		return JNI_ERR;
	if (RegisterMain(env) != 0)
		return JNI_ERR;
	return JNI_VERSION_1_6;
}
