SuperMarioBros-C
================

An attempt to manually translate the original Super Mario Bros. for the NES to readable C/C++.

I've taken the `smbdis.asm` disassembly of Super Mario Bros. and successfully converted it to C++ using an automated codegen program I wrote (which you can be found in the `Decompiler/` subdirectory of the repo). Right now, it looks very similar to the original disassembly and is fairly dense code, but it works! Check out `Decompiled.cpp` in the root of the repo if you're curious.

Building
--------

**Dependencies**
- C++11 compiler
- Boost
- SDL2

A Code::Blocks project file has been provided for convenience, and it is what is currently used for development. However, this should build on any platform that has a C++11 compiler with SDL2 support.

Running
-------

This requires an *unmodified* copy of the `Super Mario Bros. (JU) (PRG0) [!].nes` ROM in the working directory to run. Without this, the game won't have any graphics, since the CHR data is used for rendering.

Architecture
------------

The game consists of a few parts:
- The decompiled original Super Mario Bros. source code in C++
- An emulation layer, consisting of
  - Core NES CPU functionality (RAM, CPU registers, call stack, and emulation of unique 6502 instructions that don't have C++ equivalents)
  - Picture Processing Unit (PPU) emulation (for video)
  - Audio Processing Unit (APU) emulation (for sound/music)
  - Controller emulation
- SDL2 library for cross-platform video/audio/input

Essentially, the game is a statically recompiled version of Super Mario Bros. for modern platforms. The only part of the NES that doesn't have to be emulated is the CPU, since most instructions are now native C++ code.

The plan is to eventually ditch all of the emulation layer and convert code that relies upon it. Once that's done, this will be a true cross-platform version of Super Mario Bros. which behaves identically to the original. It could then be easily modified and extended with new features!

License
-------

TODO
