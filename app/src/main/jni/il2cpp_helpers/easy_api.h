#pragma once

typedef int32_t il2cpp_int_t;
typedef int64_t il2cpp_long_t;

namespace IL2CPP
{

	// Helper functions

	const Il2CppImage* FindImage(const char* namespaze, const char* klass) {
		size_t size;
		const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(il2cpp_domain_get(), &size);

		for (int i = 0; i < size; ++i)
		{
			const Il2CppImage* image = il2cpp_assembly_get_image(assemblies[i]);

			void *testClass = il2cpp_class_from_name(image, namespaze, klass);
			if (testClass) {
				return image;
			}
		}

		LOGE("il2cpp: couldn't find image for %s", klass);
		return nullptr;
	}

	// Define the base types

	struct AbstractMethod;
	template<typename T, typename ...args> struct Method;

	struct AbstractProperty;
	template<typename T> struct Property;

	// Actually define the code

	struct AbstractMethod {

		MethodInfo* info;
		AbstractMethod() noexcept = default;
		AbstractMethod(MethodInfo* other) { info = other; }

		uintptr_t GetOffset() {
			return (uintptr_t)info->methodPointer;
		}

		template<typename T, typename ...args> inline Method<T, args...> &cast() const { return (Method<T, args...> &)*this; }

	};

	template<typename T, typename ...args>
	struct Method : public AbstractMethod {
		
		Method() noexcept = default;
		Method(MethodInfo* other) { info = other; }
		Method(const AbstractMethod &other) : AbstractMethod(other) {}

		T call(args... arg) {
			return ((T(*)(args...))GetOffset())(arg...);
		}

		Method<T, args...> &operator =(const Method &other) {
			info = other.info;
			return *this;
		}

		T operator ()(args... arg) { return call(arg...); }

	};

	struct AbstractProperty {

		PropertyInfo* info;

		AbstractMethod getter;
		AbstractMethod setter;

		AbstractProperty() noexcept = default;
		AbstractProperty(PropertyInfo* other)
		{
			info = other;

			if (other->get)
				getter = AbstractMethod((MethodInfo*)other->get);
			else
				LOGW("il2cpp: getter for property %s does not exist", other->name);

			if (other->set)
				setter = AbstractMethod((MethodInfo*)other->set);
			else
				LOGW("il2cpp: setter for property %s does not exist", other->name);
		}

		template<typename T> inline Property<T> &cast() const { return (Property<T> &)*this; }

	};

	template<typename T>
	struct Property : public AbstractProperty {

		Property() noexcept = default;
		Property(const AbstractProperty &other) : AbstractProperty(other) {}

		T get() {
			return getter.cast<T>();
		}

		T get_instance(void* instance) {
			return getter.cast<T, void*>(instance);
		}

		Property<T> &operator =(const Property &other) {
			info = other.info;
			return *this;
		}

		T operator ()() { return get(); }
		T operator ()(void* instance) { return get_instance(instance); }

	};

	struct Class {

		Il2CppClass* klass;

		Class() noexcept = default;
		Class(Il2CppClass* other) { klass = other; }

		Class(const char* namespaze, const char* name)
		{
			klass = il2cpp_class_from_name(FindImage(namespaze, name), namespaze, name);
		}

		Class(const char* name)
		{
			klass = il2cpp_class_from_name(FindImage("", name), "", name);
		}

		AbstractMethod GetMethod(const char* name, int args_count = -1)
		{
			MethodInfo* info = (MethodInfo*)il2cpp_class_get_method_from_name(klass, name, args_count);
			if (!info)
				LOGE("il2cpp: couldn't find method %s", name);
			return AbstractMethod(info);
		}

		AbstractProperty GetProperty(const char* name)
		{
			PropertyInfo* info = (PropertyInfo*)il2cpp_class_get_property_from_name(klass, name);
			if (!info)
				LOGE("il2cpp: couldn't find property %s", name);
			return AbstractProperty(info);
		}

	};
};