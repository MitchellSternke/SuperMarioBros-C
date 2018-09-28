#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

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
 * Represents a string-valued option.
 */
class StringConfigurationOption : public ConfigurationOption
{
public:
    /**
     * Constructor.
     */
    StringConfigurationOption(
        const std::string& path,
        const std::string& defaultValue);
    
    /**
     * Get the string value of the configuration option.
     */
    const std::string& getValue() const;

    /**
     * Initialize the string configuration option.
     */
    void initializeValue(const boost::property_tree::ptree& propertyTree) override;

private:
    std::string stringValue;
};

/**
 * Represents an integer-valued option.
 */
class IntegerConfigurationOption : public ConfigurationOption
{
public:
    /**
     * Constructor.
     */
    IntegerConfigurationOption(
        const std::string& path,
        int defaultValue);

    /**
     * Get the integer value of the configuration option.
     */
    int getValue() const;

    /**
     * Initialize the integer configuration option.
     */
    void initializeValue(const boost::property_tree::ptree& propertyTree) override;

private:
    int integerValue;
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
     * Get the desired audio frequency, in Hz.
     */
    static int getAudioFrequency();

    /**
     * Get the desired frame rate (per second).
     */
    static int getFrameRate();

    /**
     * Get the desired ROM file name.
     */
    static const std::string& getRomFileName();

    /**
     * Get the desired render scale.
     */
    static int getRenderScale();

private:
    static IntegerConfigurationOption audioFrequency;
    static IntegerConfigurationOption frameRate;
    static IntegerConfigurationOption renderScale;
    static StringConfigurationOption romFileName;

    static std::list<ConfigurationOption*> configurationOptions;
};

#endif // CONFIGURATION_HPP
