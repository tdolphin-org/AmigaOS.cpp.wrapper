#
#  MakeFile for "AmigaOS C++ wrapper" project
#
#  Tests
#
#  (c) 2024-2026 TDolphin
#

.PHONY: all build clean cross_amigaos_m68k morphos_ppc cross_morphos_ppc

all:
	@echo "make cross_amigaos_m68k - compile tests with AmigaOS m68k cross compiler"
	@echo "make morphos_ppc        - compile tests on MorphOS (PPC)"
	@echo "make cross_morphos_ppc  - compile tests with MorphOS PPC cross compiler"
	@echo "make clean              - remove test build artifacts"

CPP_FLAGS = $(MORE_CPP_FLAGS) -I../wrappers/src \
	-fno-rtti -ffunction-sections -fdata-sections -fvisibility=hidden -fvisibility-inlines-hidden -Os
LFLAGS = $(MORE_LFLAGS) -Wl,--gc-sections

OBJ_BASE = obj/$(SUB_BUILD_PATH)
BINPATH = out/$(SUB_BUILD_PATH)
APP_TEST = stream.tests.bin

MAIN_OBJ = $(OBJ_BASE)/tests/Main.o
IOSTREAM_OBJ = $(OBJ_BASE)/amiga_std_light/iostream.o
TEST_BIN = $(BINPATH)/$(APP_TEST)

cross_amigaos_m68k: TARGET="Cross AmigaOS m68k"
cross_amigaos_m68k: SUB_BUILD_PATH=amigaos/m68k
cross_amigaos_m68k: CPPC=m68k-amigaos-g++
cross_amigaos_m68k: MORE_CPP_FLAGS=
cross_amigaos_m68k: MORE_LFLAGS=
cross_amigaos_m68k: build

morphos_ppc: TARGET="MorphOS PPC"
morphos_ppc: SUB_BUILD_PATH=morphos/ppc
morphos_ppc: CPPC=g++
morphos_ppc: MORE_CPP_FLAGS=-noixemul -fno-threadsafe-statics -D_GLIBCXX_HAS_GTHREADS=0
morphos_ppc: MORE_LFLAGS=-noixemul
morphos_ppc: build

cross_morphos_ppc: TARGET="Cross MorphOS PPC"
cross_morphos_ppc: SUB_BUILD_PATH=morphos/ppc
cross_morphos_ppc: CPPC=ppc-morphos-g++
cross_morphos_ppc: MORE_CPP_FLAGS=-noixemul -fno-threadsafe-statics -D_GLIBCXX_HAS_GTHREADS=0
cross_morphos_ppc: MORE_LFLAGS=-noixemul
cross_morphos_ppc: build

build:
	@mkdir -p $(OBJ_BASE)/tests
	@mkdir -p $(OBJ_BASE)/amiga_std_light
	@mkdir -p $(BINPATH)
	$(CPPC) $(CPP_FLAGS) -c Main.cpp -o $(MAIN_OBJ)
	$(CPPC) $(CPP_FLAGS) -c ../wrappers/src/amiga_std_light/iostream.cpp -o $(IOSTREAM_OBJ)
	$(CPPC) $(MAIN_OBJ) $(IOSTREAM_OBJ) $(LFLAGS) -o $(TEST_BIN)
	@echo "# Tests linked OK for $(TARGET): $(TEST_BIN)"

clean:
	rm -rf obj
	rm -rf out