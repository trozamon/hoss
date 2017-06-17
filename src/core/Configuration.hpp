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
        static Configuration fromYaml(const std::ifstream &yaml);

        /**
         * Load configuration from a YAML-formatted string.
         */
        static Configuration fromYaml(const std::string &yaml);

        /**
         * Get a string value from this configuration.
         */
        std::string getString(const std::string &key);
};

} /* namespace core */

} /* namespace hoss */
