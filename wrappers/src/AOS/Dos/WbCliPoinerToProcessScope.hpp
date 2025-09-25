//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

struct Process;

namespace AOS::Dos
{
    class WbCliPoinerToProcessScope
    {
        struct Process *mpProcess;

      public:
        WbCliPoinerToProcessScope();
        ~WbCliPoinerToProcessScope();
    };
}
