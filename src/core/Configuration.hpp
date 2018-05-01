#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <string>

namespace hoss
{

namespace core
{

/**
 * Base class for loading configuration from YAML.
 */
class Configuration
{
public:
        /**
         * Load configuration from a file.
         */
        static Configuration fromYaml(std::ifstream &yaml);

        /**
         * Load configuration from a YAML-formatted string.
         */
        static Configuration fromYaml(const std::string &yaml);

        /**
         * Get a string value from this configuration.
         */
        template <typename T>
        T get(const std::string &key)
        {
                return _values.get<T>(key);
        }

        std::vector<std::string> arr(const std::string &key);

private:
        boost::property_tree::ptree _values;
};

} /* namespace core */

} /* namespace hoss */
