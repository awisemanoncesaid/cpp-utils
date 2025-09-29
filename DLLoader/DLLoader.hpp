
#pragma once

#include <stdexcept>
#include <string>

#ifdef _WIN32
    #include <windows.h>

    #define LIB_HANDLE HINSTANCE
    #define LIB_LOAD(path) LoadLibrary(path)
    #define LIB_GETSYM(handle, name) GetProcAddress(handle, name)
    #define LIB_CLOSE(handle) FreeLibrary(handle)
    #define LIB_ERROR() "Unknown error"
    #define LIB_PREFIX ""
    #define LIB_SUFFIX ".dll"

#elif __linux__
    #include <dlfcn.h>

    #define LIB_HANDLE void *
    #define LIB_LOAD(path) dlopen(path, RTLD_LAZY)
    #define LIB_GETSYM(handle, name) dlsym(handle, name)
    #define LIB_CLOSE(handle) dlclose(handle)
    #define LIB_ERROR() dlerror()
    #define LIB_PREFIX "lib"
    #define LIB_SUFFIX ".so"

#else
    #error "Unsupported platform"
#endif

namespace cpputils {

    template <typename T>
    class DLLoader {
    public:
        DLLoader(const std::string &path, const std::string &name)
        {
            load(path, name);
        }
        DLLoader()
        {
        }
        ~DLLoader()
        {
            if (_handle)
                LIB_CLOSE(_handle);
        }

        void load(const std::string &path, const std::string &name)
        {
            if (_handle)
                LIB_CLOSE(_handle);
            std::string libPath = path + LIB_PREFIX + name + LIB_SUFFIX;
            _handle = LIB_LOAD(libPath.c_str());
            if (!_handle)
                throw std::runtime_error("Cannot load library: " + std::string(path) + ": " + LIB_ERROR());
        }

        template <typename... Args>
        T *getInstance(const char *name, Args... args) const
        {
            T *(*fptr)(Args...) = reinterpret_cast<T *(*)(Args...)>(LIB_GETSYM(_handle, name));
            if (!fptr)
                throw std::runtime_error("Cannot load symbol \"" + std::string(name) + "\": " + LIB_ERROR());
            return fptr(args...);
        }

        T *getInstance(const char *name) const
        {
            T *(*fptr)(void) = reinterpret_cast<T *(*)(void)>(LIB_GETSYM(_handle, name));
            if (!fptr)
                throw std::runtime_error("Cannot load symbol \"" + std::string(name) + "\": " + LIB_ERROR());
            return fptr();
        }
    private:
        LIB_HANDLE _handle = 0;
    };

} // namespace cpputils