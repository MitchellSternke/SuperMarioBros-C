#include <fstream>
#include <iostream>
#include <list>

#include "Configuration.hpp"

/**
 * List of all supported configuration options.
 */
std::list<ConfigurationOption*> Configuration::configurationOptions = {
    &Configuration::audioFrequency,
    &Configuration::renderScale,
    &Configuration::romFileName
};

/**
 * Audio frequency, in Hz
 */
IntegerConfigurationOption Configuration::audioFrequency(
    "audio.frequency", 48000
);

/**
 * Scaling factor for rendering.
 */
IntegerConfigurationOption Configuration::renderScale(
    "video.scale", 3
);

/**
 * Filename for the SMB ROM image.
 */
StringConfigurationOption Configuration::romFileName(
    "game.rom_file", "Super Mario Bros. (JU) (PRG0) [!].nes"
);

ConfigurationOption::ConfigurationOption(
    const std::string& path) :
    path(path)
{
}

const std::string& ConfigurationOption::getPath() const
{
    return path;
}

StringConfigurationOption::StringConfigurationOption(
    const std::string& path,
    const std::string& defaultValue) :
    ConfigurationOption(path),
    stringValue(defaultValue)
{
}

const std::string& StringConfigurationOption::getValue() const
{
    return stringValue;
}

void StringConfigurationOption::initializeValue(const boost::property_tree::ptree& propertyTree)
{
    stringValue = propertyTree.get<std::string>(getPath(), stringValue);
    std::cout << "Configuration option \"" << getPath() << "\" set to \"" << stringValue << "\"" << std::endl;
}

IntegerConfigurationOption::IntegerConfigurationOption(
    const std::string& path,
    int defaultValue) :
    ConfigurationOption(path),
    integerValue(defaultValue)
{
}

int IntegerConfigurationOption::getValue() const
{
    return integerValue;
}

void IntegerConfigurationOption::initializeValue(const boost::property_tree::ptree& propertyTree)
{
    integerValue = propertyTree.get<int>(getPath(), integerValue);
    std::cout << "Configuration option \"" << getPath() << "\" set to " << integerValue << std::endl;
}

void Configuration::initialize(const std::string& fileName)
{
    // Check that the configuration file exists.
    // If it does not exist, we will fall back to default values.
    //
    std::ifstream configFile(fileName.c_str());

    if (configFile.good())
    {
        // Load the configuration file into a property tree to parse it
        //
        boost::property_tree::ptree propertyTree;
        boost::property_tree::ini_parser::read_ini(configFile, propertyTree);

        // Try to load the value for all known config options
        //
        for (auto option : configurationOptions)
        {
            option->initializeValue(propertyTree);
        }
    }
}

int Configuration::getAudioFrequency()
{
    return audioFrequency.getValue();
}

int Configuration::getRenderScale()
{
    return renderScale.getValue();
}

const std::string& Configuration::getRomFileName()
{
    return romFileName.getValue();
}
