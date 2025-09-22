//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <rexx/storage.h>

namespace AOS::Rexxsyslib
{
    // message-packet commands
    enum class RX : unsigned long
    {
        COMM = RXCOMM,
        FUNC = RXFUNC,
        CLOSE = RXCLOSE,
        QUERY = RXQUERY,
        ADDFH = RXADDFH,
        ADDLIB = RXADDLIB,
        REMLIB = RXREMLIB,
        ADDCON = RXADDCON,
        REMCON = RXREMCON,
        TCOPN = RXTCOPN,
        TCCLS = RXTCCLS,
    };
}