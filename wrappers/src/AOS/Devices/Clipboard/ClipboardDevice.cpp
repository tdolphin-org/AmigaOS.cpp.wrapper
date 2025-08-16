//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "ClipboardDevice.hpp"

#include <clib/exec_protos.h>
#include <exec/io.h>

namespace AOS::Devices
{
    ClipboardDeviceCore::ClipboardDeviceCore() { }

    bool ClipboardDeviceCore::Write(const void *pData, const unsigned long size) const
    {
        auto ioClip = mClipboardDeviceScope.ioClipReq();

        ioClip->io_Data = (STRPTR)pData;
        ioClip->io_Length = size;
        ioClip->io_Command = CMD_WRITE;
        DoIO((IORequest *)ioClip);

        if (ioClip->io_Actual == size)
            return ioClip->io_Error == 0;

        return false;
    }

    bool ClipboardDeviceCore::WriteLong(const LONG *pData) const
    {
        return Write(pData, 4);
    }

    bool ClipboardDeviceCore::WriteLong(const char pData[4]) const
    {
        return WriteLong((LONG *)pData);
    }

    bool ClipboardDeviceCore::Update() const
    {
        auto ioClip = mClipboardDeviceScope.ioClipReq();
        ioClip->io_Command = CMD_UPDATE;
        DoIO((IORequest *)ioClip);

        return ioClip->io_Error == 0;
    }

    void ClipboardDeviceCore::Copy(const std::string &content) const
    {
        // TODO handle errors

        if (content.empty())
            return;

        auto ioClip = mClipboardDeviceScope.ioClipReq();

        LONG slen = content.length();
        BOOL odd = (slen & 1); // pad byte flag

        LONG formDataLength = (odd) ? slen + 1 : slen; // set length depending on whether string is odd or even length

        // Reset the clip id
        ioClip->io_ClipID = 0;
        ioClip->io_Offset = 0;

        bool error = WriteLong("FORM");

        // add 12 bytes for FTXT,CHRS & length byte to string length */
        formDataLength += 12;
        error = WriteLong(&formDataLength);
        error = WriteLong("FTXT");
        error = WriteLong("CHRS");
        error = WriteLong(&slen); // length of string

        error = Write(content.c_str(), slen);

        if (odd)
            error = Write("", 1);

        error = Update();
    }
}
