## What is this?

This is a tool used to run the [Adafruit GFX library](https://learn.adafruit.com/adafruit-gfx-graphics-library) locally via SDL2. It could be helpful with prototyping before deploying to physical hardware.

<img width="752" alt="image" src="https://github.com/twstokes/gfx-proto/assets/2092798/fd852f5d-a8d7-4000-a25d-c6acd17d6de8">

## Setup

- Fetch the dependency submodules with `git submodule update --init --recursive --depth=1`
- Install SDL2 (e.g. `brew install sdl2`)

## Building

`make`

## Running

`build/gfxproto` which should result in a SDL2 window with output.
