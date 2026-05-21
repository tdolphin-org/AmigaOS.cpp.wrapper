#
#  AmigaOS C++ wrapper - amiga_std_light
#
#  (c) 2024-2026 TDolphin
#
#  generic makefile for gcc
#
#  for MorphOS (host) (ppc)
#
#  for Linux (host) x86_64 (64-bit)
#
#  1. AmigaOS m68k cross compilation setup from -> https://github.com/bebbo/amiga-gcc
#
#  2. MorphOS cross compilation setup from -> https://morph.zone/modules/newbb_plus/viewtopic.php?topic_id=13308&forum=12
#

# compiler/linker flags
# WARNING: use the same -Ox option for this lib and Your application, different values can cause linking errors
# -fno-rtti disables RTTI (Run-Time Type Information) support
CPP_FLAGS = $(MORE_CPP_FLAGS) -Isrc \
	-fno-rtti -ffunction-sections -fdata-sections -fvisibility=hidden -fvisibility-inlines-hidden -Os
AFLAGS = rcs

dir_guard = mkdir -p $(@D)

LIB_NAME = libamiga_std_light.a
LIBPATH = lib/$(SUB_BUILD_PATH)
OBJ_BASE = obj/$(SUB_BUILD_PATH)

SRC_DIR = src/amiga_std_light
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_BASE)/amiga_std_light/%.o,$(SRCS))

LIB = $(LIBPATH)/$(LIB_NAME)

all: $(LIB)

$(OBJ_BASE)/amiga_std_light/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(dir_guard)
	$(CPPC) $(CPP_FLAGS) -c $< -o $@

$(LIB): $(OBJS)
	$(dir_guard)
	$(AR) $(AFLAGS) $@ $^
