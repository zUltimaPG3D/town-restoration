// #include "imgui/imgui.h"
#include "Unity/Screen.h"

bool uncap_fps = false;
bool sl_gc = false;

void* SaveData;

void (*old_SaveDataClear)(void* instance);
void SaveDataClear(void* instance)
{
//    LOGW("SaveDataClear()");
}

inline void set_vSyncCount(int count)
{
    IL2CPP::Method<void, int> SetVSyncCount = IL2CPP::Class("UnityEngine", "QualitySettings").GetMethod("set_vSyncCount");
    SetVSyncCount(count);
}

inline void set_targetFrameRate(int fps)
{
    IL2CPP::Method<void, int> SetTargetFrameRate = IL2CPP::Class("UnityEngine", "Application").GetMethod("set_targetFrameRate");
    SetTargetFrameRate(fps);
}

inline void OpenURL(const std::string& url)
{
	((void(*)(il2cppString*))POINTER_NOSEMICOLON("0x19D15D4"))(CreateIl2CppString(url.c_str()));
}

#include "menu_hook.h"
#include "Unity/Input.h"
#include "KittyMemory/KittyScanner.hpp"

using namespace KittyScanner;

il2cppString* (*old_GetDomainURL)(il2cppString* keyName);
il2cppString* GetDomainURL(il2cppString* keyName)
{
	il2cppString* s = old_GetDomainURL(keyName);
	std::string orig = s->getString();
	LOGW("Redirecting %s to localhost", orig.c_str());
	if (!sl_gc) return CreateIl2CppString(HTTP_SERVER_URL);
	return s;
}

il2cppString* (*old_Encrypt)(il2cppString* uid);
il2cppString* Encrypt(il2cppString* uid)
{
//    il2cppString* ret = old_Encrypt(uid);
	LOGW("Game tried to encrypt string %s!", uid->getString().c_str());
	return uid;
}

il2cppString* (*old_Decrypt)(il2cppString* src);
il2cppString* Decrypt(il2cppString* src)
{
	il2cppString* dec_src = old_Decrypt(src);
	LOGW("Game tried to decrypt string %s!", src->getString().c_str());
	LOGW("Decrypted string result: %s", dec_src->getString().c_str());
	return dec_src;
}

il2cppString* (*old_GameCode)();
il2cppString* GameCode()
{
	if (sl_gc) return CreateIl2CppString("SL");
	return old_GameCode();
}

void (*old_FramerateController_AwakeChild)(void* instance);
void FramerateController_AwakeChild(void* instance)
{
    if (uncap_fps) {
        set_targetFrameRate(144);
        set_vSyncCount(0);
        return;
    }

    old_FramerateController_AwakeChild(instance);
}

void* (*old_OpenTask)(void* retstr, void* thiz, il2cppString* messageId, il2cppArray<il2cppString**>* values);
void* OpenTask(void* retstr, void* thiz, il2cppString* messageId, il2cppArray<il2cppString**>* values)
{
    LOGW("OpenTask(\"%s\")", messageId->getString().c_str());
    return old_OpenTask(retstr, thiz, messageId, values);
}

void (*old_SaveData_ctor)(void* thiz);
void SaveData_ctor(void* thiz)
{
    SaveData = thiz;
    old_SaveData_ctor(thiz);
}

bool (*old_get_IsFirstplay)(void* thiz);
bool get_IsFirstplay(void* thiz)
{
    return true;
}

void hooks()
{
	IL2CPP::Class CommonAPI = IL2CPP::Class("NTCore", "CommonAPI");

	HOOK_DIRECT(CommonAPI.GetMethod("GetDomainURL").GetOffset(), GetDomainURL, old_GetDomainURL);

	IL2CPP::Property<il2cppString*> CommonAPI_GameCode = CommonAPI.GetProperty("GameCode");
	HOOK_DIRECT(CommonAPI_GameCode.getter.GetOffset(), GameCode, old_GameCode);

	IL2CPP::Class Crypt = IL2CPP::Class("BX.App.Util", "Crypt");
	HOOK_DIRECT(Crypt.GetMethod("Encrypt").GetOffset(), Encrypt, old_Encrypt);
	HOOK_DIRECT(Crypt.GetMethod("Decrypt").GetOffset(), Decrypt, old_Decrypt);

	HOOK("0x28638F8", FramerateController_AwakeChild, old_FramerateController_AwakeChild);
	HOOK("0x2ACA030", OpenTask, old_OpenTask);
	HOOK("0x29CBA6C", SaveDataClear, old_SaveDataClear);
	HOOK("0x29CBD6C", SaveData_ctor, old_SaveData_ctor);
	HOOK("0x285BC70", get_IsFirstplay, old_get_IsFirstplay);
}

void *hack_thread(void *) {
	LOGI("pthread created");

	do {
		sleep(1);
		il2cppMap = KittyMemory::getElfBaseMap(targetLibName);
	} while (!il2cppMap.isValid());
	do {
		unityMaps = KittyMemory::getMapsEndWith("libunity.so");
	} while (unityMaps.empty());

	LOGI("%s has been loaded", (const char *) targetLibName);
	auto il2cpp_handle = xdl_open("libil2cpp.so", 0);
	init_il2cpp_api(il2cpp_handle);
	if (il2cpp_domain_get_assemblies != nullptr) {

		Dl_info dlInfo;
		if (dladdr((void *) il2cpp_domain_get_assemblies, &dlInfo)) {
			il2cpp_base = reinterpret_cast<uint64_t>(dlInfo.dli_fbase);
		}

		while (!il2cpp_is_vm_thread(nullptr)) {
			sleep(1);
		}

		domain = il2cpp_domain_get();
		il2cpp_thread_attach(domain);
		LibImages.mscorlib = il2cpp_get_corlib();
		libs = il2cpp_domain_get_assemblies(domain, &libCount);

		for (int i = 0; i < libCount; ++i) {
			const Il2CppImage *img = il2cpp_assembly_get_image(libs[i]);
			const char *img_name = il2cpp_image_get_name(img);
			if (strcmp(img_name, "Assembly-CSharp.dll") == 0) {
				LibImages.Assembly_CSharp = img;
			}
			if (strcmp(img_name, "Neptune.Core.dll") == 0) {
				LibImages.Neptune_Core = img;
			}
			if (strcmp(img_name, "LitJson.dll") == 0) {
				LibImages.LitJson = img;
			}
			if (strcmp(img_name, "UnityEngine.CoreModule.dll") == 0) {
				LibImages.UnityCoreModule = img;
			}
		}

		DEFAULTS_INIT(Byte, "System", "Byte");
		DEFAULTS_INIT(Int16, "System", "Int16");
		DEFAULTS_INIT(Int32, "System", "Int32");
		DEFAULTS_INIT(Int64, "System", "Int64");
		DEFAULTS_INIT(Float, "System", "Single");
		DEFAULTS_INIT(Double, "System", "Double");
		DEFAULTS_INIT(Char, "System", "Char");
		DEFAULTS_INIT(String, "System", "String");
		DEFAULTS_INIT(Object, "System", "Object");
		DEFAULTS_INIT(Array, "System", "Array");
		LOGE("il2cpp initialized");
	} else {
		LOGE("failed to initialize il2cpp.");
	}

	hook_menu_stuff();

	UnityEngine::Screen::Setup();
	RegisterNativeFn injecteventptr = KittyScanner::findRegisterNativeFn(unityMaps, "nativeInjectEvent");
	if (injecteventptr.isValid()) {
		DobbyHook(injecteventptr.fnPtr, (void *) nativeInjectEvent, (void **) &old_nativeInjectEvent);
	} else {
		UnityEngine::Input::Setup();
	}

	hooks();

	LOGI("Done");

	return NULL;
}