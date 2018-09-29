SuperMarioBros-C
================

An attempt to translate the original Super Mario Bros. for the NES to readable C/C++.

I've taken the `smbdis.asm` disassembly of Super Mario Bros. and successfully converted it to C++ using an automated codegen program I wrote (which you can be found in the `codegen/` subdirectory of the repo). Right now, it looks very similar to the original disassembly and is fairly dense code, but it works! Check out `source/SMB/SMB.cpp` if you're curious.

Many thanks to doppelganger (doppelheathen@gmail.com), who wrote the original comprehensive Super Mario Bros. disassembly. This can be found in the `docs/` folder of the repo.

![Demo gif](https://github.com/MitchellSternke/SuperMarioBros-C/raw/master/demo.gif)

*looks and plays just like the original*

Building
--------

**Dependencies**
- C++11 compiler
- Boost
- SDL2
- Flex
- Bison
- CMake

From the root of the repo, execute:
```
mkdir build
cd build
cmake ..
make
```

This should create the executable `smbc` in the `build` directory.

Running
-------

This requires an *unmodified* copy of the `Super Mario Bros. (JU) (PRG0) [!].nes` ROM to run. Without this, the game won't have any graphics, since the CHR data is used for rendering. By default, the program will look for this file in the current working directory, but this can also be configured in `smbc.conf`.

Configuration
-------------

Optionally, the program can be configured with a file named `smbc.conf` in the working directory. This file has an INI format. For example, the following would configure the option `audio.frequency` to be `22050`:

```
[audio]
frequency = 22050
```

The following is a list of all configurable options:

### [audio] options

#### enabled

- Allows audio to be enabled (if set to 1) or disabled (if set to 0).
- Default: 1

#### frequency

- Controls the frequency of sampled audio output, in Hz.
- Default: 48000

### [game] options

#### frame_rate

- The desired frame rate, in frames per second. Note that on some systems it may be necessary to disable vsync (see video.vsync) in order to achieve a frame rate higher than 60 fps.
- Default: 60

#### rom_file

- The path to the Super Mario Bros. ROM file. Can be either relative to the working directory or absolute.
- Default: "Super Mario Bros. (JU) (PRG0) [!].nes"

### [video] options

#### palette_file

- Relative or absolute path to a custom palette file to use for rendering. The following formats are supported:
  - 192-byte palette file: contains 64 (R,G,B) triples with one byte per color channel. Byte order must be (R,G,B). This is the standard *.pal file format used by many NES emulators. For more documentation see https://wiki.nesdev.com/w/index.php/.pal
  - 1536-byte palette file: similar to the 192-byte palette file format described above. Only the first 192 bytes are used, as the rest are used by emphasis bits which are not supported by Super Mario Bros.
- Default: ""

#### scale

- Controls the scale factor for rendered video.
- Default: 3

#### scanlines

- Allows rendering scanlines to be enabled (if set to 1) or disabled (if set to 0)
- Default: 1

#### vsync

- Allows vsync to be enabled (if set to 1) or disabled (if set to 0).
- Default: 1

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
