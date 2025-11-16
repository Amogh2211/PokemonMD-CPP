#pragma once
#pragma once

#if defined(_DEBUG) && !defined(PKMD_DEBUG)
#error PKMD_DEBUG should be defined in project settings for debug builds!
#endif

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdbool>
#include <string>
#include <crtdefs.h>
#include <map>
#include <unordered_map>
#include <unordered_set>
// File necessities
#include <iostream>
#include <fstream>
#include <istream>

using string = std::string;
using InterfaceID = size_t;

// Macros to forcibly crash the application when encountering fatal errors
#define PKMD_ABORT_CODE 0xE0000001
#define PKMD_ABORT() RaiseException(PKMD_ABORT_CODE, 0, 0, 0)
#define PKMD_ABORT_CHECK(_code) (GetExceptionCode() == PKMD_ABORT_CODE)

// Completely unnecessary remapping to make it easier to nav to windows exception codes!
#define PKMD_ACCESS_VIOLATION EXCEPTION_ACCESS_VIOLATION

#ifndef PKMD_MEMORY_DEBUG 
#ifdef  PKMD_DEBUG
#define PKMD_MEMORY_DEBUG       // Define PKMD_MEMORY_DEBUG here!!!!! -> (Assignment purpose comments)
#define PKMD_ASSERT_HIDE() PKMD::ScopedAssertHide _unused_hide_
#define PKMD_ASSERT(_expr) if(!(_expr)) _RPT0(_CRT_ASSERT, "Assert: "#_expr)
#define PKMD_WARN(_expr) if(!(_expr)) _RPT0(_CRT_WARN, "Warning: "#_expr)
#define PKMD_ERROR(_expr) if(!(_expr)) { _RPT0(_CRT_ERROR, "Error: "#_expr); PKMD_ABORT(); }
#else
#define PKMD_ASSERT_HIDE()
#define PKMD_ASSERT(_expr)
#define PKMD_WARN(_expr)
#define PKMD_ERROR(_expr) if(!(_expr)) PKMD_ABORT()
#endif // PKMD_DEBUG
#endif // !PKMD_MEMORY_DEBUG 




namespace PKMD
{
    enum Type
    {
        Unknown,
        Int,
        Float,
        String,
        Pointer,
        Table,
        Vec4,
        Mat4
    };


#ifdef PKMD_DEBUG
    struct ScopedAssertHide
    {
        ScopedAssertHide()
        {
            _assertMode = _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
            _warnMode = _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
            _errorMode = _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
        }
        ~ScopedAssertHide()
        {
            _CrtSetReportMode(_CRT_ASSERT, _assertMode);
            _CrtSetReportMode(_CRT_WARN, _warnMode);
            _CrtSetReportMode(_CRT_ERROR, _errorMode);
        }
    private:
        uint32_t _assertMode;
        uint32_t _warnMode;
        uint32_t _errorMode;
    };
#endif

    template <typename T, bool Auto = false>
    struct Singleton
    {
        static void Create() { _Instance = new T; }
        static void Destroy() { delete _Instance; _Instance = nullptr; }
        static T* Instance()
        {
            if (Auto && _Instance == nullptr)
            {
                Create();
            }
            PKMD_ASSERT(_Instance != nullptr);
            return _Instance;
        }

    protected:
        static inline T* _Instance = nullptr;
    };
}