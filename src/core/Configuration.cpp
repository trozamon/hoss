#include "Configuration.hpp"
#include <array>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <yaml.h>

using boost::property_tree::ptree;
using hoss::core::Configuration;
using std::array;
using std::string;
using std::vector;

static void parse(ptree &tree, yaml_parser_t &parser);

Configuration Configuration::fromYaml(std::ifstream &yaml)
{
        array<char, 4096> buf;
        string content;

        while (yaml.good())
        {
                yaml.read(buf.data(), 4096);
                content.append(buf.data(), yaml.gcount());
        }

        return fromYaml(content);
}

Configuration Configuration::fromYaml(const string &yaml)
{
        yaml_parser_t parser;
        yaml_event_t event;
        ptree tree;
        Configuration c;

        yaml_parser_initialize(&parser);

        yaml_parser_set_input_string(&parser,
                        reinterpret_cast<const unsigned char *>(yaml.c_str()),
                        yaml.size());

        bool res = yaml_parser_parse(&parser, &event);
        if (!res)
        {
                throw std::invalid_argument{"Could not parse YAML"};
        }

        if (event.type != YAML_STREAM_START_EVENT)
        {
                throw std::invalid_argument{"Missing stream start"};
        }

        res = yaml_parser_parse(&parser, &event);
        if (!res)
        {
                throw std::invalid_argument{"Could not parse YAML"};
        }

        if (event.type != YAML_DOCUMENT_START_EVENT)
        {
                throw std::invalid_argument{"Missing document start"};
        }

        parse(tree, parser);
        yaml_parser_delete(&parser);
        c._values = tree;

        return c;
}

static vector<string> split(const string &s, char delim)
{
        size_t begin = 0;
        vector<string> parts;

        for (size_t i = 0; i < s.size(); i++)
        {
                if (s[i] == delim)
                {
                        parts.push_back(s.substr(begin, i));
                        begin = i + 1;
                }
        }

        parts.push_back(s.substr(begin));

        return parts;
}

vector<string> Configuration::arr(const string &key)
{
        vector<string> parts = split(key, '.');
        string last = parts[parts.size() - 1];
        vector<string> res;
        auto tmp = _values;

        for (size_t i = 0; i < parts.size() - 1; i++)
        {
                auto it = tmp.find(parts[i]);

                if (it == _values.not_found())
                {
                        return res;
                }

                tmp = it->second;
        }

        for (auto it = tmp.begin(); it != tmp.end(); it++)
        {
                if (last == it->first)
                {
                        res.push_back(it->second.get_value<string>());
                }
        }

        return res;
}

static string join(const vector<string> &parts)
{
        string tmp;

        for (size_t i = 0; i < parts.size(); i++)
        {
                if (i > 0)
                {
                        tmp += ".";
                }

                tmp += parts[i];
        }

        return tmp;
}

static string join(const vector<string> &parts, const string &part)
{
        vector<string> tmp = parts;

        tmp.push_back(part);

        return join(tmp);
}

void parse(ptree &tree, yaml_parser_t &parser)
{
        yaml_event_t event;
        bool done = false;
        vector<string> root;
        string key = "";
        bool inseq = false;

        while (!done)
        {
                if (!yaml_parser_parse(&parser, &event))
                {
                        throw std::invalid_argument{"Could not parse YAML"};
                }

                string tmp;

                switch (event.type)
                {
                case YAML_SCALAR_EVENT:
                       tmp = reinterpret_cast<char *>(event.data.scalar.value);

                        if (inseq)
                        {
                                tree.add(join(root, key), tmp);
                        }
                        else if (key.size() == 0)
                        {
                               key = tmp;
                        }
                        else
                        {
                                tree.put(join(root, key), tmp);
                                key = "";
                        }
                        break;
                case YAML_SEQUENCE_START_EVENT:
                        inseq = true;
                        break;
                case YAML_SEQUENCE_END_EVENT:
                        inseq = false;
                        key = "";
                        break;
                case YAML_MAPPING_START_EVENT:
                        if (key.size() > 0)
                        {
                                root.push_back(key);
                                key = "";
                        }
                        break;
                case YAML_MAPPING_END_EVENT:
                        if (root.size() > 0)
                        {
                                root.pop_back();
                        }
                        key = "";
                        break;
                default:
                        break;
                }

                done = (event.type == YAML_STREAM_END_EVENT);

                yaml_event_delete(&event);
        }
}
