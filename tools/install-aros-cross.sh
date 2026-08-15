#!/bin/sh
#
# install-aros-cross.sh -- install AROS/Zune cross toolchain under a standard /
# conventional path ( /opt/aros ) so that builds are machine-independent, in the
# same spirit as the AmigaOS m68k (/opt/amiga) and the MorphOS toolchains.
#
# AROS does not ship with a fixed install location: each user builds it wherever
# the AROS "rebuild.sh" archive is unpacked (e.g. ~/Aros/arosbuilds). That
# directory is full of user-specific absolute paths, which is awkward.
#
# This script maps a real AROS build tree onto the conventional /opt/aros
# layout using symlinks plus freshly generated "wrapper" compiler scripts that
# bake the sysroot, so you never have to pass --sysroot or reference /home/...
# yourself.
#
#   /opt/aros/toolchain/    -> <arosroot>/toolchain-core-<cpu>      (cross gcc)
#   /opt/aros/Development/  -> <arosroot>/.../AROS/Development       (sysroot)
#   /opt/aros/bin/          -> fresh wrapper scripts (x86_64-aros-g++ & co)
#                             that call the toolchain with
#                             --sysroot=/opt/aros/Development
#
# After installing add /opt/aros/bin to PATH. The wrapper builds in
# AmigaOS.cpp.wrapper/wrappers then pick up AROS_SYSROOT=/opt/aros/Development
# by default -- no per-user paths anywhere.
#
# Requires root to write into /opt (use sudo).
# Usage:
#   sudo install-ar-OS-cross.sh /home/you/Aros/arosbuilds [--dry-run]
#
# Exit codes: 0 = success, 1 = missing/bad args, 2 = source tree not found.

set -u

RUN=1
ARGBUILD=""
for a in "$@"; do
    case "$a" in
        --dry-run) RUN=0 ;;
        -h|--help) sed -n '2,40p' "$0"; exit 0 ;;
        *) ARGBUILD="$a" ;;
    esac
done

if [ -z "$ARGBUILD" ]; then
    echo "error: pass the path to your arosbuilds (the directory that holds" >&2
    echo "       'rebuild.sh' and {  toolchain-*, core-*-d } subdirs )." >&2
    exit 1
fi
ARGBUILD="$(cd "$ARGBUILD" 2>/dev/null && pwd)"
if [ -z "$ARGBUILD" ] || [ ! -d "$ARGBUILD" ]; then
    echo "error: '$ARGBUILD' is not a directory" >&2
    exit 2
fi

# ---- locate real toolchain + Development (sysroot) --------------------------
TC=""; DEV=""
# 1) a dedicated toolchain dir: toolchain-core-<triple> / toolchain-<triple>
for d in "$ARGBUILD"/toolchain-*; do
    [ -d "$d" ] && TC="$d"
done
# 2) fall back to a cross wrapper scene (x86_64-aros-gcc present)
[ -z "$TC" ] && for d in "$ARGBUILD"/core-*-*/bin/*-*/*; do
    [ -x "$d/x86_64-aros-gcc" ] && TC="$d"
done

# development dir: found under core-*/bin/<host>/AROS/Development
for d in "$ARGBUILD"/core-*/bin/*-*/AROS/Development; do
    [ -d "$d" ] && DEV="$d"
done

if [ -z "$TC" ]; then
    echo "error: could not locate the AROS cross toolchain under '$ARGBUILD'" >&2
    exit 2
fi
if [ -z "$DEV" ]; then
    echo "error: could not locate the AROS Development (sysroot) dir under '$ARGBUILD'" >&2
    exit 2
fi
echo "found toolchain: $TC"
echo "found Development: $DEV"
echo

DEST=/opt/aros
BIN="$DEST/bin"
if [ "$RUN" = "0" ]; then
    echo "[dry-run] would install to $DEST"
fi

step() {
    echo "[install] $1"
    [ "$RUN" = "1" ] || echo "  (skipped - dry-run)"
}

mk() {
    step "mkdir -p $1"
    [ "$RUN" = "1" ] && mkdir -p "$1" || true
}

lnk() { # src dst
    step "ln -s '$1' '$2'"
    [ "$RUN" = "1" ] && ln -sfn "$1" "$2" || true
}

# ---- 1. symlink the toolchain + sysroot -------------------------------------
mk "$DEST"
lnk "$TC" "$DEST/toolchain"
lnk "$DEV" "$DEST/Development"

# ---- 2. wrapper scripts with a baked --sysroot -------------------------------
# Only gcc/g++ understand --sysroot. The binutils (ar, nm, ranlib, strip,
# objdump) do NOT -- baking --sysroot into them makes every invocation fail
# with "unrecognized option", so they get plain wrappers without --sysroot.
mk "$BIN"
for t in gcc g++; do
    src="$TC/x86_64-aros-$t"
    [ -x "$src" ] || continue
    wr="$BIN/x86_64-aros-$t"
    if [ "$RUN" = "0" ]; then
        step "write wrapper $wr -> x86_64-aros-$t"
        continue
    fi
    {
        echo "#!/bin/sh"
        echo "exec \"$DEST/toolchain/x86_64-aros-$t\" --sysroot=\"$DEST/Development\" \"\$@\""
    } > "$wr"
    chmod +x "$wr"
    echo "[install] wrote $wr"
done
for t in ar nm ranlib strip objdump; do
    src="$TC/x86_64-aros-$t"
    [ -x "$src" ] || continue
    wr="$BIN/x86_64-aros-$t"
    if [ "$RUN" = "0" ]; then
        step "write wrapper $wr -> x86_64-aros-$t"
        continue
    fi
    {
        echo "#!/bin/sh"
        echo "exec \"$DEST/toolchain/x86_64-aros-$t\" \"\$@\""
    } > "$wr"
    chmod +x "$wr"
    echo "[install] wrote $wr"
done

echo
cat <<EOF
Done.

To use it, add to your shell profile (e.g. ~/.bashrc):

    export PATH=/opt/aros/bin:\$PATH
    export AROS_SYSROOT=/opt/aros/Development

Then build:

    make cross_aros_x86_64            # uses AROS_SYSROOT default = /opt/aros/Development

The wrappers under /opt/aros/bin bake --sysroot, so plain calls like
'x86_64-aros-g++' using any gcc --version' also work without extra flags.
EOF