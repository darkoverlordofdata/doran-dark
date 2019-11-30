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
    -I./vendor/tlm ^
    -I./include ^
    src/main.c
