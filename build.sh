#/bin/bash

CC="clang++"
OUTPUT="emulator"
TEMP="pkg-config --cflags --lib re2 fmt"
FLAGS="-std=c++20 -g -Wall -Wextra  -pedantic -fsanitize=undefined -Wodr -o $OUTPUT"
SOURCES="main.cpp"

usage() {
  echo "Usage: $0 -r RELEASE"
  echo "  release: either 'debug' or 'release'"
  exit 1
}

while getopts "r:" opt; do
  case ${opt} in
    r )
      RELEASE=$OPTARG
      ;;
    \? )
      usage
      ;;
  esac
done

if [ -z "$RELEASE" ] ; then
  RELEASE="release"
fi

if [[ "$RELEASE" != "debug" && "$RELEASE" != "release" ]]; then
  echo "Invalid RELEASE value"
  usage
fi

cp compile_commands.json compile_commands.json.backup

if [[ "$RELEASE" == "debug" ]]; then
  echo "========== COMPILING DEBUG ============"
  bear -- $CC $FLAGS $SOURCES
else
  echo "========== COMPILING RELEASE ============"
  bear -- $CC $FLAGS $SOURCES -O2
fi

if [[ -f "compile_commands.json" && $(stat -c%s "compile_commands.json") -gt 4 ]]; then
  rm compile_commands.json.backup
else
  mv compile_commands.json.backup compile_commands.json
fi

echo "========== DONE =========="
