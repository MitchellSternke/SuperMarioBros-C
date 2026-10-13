#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "parser.hpp"
#include "translator.hpp"

// Write a file only if its contents changed, so unchanged sources are not rebuilt.
//
static bool writeIfChanged(const std::string& path, const std::string& contents)
{
    std::ifstream existing(path, std::ios::binary);
    std::ostringstream current;
    current << existing.rdbuf();
    if (existing && current.str() == contents)
    {
        return true;
    }

    std::ofstream file(path, std::ios::binary);
    file << contents;
    return static_cast<bool>(file);
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::fprintf(stderr, "usage: codegen <input.asm> <output directory>\n");
        return 1;
    }

    Program program = parseProgram(argv[1]);

    GeneratedSources sources;
    try
    {
        sources = translate(program);
    }
    catch (const std::runtime_error& error)
    {
        std::fprintf(stderr, "Translation failed: %s\n", error.what());
        return 1;
    }

    const std::string outputDirectory = argv[2];
    const std::pair<const char*, const std::string*> outputs[] = {
        {"SMB.cpp", &sources.code},
        {"SMBData.cpp", &sources.data},
        {"SMBDataPointers.hpp", &sources.dataAddresses},
        {"SMBConstants.hpp", &sources.constants},
    };
    for (const auto& output : outputs)
    {
        const std::string path = outputDirectory + "/" + output.first;
        if (!writeIfChanged(path, *output.second))
        {
            std::fprintf(stderr, "Unable to write \"%s\"\n", path.c_str());
            return 1;
        }
    }

    return 0;
}
