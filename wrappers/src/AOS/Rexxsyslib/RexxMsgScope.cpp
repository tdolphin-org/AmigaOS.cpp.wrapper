//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "RexxMsgScope.hpp"

#include <proto/rexxsyslib.h>
#include <stdexcept>

namespace AOS::Rexxsyslib
{
    RexxMsgScope::RexxMsgScope(const std::string &name, bool exceptionOnError)
      : mMsgPortScope(name, exceptionOnError)
    {
        if (!mMsgPortScope.msgPort())
            return;

        // http://amigadev.elowar.com/read/ADCD_2.1/Includes_and_Autodocs_3._guide/node054A.html
        // extension (2nd arg) - default extension for the REXX scripts. If this is NULL, the default is "REXX"
        // host (3rd arg) - the name must be the same as the name of the public message port that is to be the
        // default host. If this field is NULL, the default is REXX.
        // AmigaOS/MorphOS take CONST_STRPTR (const char* in C++); AROS clib/inline take UBYTE *.
#ifdef __AROS__
        mpRexxMsg = CreateRexxMsg(mMsgPortScope.msgPort(), nullptr, (UBYTE *)name.c_str());
#else
        mpRexxMsg = CreateRexxMsg(mMsgPortScope.msgPort(), nullptr, name.c_str());
#endif
        if (mpRexxMsg == nullptr && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreateRexxMsg(...) failed!";
            throw std::runtime_error(error);
        }
    }

    RexxMsgScope::RexxMsgScope(bool exceptionOnError)
      : mMsgPortScope(exceptionOnError)
    {
        mpRexxMsg = CreateRexxMsg(mMsgPortScope.msgPort(), nullptr, nullptr);
        if (mpRexxMsg == nullptr && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreateRexxMsg(...) failed!";
            throw std::runtime_error(error);
        }
    }

    RexxMsgScope::~RexxMsgScope()
    {
        if (mpRexxMsg != nullptr)
            DeleteRexxMsg(mpRexxMsg);
    }
}
