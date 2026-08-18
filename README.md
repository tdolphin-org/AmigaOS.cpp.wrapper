# AmigaOS.cpp.wrapper

AmigaOS/MorphOS/AROS OS Related (Libraries, Devices, etc.) C++ Wrapper Classes is a C++17-based set of wrappers designed to simplify interaction with various core and external components of AmigaOS, MorphOS, and AROS. This collection of classes provides object-oriented interfaces for OS elements such as devices, system libraries, and other essential resources. By encapsulating these components in modern C++ abstractions, the wrappers improve code clarity, maintainability, and type safety, allowing developers to work more seamlessly with OS-level functionalities while leveraging the expressive power of C++.

___
## What this project builds

This project builds **exactly one artifact**: the `libamiga_std_light.a` static
library (`wrappers/src/amiga_std_light/*.cpp`).

The other sources of this repo (`wrappers/src/AOS/`, `wrappers/src/Core/`,
`wrappers/src/std/`, `mui.hpp`) are **not** compiled here. Downstream projects
compile them from their own Makefiles, pulling the sources in by path. For
example `AmigaOS.MUI.cpp.wrapper` compiles the sibling `AOS` and `Core` modules
directly:

```makefile
AOSCPP_PATH = ../../AmigaOS.cpp.wrapper
AOS_WRAPPER_MODULES = Core AOS
# then $(wildcard …/src/<module>/*.cpp) compiled with the project's own CPPC/AR
```

So this repo's `wrappers/Makefile` only needs the two tools that build
`amiga_std_light` (`$(CPPC)` and `$(AR)`); all other requirements are owned by
the consuming project.

___
## Requirements for build

### MorphOS compilation (native, on MorphOS)
- MorphOS SDK 3.18+ (native `g++`/`ar`)
- Build: `make morphos_ppc`

### Linux cross compilation for AmigaOS
- [bebbo/amiga-gcc](https://codeberg.org/bebbo/amiga-gcc) toolchain
  (`m68k-amigaos-g++` / `m68k-amigaos-ar`)
- Build: `make cross_amigaos_m68k`

### Linux cross compilation for MorphOS

- MorphOS cross SDK setup (see
  [Morph zone thread](https://morph.zone/modules/newbb_plus/viewtopic.php?topic_id=13308&forum=12)),
  providing `ppc-morphos-g++` / `ppc-morphos-ar`
- Build: `make cross_morphos_ppc`

### Linux cross compilation for AROS

Build the AROS cross-compiler + hosted AROS first (stable **ABIv11** tree, not bleeding edge):

- [AROS stable sources](https://github.com/deadwood2/AROS) + `scripts/rebuild.sh` - see [AROS Getting Started](https://elwis.github.io/aros-getting-started/docs/01-build-environment.html)
- System dependencies: `sudo apt install gcc g++ make git flex bison gawk python3 python3-mako libx11-dev libpng-dev genisoimage cmake curl nasm autoconf automake libxext-dev liblzo2-dev libxxf86vm-dev libsdl1.2-dev byacc yasm xorriso mtools`

AROS does **not** ship with a fixed install location and `x86_64-aros-g++` has no
built-in `--sysroot` (otherwise it picks up host Linux headers). To make the
environment machine-independent, map your existing AROS build onto the
conventional `/opt/aros` layout (symlinks + `--sysroot`-baking compiler wrappers),
in the same spirit as `/opt/amiga` (m68k) and the MorphOS SDK:

```sh
sudo /bin/sh tools/install-aros-cross.sh /path/to/your/arosbuilds
echo 'export PATH=/opt/aros/bin:$PATH' >> ~/.bashrc && source ~/.bashrc
```

Run this **once** (not before every `make`) - re-run only if the AROS build tree
moves. `AROS_SYSROOT` in `wrappers/Makefile` defaults to `/opt/aros/Development`
and can be overridden per-build:

```sh
make cross_aros_x86_64                            # AROS_SYSROOT=/opt/aros/Development
make cross_aros_x86_64 AROS_SYSROOT=/custom/path
```