//for the skids that dont know what this is, let me educate you:
/*
these are 'macros' 
*/

#include <cstdint>

#define setnvalue(obj, x) \
    { \
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(obj); \
        *reinterpret_cast<double*>(i_o) = (x); \
        *reinterpret_cast<unsigned char*>(i_o + sizeof(double)) = LUA_TNUMBER; \
    }

#if LUA_VECTOR_SIZE == 4
#define setvvalue(obj, x, y, z, w) \
    { \
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(obj); \
        float* i_v = reinterpret_cast<float*>(i_o); \
        i_v[0] = (x); \
        i_v[1] = (y); \
        i_v[2] = (z); \
        i_v[3] = (w); \
        *reinterpret_cast<unsigned char*>(i_o + sizeof(float) * LUA_VECTOR_SIZE) = LUA_TVECTOR; \
    }
#else
#define setvvalue(obj, x, y, z, w) \
    { \
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(obj); \
        float* i_v = reinterpret_cast<float*>(i_o); \
        i_v[0] = (x); \
        i_v[1] = (y); \
        i_v[2] = (z); \
        *reinterpret_cast<unsigned char*>(i_o + sizeof(float) * 3) = LUA_TVECTOR; \
    }
#endif

#define setpvalue(obj, x) \
    { \
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(obj); \
        *reinterpret_cast<void**>(i_o) = (x); \
        *reinterpret_cast<unsigned char*>(i_o + sizeof(void*)) = LUA_TLIGHTUSERDATA; \
    }

#define setbvalue(obj, x) \
    { \
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(obj); \
        *reinterpret_cast<bool*>(i_o) = (x); \
        *reinterpret_cast<unsigned char*>(i_o + sizeof(bool)) = LUA_TBOOLEAN; \
    }

#define setsvalue(L, obj, x) \
    { \
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(obj); \
        *reinterpret_cast<void**>(i_o) = reinterpret_cast<void*>(x); \
        *reinterpret_cast<unsigned char*>(i_o + sizeof(void*)) = LUA_TSTRING; \
    }

#define setuvalue(L, obj, x) \
    { \
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(obj); \
        *reinterpret_cast<void**>(i_o) = reinterpret_cast<void*>(x); \
        *reinterpret_cast<unsigned char*>(i_o + sizeof(void*)) = LUA_TUSERDATA; \
    }

#define setthvalue(L, obj, x) \
    { \
        std::uintptr_t i_o = reinterpret_cast<std::uintptr_t>(obj); \
        *reinterpret_cast<void**>(i_o) = reinterpret_cast<void*>(x); \
        *reinterpret_cast<unsigned char*>(i_o + sizeof(void*)) = LUA_TTHREAD; \
    }
