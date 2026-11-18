#include "taskparser.h"

#include <cstddef>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include <utility>

namespace {

[[noreturn]] void syntaxError(const std::string& filename,
                              std::size_t lineNumber,
                              const std::string& message) {
    throw std::runtime_error(filename + ":" + std::to_string(lineNumber)
                             + ": " + message);
}

} // namespace

std::vector<Task> parseTaskFile(const std::string& filename) {
    std::ifstream input{filename};
    if (!input.is_open()) {
        throw std::ios_base::failure("Could not open task file '" + filename + "'");
    }

    std::vector<Task> tasks;
    std::unordered_set<std::string> taskNames;
    Task currentTask;
    bool insideTask = false;
    std::size_t lineNumber = 0;
    std::size_t taskStartLine = 0;
    std::string line;

    while (std::getline(input, line)) {
        ++lineNumber;

        // Accept the optional UTF-8 byte-order mark written by some editors.
        if (lineNumber == 1 && line.compare(0, 3, "\xEF\xBB\xBF") == 0) {
            line.erase(0, 3);
        }

        std::istringstream tokens{line};
        std::string keyword;
        if (!(tokens >> keyword) || keyword.front() == '#') {
            continue;
        }

        if (keyword == "task") {
            if (insideTask) {
                syntaxError(filename, lineNumber,
                            "expected 'end' before starting another task");
            }

            std::string name;
            std::string extra;
            if (!(tokens >> name) || tokens >> extra) {
                syntaxError(filename, lineNumber, "expected: task NAME");
            }
            if (!taskNames.insert(name).second) {
                syntaxError(filename, lineNumber, "duplicate task name '" + name + "'");
            }

            currentTask = Task{name, {}};
            insideTask = true;
            taskStartLine = lineNumber;
        } else if (keyword == "run") {
            if (!insideTask) {
                syntaxError(filename, lineNumber, "'run' must appear inside a task");
            }

            Command command;
            std::string argument;
            while (tokens >> argument) {
                command.arguments.push_back(argument);
            }
            if (command.arguments.empty()) {
                syntaxError(filename, lineNumber, "expected: run PROGRAM ARGUMENTS...");
            }
            currentTask.commands.push_back(std::move(command));
        } else if (keyword == "end") {
            if (!insideTask) {
                syntaxError(filename, lineNumber, "'end' has no matching task");
            }

            std::string extra;
            if (tokens >> extra) {
                syntaxError(filename, lineNumber, "'end' takes no arguments");
            }
            if (currentTask.commands.empty()) {
                syntaxError(filename, lineNumber,
                            "task '" + currentTask.name + "' has no run commands");
            }

            tasks.push_back(std::move(currentTask));
            insideTask = false;
        } else {
            syntaxError(filename, lineNumber, "unknown directive '" + keyword + "'");
        }
    }

    if (input.bad()) {
        throw std::ios_base::failure("Could not read task file '" + filename + "'");
    }
    if (insideTask) {
        syntaxError(filename, taskStartLine,
                    "task '" + currentTask.name + "' is missing its 'end'");
    }

    return tasks;
}
