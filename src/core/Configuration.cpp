#include "Configuration.hpp"

using hoss::core::Configuration;

Configuration Configuration::fromYaml(const std::ifstream &/*yaml*/)
{
        return Configuration();
}

Configuration Configuration::fromYaml(const std::string &/*yaml*/)
{
        return Configuration();
}

std::string Configuration::getString(const std::string &/*key*/)
{
        return "";
}
