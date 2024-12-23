// thanks to shmoo and joeyjurjens for the usefull stuff under this comment.
#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

#include "../Misc/dobby.h"

/*void hook(void *offset, void* ptr, void **orig)
{
#if defined(__aarch64__)
    A64HookFunction(offset, ptr, orig);
#else
    MSHookFunction(offset, ptr, orig);
#endif
}*/

void hook(void *orig_fcn, void* new_fcn, void **orig_fcn_ptr)
{
    DobbyHook(orig_fcn, new_fcn, orig_fcn_ptr);
}

#define POINTER(offset) getAbsoluteAddress(targetLibName, string2Offset(offset));
#define POINTER_NOSEMICOLON(offset) getAbsoluteAddress(targetLibName, string2Offset(offset))

#define HOOK(offset, ptr, orig) DobbyHook((void *)(il2cppMap.startAddress + string2Offset(offset)), (void *)ptr, (void **)&orig)
#define HOOK_DIRECT(offset, ptr, orig) DobbyHook((void *)(offset), (void *)ptr, (void **)&orig)
#define HOOK_LIB(map, offset, ptr, orig) DobbyHook((void *)(map.startAddress + string2Offset(offset)), (void *)ptr, (void **)&orig) // uses KittyMemory map instead of library name

#define HOOKSYM(sym, ptr, orig) DobbyHook(DobbySymbolResolver(targetLibName, sym), (void *)ptr, (void **)&orig)
#define HOOKSYM_LIB(lib, sym, ptr, orig) DobbyHook(DobbySymbolResolver(lib, sym), (void *)ptr, (void **)&orig)

std::vector<MemoryPatch> memoryPatches;
std::vector<uint64_t> offsetVector;

// Patching a offset without switch.
void patchOffset(const char *fileName, uint64_t offset, std::string hexBytes, bool isOn) {

    MemoryPatch patch = MemoryPatch::createWithHex(il2cppMap, offset, hexBytes);

    //Check if offset exists in the offsetVector
    if (std::find(offsetVector.begin(), offsetVector.end(), offset) != offsetVector.end()) {
        //LOGE("Already exists");
        std::vector<uint64_t>::iterator itr = std::find(offsetVector.begin(), offsetVector.end(), offset);
        patch = memoryPatches[std::distance(offsetVector.begin(), itr)]; //Get index of memoryPatches vector
    } else {
        memoryPatches.push_back(patch);
        offsetVector.push_back(offset);
        //LOGI("Added");
    }

    if (!patch.isValid()) {
        LOGE("Failing offset: 0x%llu, please re-check the hex", offset);
        return;
    }
    if (isOn) {
        if (!patch.Modify()) {
            LOGE("Something went wrong while patching this offset: 0x%llu", offset);
        }
    } else {
        if (!patch.Restore()) {
            LOGE("Something went wrong while restoring this offset: 0x%llu", offset);
        }
    }
}

void patchOffsetSym(uintptr_t absolute_address, std::string hexBytes, bool isOn) {

    MemoryPatch patch = MemoryPatch::createWithHex(absolute_address, hexBytes);

    //Check if offset exists in the offsetVector
    if (std::find(offsetVector.begin(), offsetVector.end(), absolute_address) != offsetVector.end()) {
        //LOGE("Already exists");
        std::vector<uint64_t>::iterator itr = std::find(offsetVector.begin(), offsetVector.end(), absolute_address);
        patch = memoryPatches[std::distance(offsetVector.begin(), itr)]; //Get index of memoryPatches vector
    } else {
        memoryPatches.push_back(patch);
        offsetVector.push_back(absolute_address);
        //LOGI("Added");
    }

    if (!patch.isValid()) {
        LOGE("Failing offset: 0x%llu, please re-check the hex", absolute_address);
        return;
    }
    if (isOn) {
        if (!patch.Modify()) {
            LOGE("Something went wrong while patching this offset: 0x%llu", absolute_address);
        }
    } else {
        if (!patch.Restore()) {
            LOGE("Something went wrong while restoring this offset: 0x%llu", absolute_address);
        }
    }
}

#define PATCH(offset, hex) patchOffset(targetLibName, string2Offset(offset), hex, true)
#define PATCH_LIB(lib, offset, hex) patchOffset(lib, string2Offset(offset), hex, true)

#define PATCH_SYM(sym, hex) patchOffset(dlsym(dlopen(targetLibName, 4), sym), hex, true)
#define PATCH_LIB_SYM(lib, sym, hex) patchOffset(dlsym(dlopen(lib, 4), sym), hex, true)

#define PATCH_SWITCH(offset, hex, boolean) patchOffset(targetLibName, string2Offset(offset), hex, boolean)
#define PATCH_LIB_SWITCH(lib, offset, hex, boolean) patchOffset(lib, string2Offset(offset), hex, boolean)

#define PATCH_SYM_SWITCH(sym, hex, boolean) patchOffsetSym((uintptr_t)dlsym(dlopen(targetLibName, 4), sym), hex, boolean)
#define PATCH_LIB_SYM_SWITCH(lib, sym, hex, boolean) patchOffsetSym((uintptr_t)dlsym(dlopen(lib, 4), sym), hex, boolean)

#define RESTORE(offset) patchOffset(targetLibName, string2Offset(offset), "", false)
#define RESTORE_LIB(lib, offset) patchOffset(lib, string2Offset(offset), "", false)

#define RESTORE_SYM(sym) patchOffsetSym((uintptr_t)dlsym(dlopen(targetLibName, 4), sym), "", false)
#define RESTORE_LIB_SYM(lib, sym) patchOffsetSym((uintptr_t)dlsym(dlopen(lib, 4), sym), "", false)

#endif //ANDROID_MOD_MENU_MACROS_H