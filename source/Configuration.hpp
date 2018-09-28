#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <list>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

/**
 * Base class for configuration options.
 */
class ConfigurationOption
{
public:
    /**
     * Construct a configuration option.
     * 
     * @param path the path to the option in the conf file,
     * in the format "section.key" where section is the
     * INI section (e.g. [example]) and key is the option
     * name in the section.
     */
    ConfigurationOption(
        const std::string& path);
    
    /**
     * Get the path of the configuration option within the INI file.
     */
    const std::string& getPath() const;

    /**
     * Initialize the configuration option from the parsed property tree.
     */
    virtual void initializeValue(const boost::property_tree::ptree& propertyTree)=0;

private:
    std::string path;
};

/**
 * Basic configuration option template for values that have simple types and only a default value.
 */
template <typename T>
class BasicConfigurationOption : public ConfigurationOption
{
public:
    /**
     * Constructor.
     */
    BasicConfigurationOption(
        const std::string& path,
        const T& defaultValue) :
        ConfigurationOption(path),
        value(defaultValue)
    {
    }
    
    /**
     * Get the value of the configuration option.
     */
    const T& getValue() const
    {
        return value;
    }

    /**
     * Initialize the configuration option.
     */
    void initializeValue(const boost::property_tree::ptree& propertyTree) override
    {
        value = propertyTree.get<T>(getPath(), value);
        std::cout << "Configuration option \"" << getPath() << "\" set to \"" << value << "\"" << std::endl;
    }

private:
    T value;
};

/**
 * Singleton class that reads the configuration file that provides global
 * program options from the user.
 */
class Configuration
{
public:
    /**
     * Initialize the global configuration from the given file.
     */
    static void initialize(const std::string& fileName);

    /**
     * Get if audio is enabled or not.
     */
    static bool getAudioEnabled();

    /**
     * Get the desired audio frequency, in Hz.
     */
    static int getAudioFrequency();

    /**
     * Get the desired frame rate (per second).
     */
    static int getFrameRate();

    /**
     * Get the filename for a custom palette to use for rendering.
     */
    static const std::string& getPaletteFileName();

    /**
     * Get the desired ROM file name.
     */
    static const std::string& getRomFileName();

    /**
     * Get the desired render scale.
     */
    static int getRenderScale();

    /**
     * Get whether scanlines are enabled or not.
     */
    static bool getScanlinesEnabled();

    /**
     * Get whether vsync is enabled or not.
     */
    static bool getVsyncEnabled();

private:
    static BasicConfigurationOption<bool> audioEnabled;
    static BasicConfigurationOption<int> audioFrequency;
    static BasicConfigurationOption<int> frameRate;
    static BasicConfigurationOption<std::string> paletteFileName;
    static BasicConfigurationOption<int> renderScale;
    static BasicConfigurationOption<std::string> romFileName;
    static BasicConfigurationOption<bool> scanlinesEnabled;
    static BasicConfigurationOption<bool> vsyncEnabled;

    static std::list<ConfigurationOption*> configurationOptions;
};

#endif // CONFIGURATION_HPP
