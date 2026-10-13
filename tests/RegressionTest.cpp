/**
 * @file
 * @brief Deterministic regression test for the game engine.
 *
 * Plays a scripted game (title screen, running, jumping, dying, pausing and a console reset)
 * and compares hashes of the RAM, the rendered frames and the audio output against known-good
 * values. Any change to the game's behavior shows up as a mismatch.
 *
 * No ROM is needed: only the graphics (CHR) data comes from the ROM, and the game logic never
 * reads it, so pseudo-random CHR data is used to exercise rendering.
 *
 * Run with --print to output the current hashes, e.g. after an intentional change.
 */
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <vector>

#include "Constants.hpp"
#include "SMB/SMBEngine.hpp"

namespace
{

constexpr int FRAME_COUNT = 8000;
constexpr int CHECKPOINT_INTERVAL = 1000;
constexpr int RESET_FRAME = 4500;
constexpr int SAMPLE_RATE = 48000;
constexpr int FRAME_RATE = 60;

struct Checkpoint
{
    int frame;
    uint64_t state; /**< Hash of RAM and rendered frames up to this frame. */
    uint64_t audio; /**< Hash of the audio samples up to this frame. */
};

const Checkpoint EXPECTED[] = {
    {1000, 0xaaedbae4df228f13, 0x7812053e5e105189},
    {2000, 0x2c8cac0d4aae0690, 0x8fe37b1ca44879d5},
    {3000, 0xebefd92c5a1b0357, 0xcc568d5935f1193f},
    {4000, 0xc13673a0241c456b, 0x31cb5580c9effae3},
    {5000, 0x4a5670925bc38dfc, 0x4d944a2940e76414},
    {6000, 0x2775da54699e28c1, 0xa0a61ab1f9e5c4db},
    {7000, 0x051de7e7c8efa211, 0xeea2929c895deed9},
    {8000, 0xb4f85a940a5f555b, 0xf2abc23e9b3c83b8},
};

/**
 * Incremental 64-bit FNV-1a hash.
 */
class Hash
{
public:
    void add(const void* data, std::size_t size)
    {
        const auto* bytes = static_cast<const uint8_t*>(data);
        for (std::size_t i = 0; i < size; i++)
        {
            value = (value ^ bytes[i]) * 0x100000001b3ull;
        }
    }

    uint64_t get() const
    {
        return value;
    }

private:
    uint64_t value = 0xcbf29ce484222325ull;
};

/**
 * Controller input for a frame: start a game, then play pseudo-randomly while
 * mostly running to the right, pressing Start every so often (pausing, or
 * starting a new game after a game over).
 */
uint8_t scriptedButtons(int frame)
{
    const auto bit = [](Button button) { return static_cast<uint8_t>(1 << static_cast<int>(button)); };

    if (frame < 120)
    {
        return 0;
    }
    if (frame < 126 || frame % 400 < 3)
    {
        return bit(Button::Start);
    }

    uint32_t h = static_cast<uint32_t>(frame / 12) * 2654435761u;
    h ^= h >> 15;
    h *= 0x2c1b3c6du;
    h ^= h >> 12;

    uint8_t buttons = 0;
    if ((h & 7) < 6)
    {
        buttons |= bit(Button::Right);
    }
    else if ((h & 7) == 6)
    {
        buttons |= bit(Button::Left);
    }
    if (h & 0x10)
    {
        buttons |= bit(Button::B);
    }
    if ((h & 0x60) == 0x60)
    {
        buttons |= bit(Button::A);
    }
    if ((h & 0x380) == 0x380)
    {
        buttons |= bit(Button::Down);
    }
    if ((h & 0x1c00) == 0x1c00)
    {
        buttons |= bit(Button::Up);
    }
    return buttons;
}

std::vector<uint8_t> makeChr()
{
    std::vector<uint8_t> chr(SMBEngine::CHR_SIZE);
    uint32_t state = 0x12345678u;
    for (uint8_t& byte : chr)
    {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        byte = static_cast<uint8_t>(state >> 24);
    }
    return chr;
}

} // namespace

int main(int argc, char** argv)
{
    const bool print = argc > 1 && std::strcmp(argv[1], "--print") == 0;

    const std::vector<uint8_t> chr = makeChr();
    SMBEngine engine(chr.data(), SAMPLE_RATE, FRAME_RATE);
    engine.reset();

    std::vector<uint32_t> frameBuffer(RENDER_WIDTH * RENDER_HEIGHT);
    Hash state;
    Hash audio;
    int failures = 0;
    const Checkpoint* expected = EXPECTED;

    for (int frame = 1; frame <= FRAME_COUNT; frame++)
    {
        const uint8_t buttons = scriptedButtons(frame - 1);
        for (int button = 0; button < 8; button++)
        {
            engine.getController(0).setButtonState(static_cast<Button>(button), (buttons >> button) & 1);
        }
        if (frame - 1 == RESET_FRAME)
        {
            engine.reset();
        }

        engine.update();
        engine.render(frameBuffer.data());

        const auto& ram = engine.getRam();
        const auto& samples = engine.getAudioSamples();
        state.add(ram.data(), ram.size());
        state.add(frameBuffer.data(), frameBuffer.size() * sizeof(uint32_t));
        for (const int16_t sample : samples)
        {
            const uint8_t bytes[2] = {static_cast<uint8_t>(sample & 0xff), static_cast<uint8_t>((sample >> 8) & 0xff)};
            audio.add(bytes, sizeof(bytes));
        }

        if (frame % CHECKPOINT_INTERVAL != 0)
        {
            continue;
        }

        if (print)
        {
            std::printf("    {%d, 0x%016" PRIx64 ", 0x%016" PRIx64 "},\n", frame, state.get(), audio.get());
            continue;
        }

        const bool stateMatches = state.get() == expected->state;
        const bool audioMatches = audio.get() == expected->audio;
        std::printf("frame %5d: state %s, audio %s\n", frame, stateMatches ? "ok" : "MISMATCH", audioMatches ? "ok" : "MISMATCH");
        failures += (stateMatches ? 0 : 1) + (audioMatches ? 0 : 1);
        expected++;
    }

    if (!print)
    {
        std::printf(failures == 0 ? "PASSED\n" : "FAILED\n");
    }
    return failures == 0 ? 0 : 1;
}
