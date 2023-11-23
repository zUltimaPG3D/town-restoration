void* GetMethodInfoFromDelegate(void* delegate)
{
    void* (*get_Method)(void* instance) = (void*(*)(void*)) POINTER("0x17D666C");
    return get_Method(delegate);
}

il2cppString* GetMemberInfoName(void* memberInfo)
{
    il2cppString* (*get_Name)(void* instance) = (il2cppString*(*)(void*)) POINTER("0x6001387");
    return get_Name(memberInfo);
}