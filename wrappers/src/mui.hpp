//
//  AmigaOS C++ wrapper
//
//  (c) 2022-2026 TDolphin
//

#pragma once

#ifdef AOS_MUI38
#include <libraries/mui38.h>
#elif defined(AOS_MUI5)
#include <libraries/mui5.h>
#else // include standard MUI header by default; it may be MUI 3.8 or 5.0 depending on the system
#include <libraries/mui.h>
#endif