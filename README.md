# Raylib Tests

This repo has a bunch of tests and experiments with [raylib](https://www.raylib.com/). The purpose is to make small games and simulations that are either interesting to me, fun, or help me learning something new about the library. Each directory in this repo is one of those experiments.

## WASM Builds

- Simulations
    - Frictionless bouncing ball
    - Conway's Game of Life
    - Hilbert Curves

- Games
    - Pong

### Simulations

- N-body
- Mouse press to add ball that bounces with collisions
- [Procedurally animated fish](https://www.youtube.com/watch?v=qlfh_rv6khY)
- Boids (use the fish from above)
- Falling sand
- Hilbert Curves
- Ant Colony

### Games

- Pong
- Snake
- Tic-Tac-Toe
- Pac-man
- Asteroids
- Frogger
- Doodle jump
- Brick Breaker
- Sokobon
- Micro Tower Defense

## Running the Code

I've tested this with only c++17. It may work on earlier versions or later versions, but I haven't tested so I can't guarantee anything. Once you have c++ running, you need [raylib]([raylib](https://www.raylib.com/)) installed. If you want to build for your browser, you need [emscripten](https://emscripten.org/docs/getting_started/downloads.html) to make a [wasm build](https://webassembly.org/). 

With installation out of the way, start by cd'ing into whatever project you are interested in. 

### Run Locally

The [makefile](./makefile) uses clang. If you are not on mac or do not have clang, you'll need to change the makefile to use your c++ compiler instead of clang. Then you can run the command below and the simulation will be compiled and then you can watch it run until you get bored.

```bash
make run
```

### Run on the Browser

I have a release build of raylib in a dependency directory at `../`. You can download it with the command below. If you choose to have the raylib folder in this directory, then you'll need to update the makefile for whatever project you are in paths for the wasm command.

```bash
curl -sL \
    https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_webassembly.zip \
    | bsdtar -x -C ../dependencies/.
```

Then you can build with [emscripten](https://emscripten.org/).

```bash
make wasm
```

To see it run locally on your browser, you need a web server running. I use python, but you can use whatever you want.

```bash
python -m http.server 8000
```

Now open your browser and set the url to `127.0.0.1:8000`, and enjoy.