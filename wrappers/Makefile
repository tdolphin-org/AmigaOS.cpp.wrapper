#
#  MakeFile for AmigaOS C++ wrapper - amiga_std_light static library
#
#  (c) 2024-2026 TDolphin
#

.PHONY: all build clean cross_amigaos_m68k morphos_ppc cross_morphos_ppc

all:
	@echo "make cross_amigaos_m68k - cross compilation on linux (AmigaOS m68k)"
	@echo "make morphos_ppc        - build on MorphOS (PPC)"
	@echo "make cross_morphos_ppc  - cross compilation on linux (MorphOS PPC)"
	@echo "make clean              - remove all .o and .lib files"

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
morphos_ppc: MORE_CPP_FLAGS="-noixemul"
morphos_ppc: build

cross_morphos_ppc: TARGET="Cross MorphOS PPC"
cross_morphos_ppc: SUB_BUILD_PATH=morphos/ppc
cross_morphos_ppc: CPPC=ppc-morphos-g++
cross_morphos_ppc: AR=ppc-morphos-ar
cross_morphos_ppc: MORE_CPP_FLAGS="-noixemul"
cross_morphos_ppc: build

build:
	@echo "# Build ... $(TARGET) ... $(SUB_BUILD_PATH)"
	$(MAKE) -f makefile.generic.gcc.mk \
	SUB_BUILD_PATH=$(SUB_BUILD_PATH) CPPC=$(CPPC) AR=$(AR) \
	MORE_CPP_FLAGS=$(MORE_CPP_FLAGS) \
	all

clean:
	rm -f -R obj/*
	rm -f -R lib/*
