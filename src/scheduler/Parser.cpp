#include "Parser.hpp"
#include <array>

using boost::optional;
using boost::property_tree::ptree;
using hoss::core::Log;
using hoss::core::Yaml;
using hoss::core::linesep;
using hoss::scheduler::JobDefinition;
using hoss::scheduler::Parser;
using std::array;
using std::ifstream;
using std::string;

static const string JOB_BUILD_TYPE{"job.build.type"};
static const string JOB_NAME{"job.name"};
static const string JOB_SOURCE_TYPE{"job.source.type"};
static const string JOB_SOURCE_URI{"job.source.uri"};

Parser::Parser() : log{Log::getLogger("Parser")}
{
}

void Parser::parse(ifstream &yaml)
{
        parse(Yaml::fromYaml(yaml));
}

void Parser::parse(const string &yaml)
{
        parse(Yaml::fromYaml(yaml));
}

void Parser::parse(const Yaml &yaml)
{
        optional<string> name = yaml.tryGet<string>(JOB_NAME);

        if (name)
        {
                log.info() << "Parsing job " << *name << linesep;
                _jobHandler(parseJob(yaml));
        }
        else
        {
                log.warning("Could not load a job");
        }
}

JobDefinition Parser::parseJob(const Yaml &yaml)
{
        return JobDefinition()
                .id(yaml.get<string>(JOB_NAME))
                .sourceType(yaml.get<string>(JOB_SOURCE_TYPE))
                .sourceUri(yaml.get<string>(JOB_SOURCE_URI))
                .buildType(yaml.get<string>(JOB_BUILD_TYPE));
}

void Parser::jobHandler(std::function<void(JobDefinition)> handler)
{
        _jobHandler = handler;
}
