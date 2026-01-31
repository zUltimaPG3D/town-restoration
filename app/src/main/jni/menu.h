// #include "imgui/imgui.h"
#include "Unity/Screen.h"

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
	LOGW("Redirecting %s to %s", orig.c_str(), HTTP_SERVER_URL);
	return CreateIl2CppString(HTTP_SERVER_URL);
}

void hooks()
{
	IL2CPP::Class CommonAPI = IL2CPP::Class("NTCore", "CommonAPI");
	HOOK_DIRECT(CommonAPI.GetMethod("GetDomainURL").GetOffset(), GetDomainURL, old_GetDomainURL);
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
