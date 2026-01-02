#include "CommandLineParser.h"

#include <cstring>

CommandLineParser::CommandLineParser(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        const char* arg = argv[i];
        if (std::strncmp(arg, "--", 2) == 0)
        {
            const char* eq = std::strchr(arg, '=');
            if (eq)
            {
                // --option=value
                std::string key(arg + 2, eq - (arg + 2));
                std::string value(eq + 1);
                _options[key] = value;
            }
            else
            {
                // --flag
                _options[std::string(arg + 2)] = "";
            }
        }
        else if (arg[0] == '-')
        {
            // -f
            _options[std::string(arg + 1)] = "";
        }
        else
        {
            // Positional arguments (not starting with - or --)
            _positional.push_back(arg);
        }
    }
}

bool CommandLineParser::hasOption(const std::string& name) const
{
    return _options.find(name) != _options.end();
}

std::string CommandLineParser::getOption(const std::string& name, const std::string& defaultValue) const
{
    std::map<std::string, std::string>::const_iterator it = _options.find(name);
    return it != _options.end() ? it->second : defaultValue;
}

const std::vector<std::string>& CommandLineParser::getPositional() const
{
    return _positional;
}
