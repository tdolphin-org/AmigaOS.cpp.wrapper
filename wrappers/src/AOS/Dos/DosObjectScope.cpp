//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "DosObjectScope.hpp"

#include <proto/dos.h>
#include <stdexcept>

namespace AOS::Dos
{
    DosObjectScope::DosObjectScope(unsigned long type)
      : mType(type)
    {
        mpDosObject = AllocDosObjectTags(type, TAG_DONE);
        if (!mpDosObject)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " AllocDosObjectTags(" + std::to_string(type) + ") failed!";
            throw std::runtime_error(error);
        }
    }

    DosObjectScope::~DosObjectScope()
    {
        if (mpDosObject)
            FreeDosObject(mType, mpDosObject);
    }

    FileInfoBlock *DosObjectScope::fileInfoBlock() const
    {
        if (mType != DOS_FIB)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " wrong allocated type (" + std::to_string(mType) + ")!";
            throw std::runtime_error(error);
        }

        return (FileInfoBlock *)mpDosObject;
    }

    ExAllControl *DosObjectScope::exAllControl() const
    {
        if (mType != DOS_EXALLCONTROL)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " wrong allocated type (" + std::to_string(mType) + ")!";
            throw std::runtime_error(error);
        }

        return (ExAllControl *)mpDosObject;
    }
}