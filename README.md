<div align="center">

# Super Mario Bros. — C++

**The original NES *Super Mario Bros.*, translated from 6502 assembly into portable C++17.**

[![CI](https://github.com/anas1996/SuperMarioBros-C/actions/workflows/ci.yml/badge.svg)](https://github.com/anas1996/SuperMarioBros-C/actions/workflows/ci.yml)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![SDL2](https://img.shields.io/badge/SDL-2-blue)

![Demo](demo.gif)

*Looks and plays just like the original.*

</div>

## About

This is a static recompilation of *Super Mario Bros.* The `smbdis.asm` disassembly of the game
is converted to C++ by a code generator (in [`codegen/`](codegen)), so the game logic runs as
native code: the NES CPU is not emulated at all. Only the hardware the game talks to (the picture
and audio processors, and the controllers) is emulated.

The translated code mirrors the disassembly line for line, comments included. For example:

```cpp
WBootCheck: // check each score digit in the top score
    a = M(TopScoreDisplay + x);
    compare(a, 10); // to see if we have a valid digit
    if (c)
        goto ColdBoot; // if not, give up and proceed with cold boot
    --x;
    if (!n)
        goto WBootCheck;
```

Take a look at [`source/SMB/SMB.cpp`](source/SMB/SMB.cpp) if you're curious.

### Features

- **Faithful** — game behavior is verified frame by frame by a regression test.
- **Crisp at any size** — resizable window and fullscreen. Pixels stay uniform at every scale
  ("sharp bilinear" scaling), with optional integer-only scaling.
- **CRT effect** — scanlines and phosphor stripes, rendered at your screen's native resolution.
- **Authentic sound** — the NES's nonlinear mixer and analog output filters, in 16-bit audio.
- **Gamepads** — plug-and-play support for one or two controllers.
- **Quality of life** — pause screen, automatic pause in the background, mute, and volume control.

## Getting started

### Requirements

- A C++17 compiler (GCC, Clang or MSVC)
- [CMake](https://cmake.org) 3.16 or newer
- [SDL2](https://libsdl.org)
- *Optional:* Bison 3+ and Flex, only needed to regenerate the translated code

| Platform      | Install the dependencies                                                      |
| ------------- | ----------------------------------------------------------------------------- |
| Debian/Ubuntu | `sudo apt install build-essential cmake libsdl2-dev`                          |
| Fedora        | `sudo dnf install gcc-c++ cmake SDL2-devel`                                   |
| Arch          | `sudo pacman -S base-devel cmake sdl2`                                        |
| macOS         | `brew install cmake sdl2`                                                     |
| Windows       | [vcpkg](https://vcpkg.io) installs SDL2 from `vcpkg.json` (see below)          |

### Building

```sh
cmake -B build
cmake --build build --parallel
```

On Windows, pass vcpkg's toolchain file and build the Release configuration:

```sh
cmake -B build -DCMAKE_TOOLCHAIN_FILE=<vcpkg root>/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
```

This produces the `smbc` executable in `build/` (`build/Release/` on Windows).

### Running

The game needs an *unmodified* copy of the `Super Mario Bros. (JU) (PRG0) [!].nes` ROM image,
whose graphics data it uses. Pass its path on the command line:

```sh
./build/smbc "path/to/Super Mario Bros. (JU) (PRG0) [!].nes"
```

Without an argument, the ROM image is loaded from the path set in the [configuration](#configuration)
(by default `Super Mario Bros. (JU) (PRG0) [!].nes` in the working directory).

## Controls

| NES controller | Keyboard   | Gamepad                     |
| -------------- | ---------- | --------------------------- |
| D-pad          | Arrow keys | D-pad or left stick         |
| A (jump)       | X          | B or Y (right/top button)   |
| B (run, fire)  | Z          | A or X (bottom/left button) |
| Start          | Enter      | Start                       |
| Select         | Backspace  | Back                        |

The first gamepad controls player 1 (along with the keyboard); a second gamepad controls player 2.

| Hotkey              | Action                                  |
| ------------------- | --------------------------------------- |
| P or Pause          | Pause / resume                          |
| F11, Alt+Enter or F | Toggle fullscreen                       |
| F2                  | Toggle the CRT effect                   |
| M                   | Mute / unmute                           |
| R                   | Reset (like the console's reset button) |
| Esc                 | Quit                                    |

## Configuration

Settings are read from `smbc.conf` in the working directory, an INI file. Every setting is
optional. For example:

```ini
[audio]
volume = 80

[game]
rom_file = roms/smb.nes

[video]
scale = 4
scanlines = 0
```

| Setting                 | Default                                 | Description |
| ----------------------- | --------------------------------------- | ----------- |
| `audio.enabled`         | `1`                                     | Enable sound. |
| `audio.frequency`       | `48000`                                 | Sample rate in Hz. |
| `audio.volume`          | `100`                                   | Volume, from 0 to 100. |
| `game.frame_rate`       | `60`                                    | Frames per second. Higher values speed the game up; with vsync enabled, the display's refresh rate may limit it. |
| `game.rom_file`         | `Super Mario Bros. (JU) (PRG0) [!].nes` | Path to the ROM image, relative to the working directory or absolute. |
| `video.fullscreen`      | `0`                                     | Start in fullscreen. |
| `video.integer_scaling` | `0`                                     | Only enlarge the picture by whole numbers, for perfectly square pixels. |
| `video.palette_file`    | *(none)*                                | A custom [`.pal` palette file](https://www.nesdev.org/wiki/.pal): 64 RGB triples (192 bytes). 1536-byte files are accepted too; their emphasis variants are ignored, since the game doesn't use them. |
| `video.scale`           | `3`                                     | Initial window size, as a multiple of 256×240. |
| `video.scanlines`       | `1`                                     | Enable the CRT effect. |
| `video.vsync`           | `1`                                     | Synchronize with the display's refresh rate. |

Booleans accept `1`/`0`, `true`/`false`, `yes`/`no` or `on`/`off`.

## How it works

```
docs/smbdis.asm ──► codegen ──► source/SMB/SMB.cpp, SMBData.cpp   (the game, as C++)
 (disassembly)     (Flex/Bison)              │ run by
                                             ▼
                                         SMBEngine ──► Emulation: PPU (video), APU (audio), controllers
                                             │
                                             ▼
                                   Frontend (SDL2): window, CRT effect, audio output, input
```

| Directory          | Contents |
| ------------------ | -------- |
| `codegen/`         | The translator: a Flex/Bison 6502 assembly parser and a C++ code generator. |
| `docs/`            | `smbdis.asm`, the disassembly the game is generated from. |
| `source/SMB/`      | The generated game code and data, plus `SMBEngine`, which runs it. |
| `source/Emulation/`| Emulation of the NES hardware the game relies on: the picture processing unit (PPU), audio processing unit (APU) and controllers. |
| `source/Frontend/` | The SDL2 frontend: display, audio output and input. |
| `tests/`           | Regression tests. |

Each 6502 instruction becomes a line of C++. Registers and memory are wrapped in a
`MemoryAccess` type whose operators update the processor's carry, zero and negative flags, so
branches translate directly into `if (...) goto`. Subroutine calls push a return index and jump
to a label; `RTS` dispatches through a generated table of return points.

The long-term goal is to replace the remaining emulation with plain C++ and refactor the
translated code, making the game easy to modify and extend.

## Development

```sh
ctest --test-dir build --output-on-failure
```

The tests need no ROM image. `regression` plays a scripted game and compares hashes of the RAM,
rendered frames and audio against known-good values, so any change in the game's behavior is
caught. Run `build/smbc_regression --print` to output new values after an intentional change.
`generated_sources_up_to_date` checks that `source/SMB` matches the code generator's output.

To regenerate `source/SMB` after changing the code generator (requires Bison 3+ and Flex):

```sh
cmake --build build --target regenerate
```

## Credits

- The original [SuperMarioBros-C](https://github.com/MitchellSternke/SuperMarioBros-C) project
  by Mitchell Sternke, including the code generator.
- doppelganger (doppelheathen@gmail.com), who wrote the comprehensive Super Mario Bros.
  disassembly in [`docs/smbdis.asm`](docs/smbdis.asm).
- The [NESdev Wiki](https://www.nesdev.org/wiki/), for documentation of the NES hardware.

## License

TODO
