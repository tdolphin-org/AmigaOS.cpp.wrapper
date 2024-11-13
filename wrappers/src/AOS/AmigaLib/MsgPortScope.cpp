//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "MsgPortScope.hpp"

#include <clib/alib_protos.h>
#include <stdexcept>

namespace AOS::AmigaLib
{
    MsgPortScope::MsgPortScope(bool exceptionOnError)
    {
        mpMsgPort = CreatePort(nullptr, 0);
        if (mpMsgPort == nullptr && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreatePort(nullptr, 0) failed!";
            throw std::runtime_error(error);
        }
    }

    MsgPortScope::~MsgPortScope()
    {
        if (mpMsgPort)
            DeletePort(mpMsgPort);
    }
}
