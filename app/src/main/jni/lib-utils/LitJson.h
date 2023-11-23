void* CreateJsonData()
{
	void* (*JsonData$$ctor)() = (void* (*)()) POINTER("0x2696680");
	return JsonData$$ctor();
}

void* CreateJsonDataFromJSON(const std::string& json)
{
	void* (*JsonMapper$$ToObject)(il2cppString*) = (void* (*)(il2cppString*)) POINTER("0x26A3F40");
	return JsonMapper$$ToObject(CreateIl2CppString(json.c_str()));
}

void litjson_pointers()
{

}