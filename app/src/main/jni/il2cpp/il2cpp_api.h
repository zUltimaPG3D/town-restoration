// ty soto sapi <3 <3 <3

#define DO_API(r, n, p) r (*n) p
#include "il2cpp_functions.h"
#undef DO_API
void init_il2cpp_api(void *handle) {
	#define DO_API(r, n, p) {                      \
		n = (r (*) p) xdl_sym(handle, #n, nullptr);\
	}

	#include "il2cpp_functions.h"

	#undef DO_API
}
bool il2cppApiLoaded = false;
long il2cpp_base = 0;
Il2CppDomain* domain;
size_t libCount;
const Il2CppAssembly** libs;
#define DEFAULTS_INIT(field, ns, n) CSharpTypeClass.field = il2cpp_class_from_name(LibImages.mscorlib, ns, n);
#define DEFINE_IMAGE(name) const Il2CppImage* name
struct CSharpTypeClass {
	Il2CppClass* Byte;
	Il2CppClass* Int16;
	Il2CppClass* Int32;
	Il2CppClass* Int64;
	Il2CppClass* Float;
	Il2CppClass* Double;
	Il2CppClass* Char;
	Il2CppClass* String;
	Il2CppClass* Object;
	Il2CppClass* Array;
} CSharpTypeClass;
struct LibImages {
	DEFINE_IMAGE(mscorlib);
	DEFINE_IMAGE(UnityCoreModule);
	DEFINE_IMAGE(Assembly_CSharp);
	DEFINE_IMAGE(Neptune_Core);
	DEFINE_IMAGE(LitJson);
} LibImages;