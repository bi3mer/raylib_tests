# Ball Physics

I'm just trying to familiarize myself with [R]

## Set up for WASM

```bash
TBD
```

## Running Locally
### Compile

```bash
clang main.cpp -I include/  -lraylib -std=c++17
./a.out
```

curl -sL \
https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_webassembly.zip \
| bsdtar -x -C .