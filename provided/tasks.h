#pragma once

#include <string>
#include <vector>

struct Command {
    // Program name is arguments[0]; remaining strings are its arguments.
    std::vector<std::string> arguments;
};

struct Task {
    std::string name;
    std::vector<Command> commands;
};
