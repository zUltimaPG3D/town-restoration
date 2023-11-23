void* DummyHeaderTable()
{
    return ((void*(*)())POINTER_NOSEMICOLON("0x27A9BDC"))();
}
void* CreateHttpResponse(int statusCode, const std::string& data, void* header)
{
    return ((void*(*)(int, il2cppString*, void*))POINTER_NOSEMICOLON("0xD3ACD8"))(statusCode, CreateIl2CppString(data.c_str()), header);
}