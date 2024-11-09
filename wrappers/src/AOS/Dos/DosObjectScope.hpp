//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <dos/dos.h>
#include <dos/exall.h>
#include <string>

namespace AOS::Dos
{
    class DosObjectScope
    {
        unsigned long mType;
        void *mpDosObject;

      public:
        DosObjectScope(unsigned long type);
        ~DosObjectScope();

        struct FileInfoBlock *fileInfoBlock() const;
        struct ExAllControl *exAllControl() const;
    };
}
