#ifndef HOSS_CORE_YAML_HPP
#define HOSS_CORE_YAML_HPP

#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <string>

namespace hoss
{

namespace core
{

/**
 * Base class for loading YAML.
 */
class Yaml
{
public:
        /**
         * Load configuration from a file.
         */
        static Yaml fromYaml(std::ifstream &yaml);

        /**
         * Load configuration from a YAML-formatted string.
         */
        static Yaml fromYaml(const std::string &yaml);

        /**
         * Get a value from this configuration.
         */
        template <typename T>
        T get(const std::string &key) const
        {
                return _values.get<T>(key);
        }

        /**
         * Try to get a value from this configuration.
         */
        template <typename T>
        boost::optional<T> tryGet(const std::string &key) const
        {
                return _values.get_optional<T>(key);
        }

        /**
         * Get a list of strings as a C++ vector.
         */
        std::vector<std::string> arr(const std::string &key) const;

private:
        boost::property_tree::ptree _values;
};

} /* namespace core */

} /* namespace hoss */

#endif /* HOSS_CORE_YAML_HPP */
