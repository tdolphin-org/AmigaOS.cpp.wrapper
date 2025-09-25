//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "MsgPortScope.hpp"

#include <proto/alib.h>
#include <proto/exec.h>
#include <stdexcept>

namespace AOS::AmigaLib
{
    MsgPortScope::MsgPortScope(bool exceptionOnError)
    {
        mpMsgPort = CreatePort(nullptr, 0);
        if (mpMsgPort == nullptr && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreatePort(...) failed!";
            throw std::runtime_error(error);
        }
    }

    MsgPortScope::MsgPortScope(const std::string &name, bool exceptionOnError)
    {
        if (name.empty())
        {
            if (!exceptionOnError)
                return;

            auto error = std::string { __PRETTY_FUNCTION__ } + " name is empty!";
            throw std::runtime_error(error);
        }

        Forbid();
        if (FindPort(name.c_str()) == nullptr)
            mpMsgPort = CreatePort(name.c_str(), 0);
        Permit();

        if (mpMsgPort == nullptr && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreatePort(...) failed!";
            throw std::runtime_error(error);
        }
    }

    MsgPortScope::~MsgPortScope()
    {
        if (mpMsgPort)
            DeletePort(mpMsgPort);
    }
}
