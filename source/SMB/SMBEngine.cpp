#include <cstring>

#include "../Emulation/APU.hpp"
#include "../Emulation/PPU.hpp"

#include "SMBEngine.hpp"

SMBEngine::SMBEngine(const uint8_t* chr, int audioSampleRate, int frameRate) :
    apu(std::make_unique<APU>(audioSampleRate, frameRate)),
    ppu(std::make_unique<PPU>(chr)),
    audioEnabled(audioSampleRate > 0)
{
}

SMBEngine::~SMBEngine() = default;

Controller& SMBEngine::getController(int player)
{
    return controllers.at(player);
}

const std::vector<int16_t>& SMBEngine::getAudioSamples() const
{
    return apu->getSamples();
}

const std::array<uint8_t, 0x800>& SMBEngine::getRam() const
{
    return ram;
}

void SMBEngine::render(uint32_t* buffer) const
{
    ppu->render(buffer, palette);
}

void SMBEngine::reset()
{
    // Run the translated code for initialization
    code(0);
}

void SMBEngine::setPalette(const Palette& newPalette)
{
    palette = newPalette;
}

void SMBEngine::update()
{
    // Run the translated code for the NMI handler
    code(1);

    if (audioEnabled)
    {
        apu->stepFrame();
    }
}

uint8_t SMBEngine::readIO(uint16_t address)
{
    // PPU registers are mirrored every 8 bytes
    if (address < 0x4000)
    {
        return ppu->readRegister(0x2000 + (address & 0x7));
    }

    switch (address)
    {
    case 0x4016:
        return controllers[0].readByte();
    case 0x4017:
        return controllers[1].readByte();
    default:
        return 0;
    }
}

void SMBEngine::writeIO(uint16_t address, uint8_t value)
{
    // PPU registers are mirrored every 8 bytes
    if (address < 0x4000)
    {
        ppu->writeRegister(0x2000 + (address & 0x7), value);
        return;
    }

    switch (address)
    {
    case 0x4014: // OAM DMA
    {
        uint8_t page[256];
        for (int i = 0; i < 256; i++)
        {
            page[i] = readData(static_cast<uint16_t>((value << 8) + i));
        }
        ppu->writeDMA(page);
        break;
    }
    case 0x4016:
        controllers[0].writeByte(value);
        controllers[1].writeByte(value);
        break;
    default:
        if (address < 0x4020)
        {
            apu->writeRegister(address, value);
        }
        break;
    }
}

void SMBEngine::writeData(uint16_t address, const uint8_t* data, std::size_t length)
{
    std::memcpy(&dataStorage[address - 0x8000], data, length);
}
