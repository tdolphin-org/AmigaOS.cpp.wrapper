#
#  MakeFile for AmigaOS C++ wrapper - amiga_std_light static library
#
#  (c) 2024-2026 TDolphin
#

.PHONY: all build clean cross_amigaos_m68k morphos_ppc cross_morphos_ppc cross_aros_x86_64

all:
	@echo "make cross_amigaos_m68k  - cross compilation on linux (AmigaOS m68k)"
	@echo "make morphos_ppc         - build on MorphOS (PPC)"
	@echo "make cross_morphos_ppc   - cross compilation on linux (MorphOS PPC)"
	@echo "make cross_aros_x86_64   - cross compilation on linux (AROS x86_64)"
	@echo "make clean               - remove all .o and .lib files"

cross_amigaos_m68k: TARGET="Cross AmigaOS m68k"
cross_amigaos_m68k: SUB_BUILD_PATH=amigaos/m68k
cross_amigaos_m68k: CPPC=m68k-amigaos-g++
cross_amigaos_m68k: AR=m68k-amigaos-ar
cross_amigaos_m68k: MORE_CPP_FLAGS=
cross_amigaos_m68k: build

morphos_ppc: TARGET="MorphOS PPC"
morphos_ppc: SUB_BUILD_PATH=morphos/ppc
morphos_ppc: CPPC=g++
morphos_ppc: AR=ar
morphos_ppc: MORE_CPP_FLAGS="-noixemul -flto"
morphos_ppc: build

cross_morphos_ppc: TARGET="Cross MorphOS PPC"
cross_morphos_ppc: SUB_BUILD_PATH=morphos/ppc
cross_morphos_ppc: CPPC=ppc-morphos-g++
cross_morphos_ppc: AR=ppc-morphos-ar
cross_morphos_ppc: MORE_CPP_FLAGS="-noixemul -flto"
cross_morphos_ppc: build

# AROS x86_64 - conventional location for the cross SDK. This points at the generated
# AROS "Development" tree (sysroot with Zune headers/libs). Like the other targets
# (m68k via /opt/amiga, MorphOS via the compiler's own sysroot) this is a machine-
# independent path: on machines that follow the convention it is /opt/aros/Development.
# Override per-build with:  make cross_aros_x86_64 AROS_SYSROOT=/custom/path
AROS_SYSROOT ?= /opt/aros/Development

cross_aros_x86_64: TARGET="Cross AROS x86_64"
cross_aros_x86_64: SUB_BUILD_PATH=aros/x86_64
cross_aros_x86_64: CPPC=x86_64-aros-g++
cross_aros_x86_64: AR=x86_64-aros-ar
cross_aros_x86_64: MORE_CPP_FLAGS="-std=gnu++17 --sysroot=$(AROS_SYSROOT)"
cross_aros_x86_64: build

build:
	@echo "# Build ... $(TARGET) ... $(SUB_BUILD_PATH)"
	$(MAKE) -f makefile.generic.gcc.mk \
	SUB_BUILD_PATH=$(SUB_BUILD_PATH) CPPC=$(CPPC) AR=$(AR) \
	MORE_CPP_FLAGS=$(MORE_CPP_FLAGS) \
	all

clean:
	rm -f -R obj/*
	rm -f -R lib/*
