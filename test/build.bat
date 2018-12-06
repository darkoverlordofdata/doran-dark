REM
REM Emscripten build 
REM
emcc ^
    -w ^
    -O2 ^
    -std=c99 ^
    -o docs/index.html ^
    -s WASM=1 ^
    -D__EMSCRIPTEN__ ^
    -I./.lib/dark/include ^
    -I./.lib/dark/vendor/tgc ^
    .lib/dark/vendor/tgc/tgc.c ^
    .lib/dark/src/gc.c ^
    .lib/dark/src/string.c ^
    .lib/dark/src/Class.c ^
    .lib/dark/src/Object.c ^
    .lib/dark/src/Comparable.c ^
    .lib/dark/src/collections/Collection.c ^
    .lib/dark/src/collections/Array.c ^
    .lib/dark/src/collections/Hashmap.c ^
    .lib/dark/src/collections/List.c ^
    .lib/dark/src/io/FileSystem.c ^
    .lib/dark/src/io/File.c ^
    .lib/dark/src/types/Boolean.c ^
    .lib/dark/src/types/Number.c ^
    .lib/dark/src/types/Char.c ^
    .lib/dark/src/types/Double.c ^
    .lib/dark/src/types/Float.c ^
    .lib/dark/src/types/Integer.c ^
    .lib/dark/src/types/Long.c ^
    .lib/dark/src/types/Short.c ^
    .lib/dark/src/types/String.c ^
    .lib/dark/src/types/StringBuilder.c ^
    src/darkunit.c ^
    src/main.c
