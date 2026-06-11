//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "Library.hpp"

#include <proto/asl.h>

#ifdef TRACE_AMIGAOS
#include "amiga_std_light/iostream.hpp"
#endif

extern struct Library *ASLBase;

namespace AOS::ASL
{
    FileRequester *AOS::ASL::Library::libAllocFileRequest()
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "()" << std::endl;
#endif
        return AllocFileRequest();
    }

    void Library::libFreeFileRequest(FileRequester *fileReq)
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "()" << std::endl;
#endif
        FreeFileRequest(fileReq);
    }

    bool Library::libRequestFile(FileRequester *fileReq)
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "()" << std::endl;
#endif
        return RequestFile(fileReq);
    }
}
