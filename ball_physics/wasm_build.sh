#!/bin/bash

emcc \
main.cpp \
-I ./raylib-5.0_webassembly/include \
-L ./raylib-5.0_webassembly/lib \
-lraylib \
-lm \
-s USE_GLFW=3 \
-s GL_ENABLE_GET_PROC_ADDRESS \
-s WASM=1 \
-s MODULARIZE=1 \
-s EXPORT_ES6=1 \
-o index.js \
-O3
# --embed-file ./assets \