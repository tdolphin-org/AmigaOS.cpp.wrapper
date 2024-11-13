//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <datatypes/datatypes.h>

namespace AOS::DataTypes
{
    enum class GroupID
    {
        None = 0,
        System = GID_SYSTEM,
        Text = GID_TEXT,
        Document = GID_DOCUMENT,
        Sound = GID_SOUND,
        Instrument = GID_INSTRUMENT,
        Music = GID_MUSIC,
        Picture = GID_PICTURE,
        Animation = GID_ANIMATION,
        Movie = GID_MOVIE,
    };
}
