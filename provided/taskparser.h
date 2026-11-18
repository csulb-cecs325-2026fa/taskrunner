#pragma once

#include "tasks.h"

#include <string>
#include <vector>

// Read tasks in their declaration order, preserving command/argument order.
//
// Format:
//   task NAME
//   run PROGRAM ARGUMENTS...
//   end
//
// Names must be unique, and each task must contain at least one run command.
// Blank lines and whole-line comments (first non-whitespace character '#')
// are ignored. Tokens are separated by whitespace; quotes, escapes, shell
// operators, and inline comments have no special meaning.
// An empty or comment-only file returns an empty vector.
//
// Throws std::ios_base::failure if the file cannot be opened/read.
// Throws std::runtime_error for malformed input, with filename and line number.
std::vector<Task> parseTaskFile(const std::string& filename);
