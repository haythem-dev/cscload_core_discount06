#pragma once

#include <vector>
#include <map>
#include <string>

class CommandLineParser {
private:
    std::map<std::string, std::string> _options;
    std::vector<std::string> _positional;

public:
    CommandLineParser(int argc, char** argv);

    bool hasOption(const std::string& name) const;

    std::string getOption(const std::string& name, const std::string& defaultValue = "") const;

    const std::vector<std::string>& getPositional() const;
};
