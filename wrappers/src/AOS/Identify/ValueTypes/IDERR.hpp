//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <libraries/identify.h>

namespace AOS::Identify
{
    // error codes for identify.library
    enum class ErrorID
    {
        OKAY = IDERR_OKAY, // No error
        NOLENGTH = IDERR_NOLENGTH, // Buffer length is 0 ??
        BADID = IDERR_BADID, // Missing or bad board ID
        NOMEM = IDERR_NOMEM, // Not enough memory
        NOFD = IDERR_NOFD, // No fitting FD file found
        OFFSET = IDERR_OFFSET, // Function offset not found
        DONE = IDERR_DONE, // Done with traversing (not an error)
        NOPCIDB = IDERR_NOPCIDB, // No PCI database file found [V45]
        BADPCIDB = IDERR_BADPCIDB, // Bad PCI database file [V45]
        NOPCILIB = IDERR_NOPCILIB, // No openpci.library or PCI bridge found [V45]
    };
}
