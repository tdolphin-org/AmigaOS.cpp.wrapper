//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "ToString.hpp"

#include <datatypes/datatypes.h>

namespace AOS::DataTypes
{
    std::string ToString::FromGroup(const unsigned long groupID)
    {
        switch (groupID)
        {
            case GID_SYSTEM:
                return "System [syst] (System file, such as; directory, executable, library, device, font, etc.)";
            case GID_TEXT:
                return "Text [text] (Formatted or unformatted text)";
            case GID_DOCUMENT:
                return "Document [docu] (Formatted text with graphics or other DataTypes)";
            case GID_SOUND:
                return "Sound [soun]";
            case GID_INSTRUMENT:
                return "Instrument [inst] (Musical instruments used for musical scores)";
            case GID_MUSIC:
                return "Music [musi] (Musical score)";
            case GID_PICTURE:
                return "Picture [pict] (Still picture)";
            case GID_ANIMATION:
                return "Animation [anim] (Animated picture)";
            case GID_MOVIE:
                return "Movie [movi] (Animation with audio track)";

            default:
                return "undefined";
        }
    }
}
